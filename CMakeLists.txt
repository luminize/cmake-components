cmake_minimum_required(VERSION 2.8.3)
project(cmake-component)

# C++ 11
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS} -DRTAPI -DRTAPI_FLAVOR_ID=1 -DTHREAD_FLAVOR_ID=1")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
#find_package(Gflags REQUIRED)

# add machinekit interface target
set(MACHINEKIT_RIP_PATH "~/projects/machinekit" CACHE STRING "")
set(MACHINEKIT_INCLUDE_PATHS ${MACHINEKIT_RIP_PATH}/include)
set(MACHINEKIT_LIB_PATH ${MACHINEKIT_RIP_PATH}/lib)

add_library(machinekit INTERFACE)
find_library(LINUXCNCHAL_LIB linuxcnchal PATHS ${MACHINEKIT_LIB_PATH})
find_library(LINUXCNC_LIB linuxcnc ${MACHINEKIT_LIB_PATH})
target_link_libraries(machinekit INTERFACE ${LINUXCNCHAL_LIB})
target_link_libraries(machinekit INTERFACE ${LINUXCNC_LIB})
target_include_directories(machinekit INTERFACE ${MACHINEKIT_INCLUDE_PATHS})
if(NOT LINUXCNCHAL_LIB)
  message(FATAL_ERROR "linuxcnchal lib not found, please install machinekit or set ${MACHINEKIT_RIP_PATH}")
endif()
if(NOT LINUXCNC_LIB)
  message(FATAL_ERROR "linuxcnc lib not found, please install machinekit or set ${MACHINEKIT_RIP_PATH}")
endif()

include_directories(SYSTEM)

include_directories(
  /home/bas/projects/machinekit/include
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Machinekit libraries

#add_library(lcnc STATIC IMPORTED)
#set_target_properties(lcnc PROPERTIES IMPORTED_LOCATION 
#"/usr/lib/liblinuxcnc.a"
#)

#add_library(lcnchal SHARED IMPORTED)
#set_target_properties(lcnchal PROPERTIES IMPORTED_LOCATION 
#"/usr/lib/liblinuxcnchal.so"
#)

# Machinekit rt component
#add_library(control_component SHARED
#  control_component.cpp
#)
#target_link_libraries(control_component
#  machinekit
#)

add_library(control_component2 SHARED
  control_component2.cpp
)
target_link_libraries(control_component2
  machinekit
  #lcnc
  #lcnchal
)

# Main executable
add_executable(create_comp create_comp.cpp)
target_link_libraries(create_comp
  control_component2
  #lcnc
  #lcnchal
)

add_executable(cb callbacks.cpp)
target_link_libraries(cb
  #control_component22
  #lcnc
  #lcnchal
)

