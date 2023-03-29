#include"ros/ros.h"
#include"ros_cw3/mymsg.h"
#include"ros_cw3/filtered.h"
#include"boost/thread.hpp"
#include<cmath>



class FILTER_NODE{
    public:
    FILTER_NODE(double cutoff, double ts);
    void topic_cb(ros_cw3::mymsg::ConstPtr);
	void filter();
	void publish();
	double getSignal();


    private:
    ros::NodeHandle _nh;
    ros::Subscriber _sub;
	double _Cutoff;
	double _Fromsub;
	double _ToPub;
	double _Ts;
	ros_cw3::filtered _msg;
};

FILTER_NODE::FILTER_NODE(double cutoff, double ts){
    _sub=_nh.subscribe("/onda", 1, &FILTER_NODE::topic_cb, this);
	_ToPub=0.0;
	_Fromsub=0.0;
	_Cutoff=cutoff;
	_Ts=ts;
	_msg.name="Filtered signal";
	_msg.signal=0.0;
	boost::thread filter_loop(&FILTER_NODE::filter, this);
	boost::thread pub_t(&FILTER_NODE::publish, this);
}

void FILTER_NODE::topic_cb(ros_cw3::mymsg::ConstPtr data) {
	ROS_INFO("value: %f", data->value);
	_Fromsub=data->value;
}

void FILTER_NODE::filter(){
	double old=0.0;
	double w_c=2*M_PI*_Cutoff;
	while(1){
		old=_ToPub;
		_ToPub=old*(1-_Ts*w_c)+_Ts*w_c*_Fromsub;
		usleep(_Ts*1e6);
	}
}


void FILTER_NODE::publish(){
	ros::Publisher pub;
	pub=_nh.advertise<ros_cw3::filtered>("/filtro", 10);
	ros::Rate rate(10);
	while(ros::ok()){
		_msg.signal=_ToPub;
		pub.publish(_msg);
		rate.sleep();
	}
}

int main( int argc, char** argv ) {
	double sampletime=0.01;
	double freqcutoff=0.01;
	
	ros::init(argc, argv, "ros_filter");

	//Filter node(cutoff, sample time)
	FILTER_NODE rs(freqcutoff, sampletime);
	
	ros::spin();
	return 0;
}