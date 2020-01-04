#include "../headers/math.h"

#include <iostream>

int main(){
  std::cout<<""<<std::endl;
  /////////////////////////////////////////////////////////////////////
  /// testing math functions
  /////////////////////////////////////////////////////////////////////
  using master::Math;
  std::cout<<"max(5,3) = "<<Math::max(5,3)<<std::endl;
  std::cout<<"max(0,0) = "<<Math::max(0,0)<<std::endl;
  std::cout<<"max(-345.7,9876.2) = "<<Math::max(-345.7,9876.2)<<std::endl;
  std::cout<<"max(-5.5,-3.3) = "<<Math::max(-5.5,-3.3)<<std::endl;
  std::cout<<"max(1,4) = "<<Math::max(1,4)<<std::endl;

  std::cout<<""<<std::endl;

  std::cout<<"abs(5) = "<<Math::abs(5)<<std::endl;
  std::cout<<"abs(-155000000) = "<<Math::abs(-155000000)<<std::endl;
  std::cout<<"abs(358.235455) = "<<Math::abs(358.235455)<<std::endl;
  std::cout<<"abs(-454545) = "<<Math::abs(-454545)<<std::endl;
  std::cout<<"abs(0.) = "<<Math::abs(0.)<<std::endl;

  std::cout<<""<<std::endl;

  std::cout<<"fact(5) = "<<Math::fact(5)<<std::endl;
  std::cout<<"fact(0) = "<<Math::fact(0)<<std::endl;
  std::cout<<"fact(1) = "<<Math::fact(1)<<std::endl;
  std::cout<<"fact(9) = "<<Math::fact(9)<<std::endl;
  std::cout<<"fact(3) = "<<Math::fact(3)<<std::endl;

  std::cout<<""<<std::endl;

  std::cout<<"pow(0.,0) = "<<Math::pow(0.,0)<<std::endl;
  std::cout<<"pow(0,1) = "<<Math::pow(0,1)<<std::endl;
  std::cout<<"pow(2.,3) = "<<Math::pow(2.,3)<<std::endl;
  std::cout<<"pow(-1,3) = "<<Math::pow(-1,3)<<std::endl;
  std::cout<<"pow(0.8,2) = "<<Math::pow(0.8,2)<<std::endl;


  std::cout<<""<<std::endl;

  std::cout<<"exp(0.) = "<<Math::exp(0.)<<std::endl;
  std::cout<<"exp(1.) = "<<Math::exp(1.)<<std::endl;
  std::cout<<"exp(0.5) = "<<Math::exp(0.5)<<std::endl;
  std::cout<<"exp(-1.) = "<<Math::exp(-1.)<<std::endl;
  std::cout<<"exp(-0.5) = "<<Math::exp(-0.5)<<std::endl;

  
  std::cout<<""<<std::endl;
  return 0;
}
