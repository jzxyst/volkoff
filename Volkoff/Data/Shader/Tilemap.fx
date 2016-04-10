//=============================================================================
// �� Basic3D
//-----------------------------------------------------------------------------
//	
//=============================================================================

//-------------------------------------------------------------------------
// �萔���W�X�^
//-------------------------------------------------------------------------
// �ϊ��s��
float4x4        gWorldMatrix		: WORLD;
float4x4        gViewProjMatrix		: VIEWPROJECTION;

// �}�e���A��
float4          gMaterialDiffuse    : DIFFUSE  < string Object = "Geometry"; >;
float3          gMaterialAmbient    : AMBIENT  < string Object = "Geometry"; >;
float3          gMaterialEmisive    : EMISSIVE < string Object = "Geometry"; >;
float3          gMaterialSpecular   : SPECULAR < string Object = "Geometry"; >;
float           gSpecularPower      : SPECULARPOWER < string Object = "Geometry"; >;
float3          gMaterialToon       : TOONCOLOR;

// ���C�g
float3          gLightDiffuse       : DIFFUSE   < string Object = "Light"; >;
float3          gLightAmbient       : AMBIENT   < string Object = "Light"; >;
float3          gLightSpecular      : SPECULAR  < string Object = "Light"; >;
static float4   gDiffuseColor       = gMaterialDiffuse  * float4( gLightDiffuse, 1.0f );
static float3   gAmbientColor       = saturate( gMaterialAmbient  * gLightAmbient + gMaterialEmisive );
static float3   gSpecularColor      = gMaterialSpecular * gLightSpecular;

// �I�u�W�F�N�g�̐F���
float           gOpacity            : OPACITY;
float4          gColorScale         : COLORSCALE;
float4          gBlendColor         : BLENDCOLOR;
float4          gTone               : TONE;
static float4   gColor              = float4( gColorScale.xyz, gColorScale.a * gOpacity );

//-------------------------------------------------------------------------
// �e�X�N�`��
//-------------------------------------------------------------------------
texture gMaterialTexture	        : MATERIALTEXTURE;
sampler gTexSampler = sampler_state
{
    texture = < gMaterialTexture >;
    MINFILTER = NONE;
    MAGFILTER = NONE;
    
    ADDRESSU = CLAMP;
    ADDRESSV = CLAMP;
//BordColor=0xffffffff;
};

//-------------------------------------------------------------------------
// �o�͍\����
//-------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos      : POSITION;
    float4 Color    : COLOR0;
    float2 TexUV    : TEXCOORD0;
};

//-------------------------------------------------------------------------
// VS
//-------------------------------------------------------------------------
VS_OUTPUT vsBasic(
    float3 in_pos_      : POSITION,
	float4 in_color_    : COLOR0,
	float2 in_uv_       : TEXCOORD0 )
{
    VS_OUTPUT o;
    
    // ���W�ϊ�
    o.Pos = mul( float4( in_pos_, 1.0f ), gWorldMatrix );
	o.Pos = mul( o.Pos, gViewProjMatrix );
    
	// �f�B�t���[�Y�F�{�A���r�G���g�F �v�Z
    o.Color = in_color_;
    o.Color.rgb = saturate( max( 0, 1.0 * gDiffuseColor.rgb + gAmbientColor ) );//dot( Out.Normal, -LightDirection ))
    o.Color.a = gDiffuseColor.a;
	
	// �e�N�X�`�����W
	o.TexUV = in_uv_;
	o.TexUV.x += 0.00001;
	o.TexUV.y += 0.00001;
    
    return o;
}

//-------------------------------------------------------------------------
// PS
//-------------------------------------------------------------------------
float4 psBasic(
    float4 in_color_    : COLOR0,
    float2 in_uv_       : TEXCOORD0  ) : COLOR
{
    float4 out_color = tex2D( gTexSampler, in_uv_ ) * in_color_ * gColor;
    
    // �u�����h�̌v�Z
    //out_color.rgb = ( gBlendColor.rgb * gBlendColor.a ) + ( out_color.rgb * ( 1.0 - gBlendColor.a ) );
    out_color.rgb = lerp( out_color.rgb, gBlendColor.rgb, gBlendColor.a );
    
    // �F���̌v�Z�B(NTSC �n���d���ϖ@�Ƃ����炵���B�΂������Ȃ�ƂȂ����邭������Ƃ���h��)
	float y = ( 0.208012 * out_color.r + 0.586611 * out_color.g + 0.114478 * out_color.b ) * gTone.w;
    out_color.rgb = ( out_color.rgb * ( 1.0 - gTone.w ) ) + y + gTone.rgb;

    return out_color;
}

//-------------------------------------------------------------------------
// �e�N�j�b�N�錾
//-------------------------------------------------------------------------
technique MainDraw
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsBasic();
        PixelShader	 = compile ps_2_0 psBasic();
    }
}

//=============================================================================
//                              end of file
//=============================================================================