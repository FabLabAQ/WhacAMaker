cmake_minimum_required(VERSION 2.8.11)

project(TiroAlMostro)

# Find the QtQml library
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Gui REQUIRED)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# The list of source and header files
set(SRCS src/main.cpp src/gameItem.cpp)
set(HDRS include/gameItem.h)

# Setting the directory with headers
include_directories(include)

# Adding the file with resources
qt5_add_resources(SRCS resources.qrc)

# Tell CMake to create the helloworld executable
add_executable(TiroAlMostro ${SRCS} ${HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(TiroAlMostro Qt5::Qml Qt5::Gui Qt5::Quick)
