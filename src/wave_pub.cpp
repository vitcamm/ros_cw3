#include "ros/ros.h"
#include"ros_cw3/mymsg.h"
#include<cmath>
#include"boost/thread.hpp"

class SINE_WAVE{
    public:
        SINE_WAVE(double amp, double period, double Ts);
        double getAmp();
        double getPeriod();
        double getValue();
    
    private:
        double _Amp;
        double _Period;
        double _Ts;
        double _Value;
        void compute();
};

SINE_WAVE::SINE_WAVE(double amp, double period, double Ts){
    _Amp=amp;
    _Period=period;
    _Ts=Ts;
    _Value=0.0;
    boost::thread compute_t(&SINE_WAVE::compute, this);
}

double SINE_WAVE::getAmp(){
    return _Amp;
}

double SINE_WAVE::getPeriod(){
    return _Period;
}
double SINE_WAVE::getValue(){
    return _Value;
}

void SINE_WAVE::compute(){
    double time=0.0;
    while(1){
        _Value=_Amp*sin(2*(3.1415/_Period)*time);
        time+=_Ts;
        usleep(_Ts*1e6);
    }

}
int main(int argc, char** argv){

    ros::init(argc, argv, "ros_topic_pub");
    ros::NodeHandle nh;

    ros::Publisher topic_pub=nh.advertise<ros_cw3::mymsg>("/onda", 10);

    ros::Rate rate(10);
    SINE_WAVE onda(5, 5, 0.1);
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