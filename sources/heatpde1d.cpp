#include "../headers/math.h"
#include "../headers/heatpde1d.h"

namespace master{
  CompleteBlackScholesPDE::CompleteBlackScholesPDE(const Option& option)
    : pOption_{&option} {}
  double CompleteBlackScholesPDE::upper_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->upper_spatial_time_value(t);
  }
  double CompleteBlackScholesPDE::lower_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->lower_spatial_time_value(t);
  }
  double CompleteBlackScholesPDE::initial_boundary(double S) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->payoff(S);
  }
  ReducedBlackScholesPDE::ReducedBlackScholesPDE(const Option& option)
    : pOption_{&option} {}
  double ReducedBlackScholesPDE::upper_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_upper_spatial_time_value(t);
  }
  double ReducedBlackScholesPDE::lower_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_lower_spatial_time_value(t);
  }
  double ReducedBlackScholesPDE::initial_boundary(double S) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_payoff(S);
  }
}
