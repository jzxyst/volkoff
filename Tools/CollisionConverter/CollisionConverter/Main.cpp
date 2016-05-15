
#include <Lumino.h>
using namespace ln;

class Collision
{
private:
	static const int SET_H_NUM = 12; // 短形を取得する範囲が水平にいくつ並ぶか
	static const int SET_V_NUM = 12; // 短形を取得する範囲が垂直にいくつ並ぶか
	static const int CellW = 160;
	static const int CellH = 160;

	struct Position
	{
		int H;
		int V;
	};

	struct Data
	{
		Position Atk_pos; // 攻撃判定
		Position Atk_size;

		Position Dmg_pos; // ダメージ判定
		Position Dmg_size;

		Position origin; // 基準点

		byte_t started;
	};

	Data m_data[SET_H_NUM*SET_V_NUM];

	void FillRect(Bitmap* bitmap, const Rect& rect, int element)
	{
		for (int y = rect.GetTop(); y < rect.GetBottom(); ++y)
		{
			for (int x = rect.GetLeft(); x < rect.GetRight(); ++x)
			{
				Color c = bitmap->GetPixel(x, y);
				if (element == 0) c.r = 255;
				if (element == 1) c.g = 255;
				if (element == 2) c.b = 255;
				c.a = 255;
				bitmap->SetPixel(x, y, c);
			}
		}
	}

	void ReadRect(Bitmap* bitmap, const Rect& rect, Data* outData)
	{
		Position atkLT = { INT_MAX, INT_MAX };
		Position atkRB = { INT_MIN, INT_MIN };
		Position dmgLT = { INT_MAX, INT_MAX };
		Position dmgRB = { INT_MIN, INT_MIN };

		for (int y = 0; y < rect.width; ++y)
		{
			for (int x = 0; x < rect.height; ++x)
			{
				Color c = bitmap->GetPixel(rect.x + x, rect.y + y);
				// 攻撃判定は赤
				if (c.r > 0)
				{
					atkLT.H = std::min(atkLT.H, x);
					atkLT.V = std::min(atkLT.V, y);
					atkRB.H = std::max(atkRB.H, x);
					atkRB.V = std::max(atkRB.V, y);
				}
				// ダメージ判定は青
				if (c.b > 0)
				{
					dmgLT.H = std::min(dmgLT.H, x);
					dmgLT.V = std::min(dmgLT.V, y);
					dmgRB.H = std::max(dmgRB.H, x);
					dmgRB.V = std::max(dmgRB.V, y);
				}
				// 原点は緑の1px
				if (c.g > 0)
				{
					outData->origin.H = x;
					outData->origin.V = y;
				}
			}
		}

		if (atkLT.H != INT_MAX)
		{
			outData->Atk_pos.H = atkLT.H;
			outData->Atk_pos.V = atkLT.V;
			outData->Atk_size.H = atkRB.H - atkLT.H + 1;
			outData->Atk_size.V = atkRB.V - atkLT.V + 1;
		}
		if (dmgLT.H != INT_MAX)
		{
			outData->Dmg_pos.H = dmgLT.H;
			outData->Dmg_pos.V = dmgLT.V;
			outData->Dmg_size.H = dmgRB.H - dmgLT.H + 1;
			outData->Dmg_size.V = dmgRB.V - dmgLT.V + 1;
		}
	}

public:

	// .dat を .png に変換する
	void DatToPng(const PathName& datFilePath)
	{
		auto file = FileStream::Create(datFilePath, FileOpenMode::Read);
		file->Read(m_data, sizeof(Data) * SET_H_NUM * SET_V_NUM);

		Bitmap bitmap(Size(2048, 2048), PixelFormat::R8G8B8A8);

		for (int cellY = 0; cellY < SET_H_NUM; ++cellY)
		{
			for (int cellX = 0; cellX < SET_V_NUM; ++cellX)
			{
				Data& data = m_data[cellY * SET_H_NUM + cellX];
				int left = cellX * CellW;
				int top = cellY * CellH;
				// 攻撃判定は赤
				FillRect(&bitmap, Rect(left + data.Atk_pos.H, top + data.Atk_pos.V, data.Atk_size.H, data.Atk_size.V), 0);
				// ダメージ判定は青
				FillRect(&bitmap, Rect(left + data.Dmg_pos.H, top + data.Dmg_pos.V, data.Dmg_size.H, data.Dmg_size.V), 2);
				// 原点は緑の1px
				FillRect(&bitmap, Rect(left + data.origin.H, top + data.origin.V, 1, 1), 1);
			}
		}

		bitmap.Save(datFilePath.ChangeExtension("png"));
	}

	// .png を .dat に変換する
	void PngToDat(const PathName& datFilePath)
	{
		memset(m_data, 0, sizeof(Data) * SET_H_NUM * SET_V_NUM);

		Bitmap bitmap(datFilePath);

		for (int cellY = 0; cellY < SET_H_NUM; ++cellY)
		{
			for (int cellX = 0; cellX < SET_V_NUM; ++cellX)
			{
				Data& data = m_data[cellY * SET_H_NUM + cellX];
				Rect cellRect(cellX * CellW, cellY * CellH, CellW, CellH);
				ReadRect(&bitmap, cellRect, &data);
			}
		}

		FileSystem::WriteAllBytes(datFilePath.ChangeExtension("dat"), m_data, sizeof(Data) * SET_H_NUM * SET_V_NUM);
	}
};

// Lumino アプリケーションのエントリーポイント
void Main()
{
	Console::Alloc();

	PathName path = __argv[1];

	Collision converter;
	if (path.CheckExt("dat"))
	{
		converter.DatToPng(path);
	}
	else if (path.CheckExt("png"))
	{
		converter.PngToDat(path);
	}
}
