cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(BasicSim)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(simulation src/simulation.cc ${sources} ${headers})
target_link_libraries(simulation ${Geant4_LIBRARIES})

add_custom_target(BasicSim DEPENDS simulation)

install(TARGETS simulation DESTINATION bin)