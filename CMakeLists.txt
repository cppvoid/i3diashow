project(i3diashow)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBRARIES OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(Boost_USE_STATIC_LIBS   ON)
FIND_PACKAGE(Boost COMPONENTS program_options filesystem system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp" "src/*.c" "inc/*.h")
INCLUDE_DIRECTORIES("inc")

add_executable(${PROJECT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Boost_LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
