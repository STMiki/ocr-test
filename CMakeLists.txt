cmake_minimum_required(VERSION 3.15)

project(OcrTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(Tesseract REQUIRED IMPORTED_TARGET tesseract)
pkg_check_modules(Leptonica REQUIRED IMPORTED_TARGET lept)

# find_package(OpenCV REQUIRED)
# find_package(Leptonica REQUIRED)

find_package(SFML COMPONENTS graphics window system)

if (NOT SFML_FOUND)
    message(WARNING "SFML not found, using FetchContent")
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_PROGRESS TRUE)
    FetchContent_MakeAvailable(SFML)
endif()

set(EXECUTABLE_NAME OcrTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${EXECUTABLE_NAME})

add_subdirectory(src)

target_link_libraries(OcrTest PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        PkgConfig::Tesseract
        PkgConfig::Leptonica
        )

target_include_directories(OcrTest PRIVATE
        include
        )

target_compile_options(OcrTest PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        )

target_compile_definitions(OcrTest PRIVATE
        TESSDATA_PREFIX="${CMAKE_SOURCE_DIR}/tessdata"
        )

