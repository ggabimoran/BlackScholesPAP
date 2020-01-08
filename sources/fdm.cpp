#include "../headers/fdm.h"
#include "../headers/math.h"

namespace master{
  FDM::FDM(unsigned int M,unsigned int N)
    : M_{M},N_{N},minx_{0.},mint_{0.},maxx_{0.},maxt_{0.},dx_{0.},dt_{0.},
      pnew_result{nullptr},
      pold_result{nullptr}{
	VectorColumn new_result{N-1};
	VectorColumn old_result{N-1};
	pnew_result=&new_result;
	pold_result=&old_result;
      }
  FDMImplicit::FDMImplicit(unsigned int M,unsigned int N,const ReducedBlackScholesPDE& rpde)
    : FDM{M,N},ppde_{&rpde},lambda_{0.},pA{nullptr},pb{nullptr}
  {
    if (ppde_->get_pOption()==nullptr) throw "pointer to option cannot be nullptr";
    maxx_=ppde_->get_pOption()->get_L();
    maxt_=ppde_->get_pOption()->get_T();
    dx_=maxx_/N;
    dt_=maxt_/M;
    lambda_=dt_/Math::pow(dx_,2);//time c squared to be determined
    Square_Matrix_Sparse A{N-1};
    pA=&A;
    VectorColumn_Sparse b{N-1};
    pb=&b;
  }
  void FDMImplicit::initialize_matrices(){
    //initialization of A
    for (unsigned int i=0;i<pA->get_nl();i++){
      (*pA)(i,i) = 1-2*lambda_;
      if (i>0) (*pA)(i-1,i) = -lambda_;
      if (i<(pA->get_nl()-1)) (*pA)(i+1,i) = -lambda_;
    }
    //initialization of u^n+1
    for (unsigned int j=0;j<pold_result->get_nl();j++) {
      (*pold_result)[j]=ppde_->initial_boundary(minx_+(j+1)*dx_);
    }
    //initialization of b
    (*pb)[0] = -lambda_*ppde_->lower_boundary(maxt_);
    (*pb)[N_-2] = -lambda_*ppde_->upper_boundary(maxt_);
  }
  void FDMImplicit::execute(){
    initialize_matrices();
    double curr_t=maxt_;
    double prev_t=maxt_;
    while (curr_t>0){
      prev_t = curr_t;
      curr_t -= dt_;
      (*pb)[0] = -lambda_*ppde_->lower_boundary(curr_t);
      (*pb)[N_-2] = -lambda_*ppde_->upper_boundary(curr_t);
      VectorColumn tempvect = *pnew_result;
      *pnew_result = pA->inv() * (*pold_result - *pb);
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
    gamma_=Math::pow(ppde_->get_pOption()->get_sigma(),2)*dt_;
    Square_Matrix_Sparse A{N-1};
    pA=&A;
    Square_Matrix_Sparse B{N-1};
    pB=&B;
    VectorColumn_Sparse b{N-1};
    pb=&b;
  }
  void FDMCrankNicholson::initialize_matrices(){
    //initialization of A
    for (unsigned int i=0;i<pA->get_nl();i++){
      (*pA)(i,i) = -1-theta_/2;
      if (i>0) (*pA)(i-1,i) = i*theta_/4;
      if (i<(pA->get_nl()-1)) (*pA)(i+1,i) = -i*theta_/4;
    }
    //initialization of B
    for (unsigned int j=0;j<pB->get_nl();j++){
      (*pB)(j,j) = theta_/2-1+gamma_*Math::pow(j,2);
      if (j>0) (*pB)(j-1,j) = -theta_/4*j-gamma_/2*Math::pow(j,2);
      if (j<(pB->get_nl()-1)) (*pB)(j+1,j) = theta_/4*j-gamma_*Math::pow(j,2);
    }
    //initialization of u^n+1
    for (unsigned int k=0;k<pold_result->get_nl();k++) {
      (*pold_result)[k]=ppde_->initial_boundary(minx_+(k+1)*dx_);
    }
    //initialization of b
    (*pb)[N_-2] = theta_/4*N_*ppde_->upper_boundary(maxt_)+(theta_/4*N_* + gamma_/2 * Math::pow(N_,2))*ppde_->upper_boundary(maxt_-dt_);   
  }
  void FDMCrankNicholson::execute(){
    initialize_matrices();
    double curr_t=maxt_;
    double prev_t=maxt_;
    while (curr_t>0){
      prev_t = curr_t;
      curr_t -= dt_;
      (*pb)[N_-2] = theta_/4*N_*ppde_->upper_boundary(prev_t)+(theta_/4*N_* + gamma_/2 * Math::pow(N_,2))*ppde_->upper_boundary(curr_t); ;
      VectorColumn tempvect = *pnew_result;
      *pnew_result = pB->inv() * ((*pA * *pold_result) + *pb);
      *pold_result = tempvect;
    }
  }
}
