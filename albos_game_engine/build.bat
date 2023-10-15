@echo off

IF NOT EXIST build mkdir build
pushd build
cl -FC -Zi ..\albos_win32platform_layer.cpp user32.lib gdi32.lib
popd

