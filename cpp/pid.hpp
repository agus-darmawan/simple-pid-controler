#ifndef PID_H
#define PID_H

template <class T> class PID{
private:
    float _p,
          _i,
          _d;

    T   _set_point,

        current_feedback,
        current_error,
        last_error,

        integral_cumulation,
        max_integral_comulation,

        cycle_derivative,

        output_lower_bound,
        output_upper_bound;

    unsigned long last_time,
                  current_time;
    bool use_time,
         use_output_bound,
         use_max_i_cum;


        
public:
    PID(float p, float i, float d, int set_point);
    float getP(),
          getI(),
          getD();

    T   calculation(),
        getPropotional(),
        getIntegral(),
        getDerivative(),
        getIntegralCum();

    void setP(float p),
         setI(float i),
         setD(float d),
         setPID(float p, float i, float d),
         setTarget(int set_point),
         setFeedback(int feedback),
         setTime(unsigned long time),
         setMaxIntegralCum(int max_integral_cum),
         setOutputBound(int lower_bound, int upper_bound);
};
#endif
