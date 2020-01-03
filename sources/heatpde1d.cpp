#include "../headers/math.h"
#include "../headers/heatpde1d.h"

namespace master{
  BlackScholesPDE::BlackScholesPDE(const Option& option) : pOption_{&option}{};
  CompleteBlackScholesPDE::CompleteBlackScholesPDE(const Option& option)
    : BlackScholesPDE{option} {}
  double CompleteBlackScholesPDE::upper_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->upper_spatial_time_value(t);
  }
  double CompleteBlackScholesPDE::lower_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->lower_spatial_time_value(t);
  }
  double CompleteBlackScholesPDE::terminal_boundary(double S) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->payoff(S);
  }
  ReducedBlackScholesPDE::ReducedBlackScholesPDE(const Option& option)
    : BlackScholesPDE{option} {}
  double ReducedBlackScholesPDE::upper_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_upper_spatial_time_value(t);
  }
  double ReducedBlackScholesPDE::lower_boundary(double t) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_lower_spatial_time_value(t);
  }
  double ReducedBlackScholesPDE::terminal_boundary(double S) const{
    if (pOption_==nullptr) throw "pointer to option cannot be nullptr";
    pOption_->heat_payoff(S);
  }
}
