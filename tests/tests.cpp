#include "../headers/math.h"
#include "../headers/option.h"
#include "../headers/heatpde1d.h"

#include <iostream>

int main(){
  std::cout<<""<<std::endl;
  /////////////////////////////////////////////////////////////////////
  /// testing math functions
  /////////////////////////////////////////////////////////////////////
  using master::Math;
  std::cout<<"max(5,3) = "<<Math::max(5,3)<<'\n';
  std::cout<<"max(0,0) = "<<Math::max(0,0)<<'\n';
  std::cout<<"max(-345.7,9876.2) = "<<Math::max(-345.7,9876.2)<<'\n';
  std::cout<<"max(-5.5,-3.3) = "<<Math::max(-5.5,-3.3)<<'\n';
  std::cout<<"max(1,4) = "<<Math::max(1,4)<<'\n';

  std::cout<<'\n';

  std::cout<<"abs(5) = "<<Math::abs(5)<<'\n';
  std::cout<<"abs(-155000000) = "<<Math::abs(-155000000)<<'\n';
  std::cout<<"abs(358.235455) = "<<Math::abs(358.235455)<<'\n';
  std::cout<<"abs(-454545) = "<<Math::abs(-454545)<<'\n';
  std::cout<<"abs(0.) = "<<Math::abs(0.)<<'\n';

  std::cout<<'\n';

  std::cout<<"fact(5) = "<<Math::fact(5)<<'\n';
  std::cout<<"fact(0) = "<<Math::fact(0)<<'\n';
  std::cout<<"fact(1) = "<<Math::fact(1)<<'\n';
  std::cout<<"fact(9) = "<<Math::fact(9)<<'\n';
  std::cout<<"fact(3) = "<<Math::fact(3)<<'\n';

  std::cout<<'\n';

  std::cout<<"pow(0.,0) = "<<Math::pow(0.,0)<<'\n';
  std::cout<<"pow(0,1) = "<<Math::pow(0,1)<<'\n';
  std::cout<<"pow(2.,3) = "<<Math::pow(2.,3)<<'\n';
  std::cout<<"pow(-1,3) = "<<Math::pow(-1,3)<<'\n';
  std::cout<<"pow(0.8,2) = "<<Math::pow(0.8,2)<<'\n';


  std::cout<<'\n';

  std::cout<<"exp(0.) = "<<Math::exp(0.)<<'\n';
  std::cout<<"exp(1.) = "<<Math::exp(1.)<<'\n';
  std::cout<<"exp(0.5) = "<<Math::exp(0.5)<<'\n';
  std::cout<<"exp(-1.) = "<<Math::exp(-1.)<<'\n';
  std::cout<<"exp(-0.5) = "<<Math::exp(-0.5)<<'\n';

  
  std::cout<<'\n';
  
  
  try{
    /////////////////////////////////////////////////////////////////////
    /// testing option functions
    /////////////////////////////////////////////////////////////////////
    using master::CallOption;
    using master::PutOption;
    std::cout<<"CallOption callOption{100,1,0.1,0.1,300}\n";
    CallOption callOption{100,1,0.1,0.1,300};
    std::cout<<"callOption.get_K() : "<<callOption.get_K()<<'\n';
    std::cout<<"callOption.get_T() : "<<callOption.get_T()<<'\n';
    std::cout<<"callOption.get_sigma() : "<<callOption.get_sigma()<<'\n';
    std::cout<<"callOption.get_r() : "<<callOption.get_r()<<'\n';
    std::cout<<"callOption.get_L() : "<<callOption.get_L()<<'\n';
    std::cout<<"callOption.get_alpha() : "<<callOption.get_alpha()<<'\n';
    std::cout<<"callOption.get_beta() : "<<callOption.get_beta()<<'\n';
    std::cout<<"callOption.payoff(150) : "<<callOption.payoff(150)<<'\n';
    std::cout<<"callOption.payoff(50) : "<<callOption.payoff(50)<<'\n';
    std::cout<<"callOption.upper_spatial_time_value(0.5) : "<<callOption.upper_spatial_time_value(0.5)<<'\n';
    std::cout<<"callOption.upper_spatial_time_value(0) : "<<callOption.upper_spatial_time_value(0)<<'\n';
    std::cout<<"callOption.upper_spatial_time_value(1) : "<<callOption.upper_spatial_time_value(1)<<'\n';
    std::cout<<"callOption.lower_spatial_time_value(0.5) : "<<callOption.lower_spatial_time_value(0.5)<<'\n';
    std::cout<<"PutOption putOption{100,1,0.1,0.1,300}\n";
    PutOption putOption{100,1,0.1,0.1,300};
    std::cout<<"putOption.payoff(150) : "<<putOption.payoff(150)<<'\n';
    std::cout<<"putOption.payoff(50) : "<<putOption.payoff(50)<<'\n';
    std::cout<<"putOption.upper_spatial_time_value(0.5) : "<<putOption.upper_spatial_time_value(0.5)<<'\n';
    std::cout<<"putOption.lower_spatial_time_value(0) : "<<putOption.lower_spatial_time_value(0)<<'\n';
    std::cout<<"putOption.lower_spatial_time_value(1) : "<<putOption.lower_spatial_time_value(1)<<'\n';
    std::cout<<"putOption.lower_spatial_time_value(0.5) : "<<putOption.lower_spatial_time_value(0.5)<<'\n';

    std::cout<<'\n';

    /////////////////////////////////////////////////////////////////////
    /// testing heatpde1d functions
    /////////////////////////////////////////////////////////////////////

    using master::CompleteBlackScholesPDE;

    std::cout<<"CompleteBlackScholesPDE pdeC{callOption}\n";
    CompleteBlackScholesPDE pdeC{callOption};
    std::cout<<"pdeC.upper_boundary(0.5) : "<<pdeC.upper_boundary(0.5)<<'\n';
    std::cout<<"pdeC.initial_boundary(150) : "<<pdeC.initial_boundary(150)<<'\n';
    std::cout<<"pdeC.lower_boundary(0.5) : "<<pdeC.lower_boundary(0.5)<<'\n';
    std::cout<<"pdeC.get_pOption() == &callOption : "<<(pdeC.get_pOption() == &callOption)<<'\n';
  }
  catch (const char *exception) {
    std::cerr<<"Error : "<<exception<<'\n';
    return 1;
  }

  std::cout<<'\n';

  
  return 0;
}
