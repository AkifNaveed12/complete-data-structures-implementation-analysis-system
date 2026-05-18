cmake_minimum_required(VERSION 3.16)
project(CDSIAS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Qt 6 path if it exists
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

# Find Qt6 or fallback to Qt5
find_package(Qt6 COMPONENTS Core Gui Widgets)
if(Qt6_FOUND)
    message(STATUS "Found Qt6, building with Qt6...")
    set(QT_LIBRARIES Qt6::Core Qt6::Gui Qt6::Widgets)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
    message(STATUS "Qt6 not found. Found Qt5, building with Qt5...")
    set(QT_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Core sources (ignoring main.cpp which is CLI)
set(CORE_SOURCES
    src/core/linear/array.cpp
    src/core/linear/linked_list.cpp
    src/core/stack_queue/stack.cpp
    src/core/stack_queue/queue.cpp
    src/core/trees/bt.cpp
    src/core/trees/bst.cpp
    src/core/trees/avl.cpp
    src/core/trees/heap.cpp
    src/core/graph/graph.cpp
    src/core/searching_sorting/searching.cpp
    src/core/searching_sorting/sorting.cpp
    src/core/hashing/hash.cpp
    src/analysis/performance.cpp
)

# GUI sources
set(GUI_SOURCES
    src/gui/main.cpp
    src/gui/MainWindow.cpp
    src/gui/visual_qt.cpp
    src/gui/GlobalGuiNotifier.cpp
    src/gui/modules/ModulePanel.cpp
    src/gui/modules/ArrayView.cpp
    src/gui/modules/LinkedListView.cpp
    src/gui/modules/StackQueueView.cpp
    src/gui/modules/TreeView.cpp
    src/gui/modules/PerformanceView.cpp
    src/gui/modules/GraphView.cpp
    src/gui/modules/SearchingSortingView.cpp
    src/gui/modules/HashingView.cpp
)

add_executable(cdsias_gui
    ${CORE_SOURCES}
    ${GUI_SOURCES}
)

target_link_libraries(cdsias_gui PRIVATE ${QT_LIBRARIES})

target_include_directories(cdsias_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/analysis
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)

target_compile_definitions(cdsias_gui PRIVATE CDSIAS_GUI=1)

