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
