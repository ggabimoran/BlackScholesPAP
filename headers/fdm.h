#ifndef FDM_H
#define FDM_H

#include "heatpde1d.h"
#include "matrix.h"

namespace master{
  class FDM{
  public:
     virtual void execute() = 0;
  protected:
    FDM(unsigned long,unsigned long);
    double minx_,maxx_,mint_,maxt_,dx_,dt_;
    unsigned long M_,N_;
    VectorColumn* pnew_result;
    VectorColumn* pold_result;
    virtual void initialize_matrices() = 0;
  };
  class FDMImplicit : public FDM{
  public:
    FDMImplicit(unsigned long,unsigned long,const ReducedBlackScholesPDE& rpde);
    void execute() override final;
  private:
    const ReducedBlackScholesPDE *ppde_;
    double lambda_;
    Square_Matrix_Sparse *pA;
    VectorColumn_Sparse *pb;
    void initialize_matrices() override final;
  };
  class FDMCrankNicholson : public FDM{
  public:
    FDMCrankNicholson(unsigned long,unsigned long,const CompleteBlackScholesPDE& rpde);
    void execute() override final;
  private:
    const CompleteBlackScholesPDE *ppde_;
    double theta_,gamma_;
    Square_Matrix_Sparse *pA,*pB;
    VectorColumn_Sparse *pb;
    void initialize_matrices() override final;
  };
}

#endif
