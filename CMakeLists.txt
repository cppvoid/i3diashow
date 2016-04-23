project(i3diashow)
cmake_minimum_required(VERSION 2.8)

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost COMPONENTS program_options filesystem system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp" "src/*.c" "inc/*.h")
include_directories("inc")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for cxx_auto_type)
