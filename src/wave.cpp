
#include"wave.h"


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