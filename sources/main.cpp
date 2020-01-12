#include "../headers/option.h"
#include "../headers/heatpde1d.h"
#include "../headers/matrix.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

int main(){
  std::cout<<'\n';
  
  try{
    using master::VectorColumn;
    VectorColumn v{5};
    v[0]=2.34;
    v[1]=1.69;
    v[2]=5.23;
    v[3]=6.43;
    v[4]=3.3;
    std::ofstream fdm_out("scilab_data/fdm.csv");
    unsigned int n=v.get_size();
    for (int i=0;i<n;i++){
      fdm_out<<((i==0)?"v=[":";")<<v[i];
    }
    fdm_out<<"]\n";
    fdm_out<<"plot(v)";
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
