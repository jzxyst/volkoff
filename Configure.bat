
cd External

mkdir Lumino\build\build_msvc140x86_MT
cd Lumino\build\build_msvc140x86_MT
cmake -G "Visual Studio 14 2015" -DLN_USE_UNICODE_CHAR_SET=OFF -DLN_BUILD_FOUNDATION_MODULE=ON -DLN_BUILD_SCENE_MODULE=ON ..\..\
cd ..\..\..\

pause

