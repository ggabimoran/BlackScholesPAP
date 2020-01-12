#include "../headers/option.h"
#include "../headers/heatpde1d.h"
#include "../headers/matrix.h"
#include "../headers/fdm.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

int main(){
  std::cout<<'\n';
  
  try{
    clock_t begin = clock();

    unsigned int N=500;
    unsigned int M=500;
    double K=100;
    double r=0.1;
    double sigma=0.1;
    double L=300;
    double T=1;
    
    using master::CallOption;
    CallOption callOption{K,T,sigma,r,L};

    using master::PutOption;
    CallOption putOption{K,T,sigma,r,L};
    
    using master::CompleteBlackScholesPDE;
    CompleteBlackScholesPDE pdeC{callOption};
    CompleteBlackScholesPDE pdeP{putOption};

    using master::FDMCrankNicholson;
    FDMCrankNicholson cnC{M,N,pdeC};
    FDMCrankNicholson cnP{M,N,pdeP};
    std::cout<<"solving complete pde...\n";
    std::cout<<"solving call option...\n";
    cnC.execute();
    std::cout<<"call option resolved\n";
    std::cout<<"solving put option...\n";
    cnP.execute();
    std::cout<<"put option solved\n";
    std::cout<<'\n';
    std::cout<<'\n';
    using master::VectorColumn;
    VectorColumn completeCallSol{cnC.get_result()};
    VectorColumn completePutSol{cnP.get_result()};
    VectorColumn assetValue{completeCallSol.get_size()};

    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    std::cout<<"\033[1;31mExecution time : \033[0m"<<time_spent<<" seconds\n";
    std::cout<<'\n';
    std::ofstream fdm_out("scilab_data/fdm.csv");
    unsigned int n=completeCallSol.get_size();
    for (int i=0;i<n;i++){
      fdm_out<<((i==0)?"compCall=[":";")<<completeCallSol[i];
    }
    fdm_out<<"]\n";
    for (int i=0;i<n;i++){
      fdm_out<<((i==0)?"putCall=[":";")<<completePutSol[i];
    }
    fdm_out<<"]\n";
    for (int j=0;j<n;j++){
      assetValue[j]=j*cnC.get_dx();
      fdm_out<<((j==0)?"assetVal=[":";")<<assetValue[j];
    }
    fdm_out<<"]\n";
    fdm_out<<"f0=scf(0);";
    fdm_out<<"plot(assetVal,compCall);";
    fdm_out<<"xlabel('Value of underlying asset');";
    fdm_out<<"ylabel('Price of option C(0,s)');";
    fdm_out<<"title('Call option price at emission for complete PDE');";

    fdm_out<<"f1=scf(1);";
    fdm_out<<"plot(assetVal,putCall);";
    fdm_out<<"xlabel('Value of underlying asset');";
    fdm_out<<"ylabel('Price of option C(0,s)');";
    fdm_out<<"title('Put option price at emission for complete PDE');";
    
    fdm_out.close();
    std::cout<<"Please enter relative path to executable scilab-adv-cli: \n";
    std::cout<<"(  for example : ~/scilab/scilab-6.0.2/bin/  )\n";
    std::string relative_path;
    std::cin>>relative_path;
    std::string command=relative_path+"scilab-adv-cli -f scilab_data/fdm.csv";
    system(command.c_str());
    }
  catch (const char *exception) {
    std::cerr<<"Error : "<<exception<<'\n';
    return 1;
  }

  std::cout<<'\n';

  
  return 0;
}
