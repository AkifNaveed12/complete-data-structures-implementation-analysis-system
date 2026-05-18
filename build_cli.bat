@echo off
cls
echo ============================================================
echo  CDSIAS — C++ Application Builder
echo ============================================================
echo.
echo [1/2] Compiling all C++ source files...
echo (This will take about 2-3 seconds, please wait...)
echo.

g++ -std=c++17 src/main.cpp src/core/linear/array.cpp src/core/linear/linked_list.cpp src/core/stack_queue/stack.cpp src/core/stack_queue/queue.cpp src/core/trees/bt.cpp src/core/trees/bst.cpp src/core/trees/avl.cpp src/core/trees/heap.cpp src/core/graph/graph.cpp src/core/searching_sorting/searching.cpp src/core/searching_sorting/sorting.cpp src/core/hashing/hash.cpp src/analysis/performance.cpp -o app.exe

if errorlevel 1 goto failed

echo.
echo [2/2] [SUCCESS] Compilation succeeded!
echo Running the application...
echo.
pause
app.exe
goto end

:failed
echo.
echo [ERROR] Compilation failed. Please make sure g++ is installed and in your PATH.
pause
exit /b 1

:end


