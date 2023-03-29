#include "ros/ros.h"
#include"ros_cw3/mymsg.h"
#include"wave.h"


int main(int argc, char** argv){

    ros::init(argc, argv, "ros_topic_pub");
    ros::NodeHandle nh;
    ros::Publisher topic_pub=nh.advertise<ros_cw3::mymsg>("/onda", 10);
    ros::Rate rate(10);

    double amplitude=100;
    double period=10;
    double sampletime=0.1;

    //onda(amp, periodo, sampletime)
    SINE_WAVE onda(amplitude, period, sampletime);
    ros_cw3::mymsg msg;

    msg.name="Messaggio Custom";
    while(ros::ok()){
        msg.amp=onda.getAmp();
        msg.period=onda.getPeriod();
        msg.value=onda.getValue();

        ROS_INFO("[%f], [%f], [%f]", msg.amp, msg.period, msg.value);
        topic_pub.publish(msg);
        rate.sleep();
    }
    return 0;
}