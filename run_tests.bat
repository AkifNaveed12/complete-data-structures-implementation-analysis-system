@echo off
cls
echo ============================================================
echo  CDSIAS — C++ Test Suite Builder ^& Runner
echo ============================================================
echo.
echo Select the test you want to build and run:
echo 1. Array Test
echo 2. Linked List Test
echo 3. Stack Test
echo 4. Queue Test
echo 5. Trees Test
echo 6. Graph Test
echo 7. Searching Test
echo 8. Sorting Test
echo 9. Hashing Test
echo 10. Run All Tests
echo 11. Exit
echo.
set /p choice="Enter choice (1-11): "

if "%choice%"=="1" goto test_array
if "%choice%"=="2" goto test_ll
if "%choice%"=="3" goto test_stack
if "%choice%"=="4" goto test_queue
if "%choice%"=="5" goto test_trees
if "%choice%"=="6" goto test_graph
if "%choice%"=="7" goto test_searching
if "%choice%"=="8" goto test_sorting
if "%choice%"=="9" goto test_hashing
if "%choice%"=="10" goto run_all
if "%choice%"=="11" goto end

:test_array
echo.
echo Compiling Array Test...
g++ -std=c++17 tests/test_array.cpp src/core/linear/array.cpp src/analysis/performance.cpp -o test_array.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Array Test.
) else (
    echo Running Array Test...
    test_array.exe
)
pause
goto end

:test_ll
echo.
echo Compiling Linked List Test...
g++ -std=c++17 tests/test_linked_list.cpp src/core/linear/linked_list.cpp src/analysis/performance.cpp -o test_ll.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Linked List Test.
) else (
    echo Running Linked List Test...
    test_ll.exe
)
pause
goto end

:test_stack
echo.
echo Compiling Stack Test...
g++ -std=c++17 tests/test_stack.cpp src/core/stack_queue/stack.cpp src/analysis/performance.cpp -o test_stack.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Stack Test.
) else (
    echo Running Stack Test...
    test_stack.exe
)
pause
goto end

:test_queue
echo.
echo Compiling Queue Test...
g++ -std=c++17 tests/test_queue.cpp src/core/stack_queue/queue.cpp src/analysis/performance.cpp -o test_queue.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Queue Test.
) else (
    echo Running Queue Test...
    test_queue.exe
)
pause
goto end

:test_trees
echo.
echo Compiling Trees Test...
g++ -std=c++17 tests/test_trees.cpp src/core/trees/bt.cpp src/core/trees/bst.cpp src/core/trees/avl.cpp src/core/trees/heap.cpp src/analysis/performance.cpp -o test_trees.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Trees Test.
) else (
    echo Running Trees Test...
    test_trees.exe
)
pause
goto end

:test_graph
echo.
echo Compiling Graph Test...
g++ -std=c++17 tests/test_graph.cpp src/core/graph/graph.cpp src/analysis/performance.cpp -o test_graph.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Graph Test.
) else (
    echo Running Graph Test...
    test_graph.exe
)
pause
goto end

:test_searching
echo.
echo Compiling Searching Test...
g++ -std=c++17 tests/test_searching.cpp src/core/searching_sorting/searching.cpp src/analysis/performance.cpp -o test_searching.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Searching Test.
) else (
    echo Running Searching Test...
    test_searching.exe
)
pause
goto end

:test_sorting
echo.
echo Compiling Sorting Test...
g++ -std=c++17 tests/test_sorting.cpp src/core/searching_sorting/sorting.cpp src/analysis/performance.cpp -o test_sorting.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Sorting Test.
) else (
    echo Running Sorting Test...
    test_sorting.exe
)
pause
goto end

:test_hashing
echo.
echo Compiling Hashing Test...
g++ -std=c++17 tests/test_hashing.cpp src/core/hashing/hash.cpp src/analysis/performance.cpp -o test_hashing.exe
if errorlevel 1 (
    echo [ERROR] Failed to compile Hashing Test.
) else (
    echo Running Hashing Test...
    test_hashing.exe
)
pause
goto end

:run_all
echo.
echo Building all tests...
g++ -std=c++17 tests/test_array.cpp src/core/linear/array.cpp src/analysis/performance.cpp -o test_array.exe
g++ -std=c++17 tests/test_linked_list.cpp src/core/linear/linked_list.cpp src/analysis/performance.cpp -o test_ll.exe
g++ -std=c++17 tests/test_stack.cpp src/core/stack_queue/stack.cpp src/analysis/performance.cpp -o test_stack.exe
g++ -std=c++17 tests/test_queue.cpp src/core/stack_queue/queue.cpp src/analysis/performance.cpp -o test_queue.exe
g++ -std=c++17 tests/test_trees.cpp src/core/trees/bt.cpp src/core/trees/bst.cpp src/core/trees/avl.cpp src/core/trees/heap.cpp src/analysis/performance.cpp -o test_trees.exe
g++ -std=c++17 tests/test_graph.cpp src/core/graph/graph.cpp src/analysis/performance.cpp -o test_graph.exe
g++ -std=c++17 tests/test_searching.cpp src/core/searching_sorting/searching.cpp src/analysis/performance.cpp -o test_searching.exe
g++ -std=c++17 tests/test_sorting.cpp src/core/searching_sorting/sorting.cpp src/analysis/performance.cpp -o test_sorting.exe
g++ -std=c++17 tests/test_hashing.cpp src/core/hashing/hash.cpp src/analysis/performance.cpp -o test_hashing.exe

echo.
echo Running all tests...
echo ----------------------------------------
echo Running Array Test:
test_array.exe
echo.
echo ----------------------------------------
echo Running Linked List Test:
test_ll.exe
echo.
echo ----------------------------------------
echo Running Stack Test:
test_stack.exe
echo.
echo ----------------------------------------
echo Running Queue Test:
test_queue.exe
echo.
echo ----------------------------------------
echo Running Trees Test:
test_trees.exe
echo.
echo ----------------------------------------
echo Running Graph Test:
test_graph.exe
echo.
echo ----------------------------------------
echo Running Searching Test:
test_searching.exe
echo.
echo ----------------------------------------
echo Running Sorting Test:
test_sorting.exe
echo.
echo ----------------------------------------
echo Running Hashing Test:
test_hashing.exe
pause
goto end

:end
echo Exiting.
