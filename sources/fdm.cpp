#include "../headers/fdm.h"
#include <cmath>

namespace master{
  FDM::FDM(unsigned int M,unsigned int N)
    : M_{M},N_{N},minx_{0.},mint_{0.},maxx_{0.},maxt_{0.},dx_{0.},dt_{0.},
      pnew_result{nullptr},
      pold_result{nullptr}{
	pnew_result=new VectorColumn{N-1};
	pold_result=new VectorColumn{N-1};
      }
  FDM::~FDM(){
    delete pnew_result;
    delete pold_result;
  }
  FDMImplicit::FDMImplicit(unsigned int M,unsigned int N,const ReducedBlackScholesPDE& rpde)
    : FDM{M,N},ppde_{&rpde},lambda_{0.},pA{nullptr},pb{nullptr}
  {
    if (ppde_->get_pOption()==nullptr) throw "pointer to option cannot be nullptr";
    maxx_=ppde_->get_pOption()->get_L();
    maxt_=ppde_->get_pOption()->get_T();
    dx_=maxx_/N;
    dt_=maxt_/M;
    for (int k=0;k<N_-1;k++){
      lambda_.push_back(-std::pow(ppde_->get_pOption()->get_sigma(),2)/2 * dt_/std::pow(std::log((k+2)/(k+1)),2));
    }
    //initialization of A
    FullMatrix A{N_-1,N_-1};
    for (unsigned int i=0;i<A.get_nl();i++){
      A(i,i) = 1+2*lambda_[i];
      if (i>0) A(i-1,i) = -lambda_[i-1];
      if (i<(A.get_nl()-1)) A(i+1,i) = -lambda_[i+1];
    }
    pA=new TriDiag_Matrix_Sparse{A};
    //initialization of u^n+1
    for (unsigned int j=0;j<N_-1;j++) {
      (*pold_result)[j]=ppde_->initial_boundary(minx_+(j+1)*dx_);
    }
    //initialization of b
    pb=new VectorColumn{N_-1};
    (*pb)[0] = -lambda_[0]*ppde_->lower_boundary(maxt_);
    (*pb)[N_-2] = -lambda_[N_-2]*ppde_->upper_boundary(maxt_);
  }
  FDMImplicit::~FDMImplicit(){
    delete pA;
    delete pb;
  }
  void FDMImplicit::execute(){
    double curr_t=maxt_;
    double prev_t=maxt_;
    while (curr_t>dt_){
      prev_t = curr_t;
      curr_t -= dt_;
      (*pb)[0] = -lambda_[0]*ppde_->lower_boundary(curr_t);
      (*pb)[N_-2] = -lambda_[N_-2]*ppde_->upper_boundary(curr_t);
      VectorColumn tempvect = *pnew_result;
      *pnew_result = resolutionLUTriDiag(*pA,(*pold_result)-(*pb));
      *pold_result = tempvect;
    }
  }
  FDMCrankNicholson::FDMCrankNicholson(unsigned int M,unsigned int N,const CompleteBlackScholesPDE& rpde)
    : FDM{M,N},ppde_{&rpde},theta_{0.},gamma_{0.},pA{nullptr},pB{nullptr},
      pb{nullptr}
  {
    if (ppde_->get_pOption()==nullptr) throw "pointer to option cannot be nullptr";
    maxx_=ppde_->get_pOption()->get_L();
    maxt_=ppde_->get_pOption()->get_T();
    dx_=maxx_/N;
    dt_=maxt_/M;
    theta_=ppde_->get_pOption()->get_r()*dt_;
    gamma_=std::pow(ppde_->get_pOption()->get_sigma(),2)*dt_;
    //initialization of A
    FullMatrix A{N_-1,N_-1};
    for (unsigned int i=0;i<A.get_nl();i++){
      A(i,i) = 1-theta_/2;
      if (i>0) A(i-1,i) = i*theta_/4;
      if (i<(A.get_nl()-1)) A(i+1,i) = -(static_cast<int>(i)+2)*theta_/4;
    }
    pA=new TriDiag_Matrix_Sparse{A};
    //initialization of B
    FullMatrix B{N_-1,N_-1};
    for (unsigned int j=0;j<B.get_nl();j++){
      B(j,j) = theta_/2+1+gamma_*std::pow(j+1,2);
      if (j>0) B(j-1,j) = -(j*theta_/4+gamma_*std::pow(j,2)/2);
      if (j<(B.get_nl()-1)) B(j+1,j) = (j+2)*theta_/4-gamma_*std::pow(j+2,2)/2;
    }
    pB=new TriDiag_Matrix_Sparse{B};
    //initialization of u^n+1
    for (unsigned int k=0;k<N_-1;k++) {
      (*pold_result)[k]=ppde_->initial_boundary(minx_+(k+1)*dx_);
    }
    //initialization of b
    pb=new VectorColumn{N_-1};
    (*pb)[N_-2] = theta_/4*(N_-1)*ppde_->upper_boundary(maxt_)+(theta_/4*(N_-1) + gamma_/2 * std::pow(N_-1,2))*ppde_->upper_boundary(maxt_-dt_);
  }
  FDMCrankNicholson::~FDMCrankNicholson(){
    delete pA;
    delete pB;
    delete pb;
  }
  void FDMCrankNicholson::execute(){
    double curr_t=maxt_;
    double prev_t=maxt_;
    while (curr_t>dt_){
      prev_t = curr_t;
      curr_t -= dt_;
      (*pb)[N_-2] = theta_/4*(N_-1)*ppde_->upper_boundary(prev_t)+(theta_/4*(N_-1)+ gamma_/2 * std::pow(N_-1,2))*ppde_->upper_boundary(curr_t); ;
      VectorColumn tempvect = *pnew_result;
      *pnew_result = resolutionLUTriDiag(*pB,(((*pA) * (*pold_result)))+(*pb));
      *pold_result = tempvect;
    }
  }
}
