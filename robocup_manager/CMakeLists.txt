cmake_minimum_required(VERSION 2.4.6)
project(robocup_manager)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)


#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
#add_message_files(
#  FILES
#
#)

## Generate services in the 'srv' folder
#add_service_files(
#  FILES
#
#)

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )
###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs
#  DEPENDS system_lib
)

find_package(Boost REQUIRED COMPONENTS  system thread)
include_directories(${Boost_INCLUDE_DIRS} include) 

add_library(
manager 

src/Controller.cpp

src/arenaState/actors/Actor.cpp
src/arenaState/actors/Machine.cpp
src/arenaState/actors/Puck.cpp
src/arenaState/actors/Robotino.cpp

src/arenaState/zones/InputStorage.cpp
src/arenaState/zones/MachineStorage.cpp
src/arenaState/zones/Zone.cpp

src/arenaState/ArenaState.cpp

src/gameState/GeneralGameStatus.cpp

src/tasks/basicTasks/GoToTask.cpp
src/tasks/basicTasks/ReportMachineTask.cpp
src/tasks/explorationTask/ExploreMachineTask.cpp
src/tasks/AbstractTask.cpp
src/tasks/ComposedTask.cpp
src/tasks/SimpleTask.cpp

src/utils/geometry_utils.cpp
)

set_target_properties(manager PROPERTIES COMPILE_FLAGS -std=c++0x)

add_executable(robocupManagerNode src/robocupManagerNode.cpp)

add_dependencies(robocupManagerNode ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  robocupManagerNode 

  manager
  ${Boost_LIBRARIES} 
  ${catkin_LIBRARIES}
  ${roscpp_LIBRARIES}
)

set_target_properties(robocupManagerNode PROPERTIES COMPILE_FLAGS -std=c++0x)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

# Mark executables and/or libraries for installation
install(TARGETS robocupManagerNode
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

