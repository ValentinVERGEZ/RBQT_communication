cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

###################################
## catkin specific configuration ##
###################################
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs
#  DEPENDS system_lib
)

rosbuild_add_boost_directories()

rosbuild_add_library(
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
rosbuild_add_compile_flags(manager -std=c++0x)

rosbuild_add_executable(robocupManagerNode src/robocupManagerNode.cpp)
target_link_libraries(robocupManagerNode manager)
rosbuild_add_compile_flags(robocupManagerNode -std=c++0x)


rosbuild_link_boost(robocupManagerNode system thread)

