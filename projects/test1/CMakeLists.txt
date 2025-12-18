cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(TestSimulation1)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(test1 src/test1.cc ${sources} ${headers})
target_link_libraries(test1 ${Geant4_LIBRARIES})

add_custom_target(TestSimulation1 DEPENDS test1)

install(TARGETS test1 DESTINATION bin)