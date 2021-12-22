cmake_minimum_required(VERSION 3.21)
project(mitp_sfml_gui)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(SFML 2.5.1 REQUIRED)

add_executable(mitp_sfml_gui
        main.cpp
        widget/text_area.hpp
        widget/text_area.cpp
        event_listener/keyboard_listener.hpp
        event_listener/keyboard_listener.cpp
        event_listener/controls_listener.hpp
        event_listener/controls_listener.cpp)

target_link_libraries(mitp_sfml_gui PRIVATE sfml-graphics)
target_include_directories(mitp_sfml_gui PRIVATE
        $<TARGET_PROPERTY:sfml-graphics,INCLUDE_DIRECTORIES>
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR})
