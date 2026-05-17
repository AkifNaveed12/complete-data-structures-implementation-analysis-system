cmake_minimum_required(VERSION 3.16)
project(CDSIAS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Qt 6 path if it exists
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

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
)

add_executable(cdsias_gui
    ${CORE_SOURCES}
    ${GUI_SOURCES}
)

target_link_libraries(cdsias_gui PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(cdsias_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/analysis
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gui
)

target_compile_definitions(cdsias_gui PRIVATE CDSIAS_GUI=1)

