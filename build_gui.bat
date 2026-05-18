@echo off
cls
echo ============================================================
echo  CDSIAS — C++ GUI Application Builder
echo ============================================================
echo.
echo [1/4] Configuring MSYS2 UCRT64 Toolchain PATH...
set "PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%"

echo.
echo [2/4] Setting up build directory...
if exist build_gui rmdir /s /q build_gui
mkdir build_gui
cd build_gui

echo.
echo [3/4] Running CMake (Configuring Qt5)...
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/msys64/ucrt64" ..

if errorlevel 1 (
    echo.
    echo [ERROR] CMake configuration failed. 
    echo Please make sure you have MSYS2 UCRT64 C++ tools and Qt5 installed.
    pause
    exit /b 1
)

echo.
echo [4/4] Compiling the GUI Application...
cmake --build .

if errorlevel 1 (
    echo.
    echo [ERROR] Compilation failed.
    pause
    exit /b 1
)

echo.
echo [SUCCESS] Compilation succeeded!
echo Launching CDSIAS GUI...
echo.
pause
cdsias_gui.exe
