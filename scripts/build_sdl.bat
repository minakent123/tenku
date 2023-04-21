@echo off

if not defined DevEnvDir (
	call "C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
)

set SDL_ROOT=%~dp0..\third_party\SDL
pushd %SDL_ROOT%

set BUILD_DIR=build
del /F /S /Q %BUILD_DIR%
rd /S /Q %BUILD_DIR%
mkdir %BUILD_DIR%
pushd %BUILD_DIR%

call :build_sdl debug Debug
call :build_sdl release Release

popd
popd
exit /b

:build_sdl
	set CONFIG=%1
	set BUILD_TYPE=%2
	mkdir %CONFIG%
	pushd %CONFIG%
	cmake -G Ninja ^
		  -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
		  -DCMAKE_INSTALL_PREFIX=install ^
		  -DSDL_FORCE_STATIC_VCRT=ON ^
		  ../..
	if %ERRORLEVEL% neq 0 (
		popd
		exit /b 1
	)
	ninja
	if %ERRORLEVEL% neq 0 (
		popd
		exit /b 1
	)
	ninja install
	if %ERRORLEVEL% neq 0 (
		popd
		exit /b 1
	)
	popd
	exit /b
