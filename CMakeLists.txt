cmake_minimum_required(VERSION 3.20)

project(OcrTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# find_package(OpenCV REQUIRED)
# find_package(Leptonica REQUIRED)
# find_package(Tesseract REQUIRED)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(EXECUTABLE_NAME OcrTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${EXECUTABLE_NAME})

add_subdirectory(src)

target_link_libraries(OcrTest PRIVATE
        # ${OpenCV_LIBS}
        # ${Leptonica_LIBS}
        # ${Tesseract_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
        )

target_include_directories(OcrTest PRIVATE
        # ${OpenCV_INCLUDE_DIRS}
        # ${Leptonica_INCLUDE_DIRS}
        # ${Tesseract_INCLUDE_DIRS}
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

