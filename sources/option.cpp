#include "../headers/math.h"
#include "../headers/option.h"

namespace master{
  Option::Option(double K,double T,double sigma,double r,double L)
    : K_{K},T_{T},sigma_{sigma},r_{r},L_{L}
  {
    if (K <= 0) throw "strike must be strictly positive";
    if (K >= L) throw "max value L of underlying asset must be greater than K";
    if (T <= 0) throw "time to maturity must be strictly positive";
    if (sigma < 0) throw "volatility sigma must be positive";
    if (Math::abs(r)>=1) throw "risk-free interest rate must be less than 1 in absolute value";
  }
  CallOption::CallOption(double K,double T,double sigma,double r,double L)
    : Option(K,T,sigma,r,L) {}
  double CallOption::payoff(double S) const{
    if (S<0) throw "asset S must have positive value";
    return Math::max(S-K_,0.);
  }
  double CallOption::upper_spatial_time_value(double t) const{
    if (t<0||t>T_) throw "time t must be valid";
    return L_-K_*Math::exp(-r_*(T_-t));
  }
  double CallOption::lower_spatial_time_value(double t) const{
    if (t<0||t>T_) throw "time t must be valid";
    return 0;
  }
  PutOption::PutOption(double K,double T,double sigma,double r,double L)
    : Option(K,T,sigma,r,L) {}
  double PutOption::payoff(double S) const{
    if (S<0) throw "asset S must have positive value";
    return Math::max(K_-S,0.);
  }
  double PutOption::upper_spatial_time_value(double t) const{
    if (t<0||t>T_) throw "time t must be valid";
    return 0;
  }
  double PutOption::lower_spatial_time_value(double t) const{
    if (t<0||t>T_) throw "time t must be valid";
    return K_*Math::exp(-r_*(T_-t));
  }
}
