
cd External

mkdir Lumino\build
cd Lumino\build
cmake -G "Visual Studio 14 2015" -DLN_USE_UNICODE_CHAR_SET=OFF -DLN_BUILD_FOUNDATION_MODULE=ON -DLN_BUILD_SCENE_MODULE=ON ..\
cd ..\..\

pause

