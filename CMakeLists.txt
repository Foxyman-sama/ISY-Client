cmake_minimum_required(VERSION 3.16)

project(ISY VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES
    include/client.hpp
    include/clientmodel.hpp)
set(SOURCES
    src/client.cpp
    src/clientmodel.cpp)

find_package(Qt6 6.2 COMPONENTS Quick Qml QuickControls2  REQUIRED)

qt_add_executable(ISY
    main.cpp
    ${INCLUDES}
    ${SOURCES})
qt_add_qml_module(ISY
    URI ISY
    VERSION 1.0
    QML_FILES
    qml/main.qml
    qml/MainScreen.qml
    qml/List.qml
    qml/EventButton.qml
    qml/FileControl.qml
    qml/TouchScreen.qml)
target_link_libraries(ISY PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
)
include_directories(
    include
    D:/Git/vcpkg/installed/x64-windows/include)
link_directories(D:/Git/vcpkg/installed/x64-windows/lib)
