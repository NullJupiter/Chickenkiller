PUSHD %~dp0\..\
call vendor\binaries\premake\premake5.exe vs2019
POPD
PAUSE