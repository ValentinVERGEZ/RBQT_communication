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

#set(LLSF_BASEDIR /home/vincent/refbox/llsf-refbox-crypto)
set(LLSF_BASEDIR $ENV{HOME}/refbox/llsf-refbox)
#set(CONFDIR ${LLSF_BASEDIR}/cfg)
set(CONFDIR ${PROJECT_SOURCE_DIR}/cfg)

add_definitions( -DCONFDIR=\\"${CONFDIR}\\" )
add_definitions( -DUSERDIR=\\".\\" )
add_definitions( -DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG)

include_directories(${LLSF_BASEDIR}/src/libs ${roscpp_INCLUDE_DIRS})
include_directories(${LLSF_BASEDIR}/src ${roscpp_INCLUDE_DIRS})

link_directories(${LLSF_BASEDIR}/lib)
link_directories(${LLSF_BASEDIR}/lib/protobuf)

rosbuild_add_boost_directories()

rosbuild_add_library(refBoxTransport src/refBoxTransport.cpp)

rosbuild_add_executable(
  refBoxComm 
  src/refBoxCommNode.cpp 
)

rosbuild_add_executable(
  eiListener
  src/explorationInfoListenerNode.cpp 
)


target_link_libraries(
  refBoxComm 

  refBoxTransport
  llsf_msgs
  llsf_protobuf_comm 
  protobuf 
  llsfrbconfig
  llsfrbcore
  llsfrbutils
  yaml-cpp
  
  ${roscpp_LIBRARIES}
  
)

target_link_libraries( 
  eiListener
  ${roscpp_LIBRARIES}
)

rosbuild_add_compile_flags(refBoxTransport -std=c++0x)
rosbuild_add_compile_flags(refBoxComm -std=c++0x)

rosbuild_link_boost(refBoxComm system)

