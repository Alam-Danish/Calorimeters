# Setup the project
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Calorimeters)


# Find Geant4 package, activating all available UI and Vis drivers by default
find_package(Geant4 REQUIRED ui_all vis_all)

# Setup Geant4 include directories
include(${Geant4_USE_FILE})

# Find all the headers and source files
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# Create an executable and link it to Geant4 libraries
add_executable(calo main.cc ${sources} ${headers})
target_link_libraries(calo ${Geant4_LIBRARIES})

# Create custom target
add_custom_target(Calorimeters DEPENDS calo)