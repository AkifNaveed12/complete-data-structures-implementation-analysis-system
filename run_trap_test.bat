@echo off
cls
echo ============================================================
echo  CDSIAS — Traps 1, 2, 3 Test Runner
echo ============================================================
echo.
echo Compiling the test...
g++ -std=c++17 tests/test_operation_count.cpp src/core/stack_queue/stack.cpp src/core/stack_queue/queue.cpp src/analysis/performance.cpp -o test_operation_count.exe

if errorlevel 1 (
    echo [ERROR] Failed to compile the test.
    pause
    exit /b 1
)

echo Compilation successful! Running test...
echo NOTE: Since this is 1000 operations and each has a UI delay in the backend,
echo we are bypassing the text output logs to speed it up visually in console.
echo ------------------------------------------------------------
echo.
test_operation_count.exe > test_results.log
echo Test completed! Results saved to test_results.log.
echo Outputting summary of test_results.log:
echo.
findstr /C:"Expected" /C:"Actual" /C:"PASSED" /C:"FAILED" test_results.log
echo.
pause
