#include "pid.hpp"

template<class T> 
PID<T>::PID(float p, float i, float d, int set_point){
    _p = p;
    _i = i;
    _d = d;
    _set_point = set_point;

    last_error = 0;
    last_time = 0;
    integral_cumulation = 0;

    use_time = false;
    use_output_bound = false;
    use_max_i_cum = false;
}

template<class T> T PID<T>::calculation(){
    current_error = _set_point - current_feedback;
    if(use_time){
        long delta_time = current_time - last_time;
        int cycle_integral = (last_error + current_error / 2) * delta_time;
        integral_cumulation += cycle_integral;
        cycle_derivative = (current_error - last_error) / delta_time;
        last_time = current_time;
    }
    else{
        integral_cumulation += current_error;
        cycle_derivative = current_error - last_error;
    }    
    if(use_max_i_cum){
        if(integral_cumulation > max_integral_comulation){
            integral_cumulation = max_integral_comulation;
        }
        else if(integral_cumulation < -max_integral_comulation){
            integral_cumulation = -max_integral_comulation;
        }
    }
    
    
    int output = (current_error * _p) + (integral_cumulation * _i) + (cycle_derivative * _d);
    if(use_output_bound){
        if (output > output_upper_bound){
            output = output_upper_bound;
        }
        else if (output < output_lower_bound){
            output = output_lower_bound;
        }
    }

    last_error = current_error;
    return output;
}


template<class T> float PID<T>::getP(){
    return _p;
}
template<class T> float PID<T>::getI(){
    return _i;
}
template<class T> float PID<T>::getD(){
    return _d;
}
template<class T> T PID<T>::getPropotional(){
    return current_error * _p;
}
template<class T> T PID<T>::getIntegral(){
    return integral_cumulation * _i;
}
template<class T> T PID<T>::getDerivative(){
    return cycle_derivative * _d;
}
template<class T> T PID<T>::getIntegralCum(){
    return integral_cumulation;
}

template<class T> void PID<T>::setP(float p){
    _p = p;
}
template<class T> void PID<T>::setI(float i){
    _i = i;
}
template<class T> void PID<T>::setD(float d){
    _d = d;
}
template<class T> void PID<T>::setTarget(int set_point){
    set_point = set_point;
}
template<class T> void PID<T>::setPID(float p, float i, float d){
    _p = p;
    _i = i;
    _d = d;
}
template<class T> void PID<T>::setFeedback(int feedback){
    current_feedback = feedback;
}
template<class T> void PID<T>::setTime(unsigned long time){
    current_time = time;
}
template<class T> void PID<T>::setMaxIntegralCum(int max_integral_cum){
    max_integral_comulation = max_integral_cum;
}
template<class T> void PID<T>::setOutputBound(int lower_bound, int upper_bound){
    output_lower_bound = lower_bound;
    output_upper_bound = upper_bound;
}

template class PID<int>;
template class PID<long>;
template class PID<float>;
template class PID<double>;
