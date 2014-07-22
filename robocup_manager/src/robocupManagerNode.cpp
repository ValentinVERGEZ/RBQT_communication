/**
 * \file 		robocupManagerNode.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#include "ros/ros.h"
#include <tf/transform_datatypes.h>

#include "Controller.h"
#include "tasks/explorationTask/ExploreMachineTask.h"
#include "tasks/basicTasks/GoToTask.h"
#include "tasks/basicTasks/ReportMachineTask.h"

int main(int argc, char** argv)
{

	ros::init(argc, argv, "robocupManagerNode");

	Controller controller("R1", 1);
/*
	ExploreMachineTask* t1 = new ExploreMachineTask(controller.getArenaState(), &controller);
	controller.addJob(t1);
	ExploreMachineTask* t2 = new ExploreMachineTask(controller.getArenaState(), &controller);
	controller.addJob(t2);
	ExploreMachineTask* t3 = new ExploreMachineTask(controller.getArenaState(), &controller);
	controller.addJob(t3);
*/
	//pose de la première machine
	geometry_msgs::Pose p1;
	p1.position.x = 0;
	p1.position.y = 1.12;
	p1.orientation = tf::createQuaternionMsgFromYaw(0);

/*
	GoToTask* t1 = new GoToTask(controller.getArenaState(), &controller, controller.getGameState(), p1);
	ROS_INFO("Robot %s assigned to task", controller.getArenaState()->getRobotino("R1")->getActorId().c_str());
	t1->assignActor(controller.getArenaState()->getRobotino("R1"));
	controller.addJob(t1);
*/

	ReportMachineTask *t2 = new ReportMachineTask(controller.getArenaState(), &controller, controller.getGameState(), "M1");
	t2->assignActor(controller.getArenaState()->getRobotino("R1"));
	controller.addJob(t2);

	sleep(1);
	controller.run();


	return 0;
}




