#include"ros/ros.h"
#include"ros_cw3/mymsg.h"

class ROS_SUB{
    public:
    ROS_SUB();
    void topic_cb(ros_cw3::mymsg::ConstPtr);

    private:
    ros::NodeHandle _nh;
    ros::Subscriber _sub;

};

ROS_SUB::ROS_SUB(){
    _sub=_nh.subscribe("/onda", 10, &ROS_SUB::topic_cb, this);
}

void ROS_SUB::topic_cb( ros_cw3::mymsg::ConstPtr data) {

	//data is a pointer of std_msgs::Int32 type
	//	to access to its fiel, the "." can not be used
	ROS_INFO("value: %f", data->value);
}

int main( int argc, char** argv ) {

	//Init the ros node with ros_subscriber name
	ros::init(argc, argv, "ros_subscriber");

	//Create the ROS_SUB class object
	ROS_SUB rs;
	
	
	ros::spin(); 

	

	return 0;
}