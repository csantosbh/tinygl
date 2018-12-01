# Set Qt5Widgets_DIR=/opt/Qt/5.11.1/gcc_64/lib/cmake/Qt5Widgets/
cmake_minimum_required(VERSION 3.1.0)

project(qtwindow)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(qtwindow_SRCS
    canvas.ui
    canvas.cpp
    main.cpp
)

# Tell CMake to create the qtwindow executable
add_executable(qtwindow ${qtwindow_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(qtwindow Qt5::Widgets)

