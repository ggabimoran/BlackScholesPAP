#include "../headers/option.h"
#include "../headers/heatpde1d.h"
#include "../headers/matrix.h"

#include <iostream>

int main(){
  std::cout<<""<<std::endl;
  
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

    std::cout<<'\n';

    /////////////////////////////////////////////////////////////////////
    /// testing matrix functions
    /////////////////////////////////////////////////////////////////////
    using master::FullMatrix;
    using master::TriDiag_Matrix_Sparse;
    using master::VectorColumn;
    

    FullMatrix fm{5,5};
    VectorColumn v{5};
    VectorColumn v2{5};

    fm(4,3)=1;
    fm(2,3)=3;
    fm(0,0)=2;
    fm(1,1)=3;
    fm(1,0)=3;
    fm(1,2)=2;
    fm(3,4)=3;
    fm(2,2)=5;
    fm(0,1)=5;

    v[1]=3;
    v[4]=2;
    v[2]=-1;
    v[3]=1;
    v2[0]=1;
    v2[1]=1;
    v2[2]=1;
    v2[3]=1;
    v2[4]=1;

    const TriDiag_Matrix_Sparse tm{fm};

    fm(0,4)=3;
    fm(4,0)=9;
    fm(3,0)=12;

    std::cout<<fm<<"\n";

    std::cout<<tm<<"\n";
    std::cout<<v<<"\n";
    //std::cout<<v+v2<<'\n';
    //std::cout<<v-v2<<'\n';
    std::cout<<fm*v2<<'\n';
    std::cout<<tm*v<<'\n';
  }
  catch (const char *exception) {
    std::cerr<<"Error : "<<exception<<'\n';
    return 1;
  }

  std::cout<<'\n';

  
  return 0;
}
