#ifndef FDM_H
#define FDM_H

/**
 *\file fdm.h
 *\brief handles finite difference methods
 *\authors Gabriel Moran, Julien Malfoy
 */

#include "heatpde1d.h"
#include "matrix.h"
#include <vector>

/**
 *\namespace master
 *\brief namespace used for program
 */
namespace master{
  /**
   *\class FDM
   *\brief finite difference method abstract class
   */
  class FDM{
  public:
    /**
    *\fn void execute()
    *\brief fdm execution function
    */
    virtual void execute() = 0;
    VectorColumn get_result() const{return *pnew_result;}
    double get_dx() const{return dx_;}
    double get_dt() const{return dt_;}
  protected:
    /**
     *\fn FDM(unsigned long,unsigned long)
     *\brief parameterized constructor
     *\param M number of time intervals
     *\param N number of space intervals
     */
    FDM(unsigned int,unsigned int);
    /**
     *\fn ~FDM()
     *\brief destructor
     */
    virtual ~FDM();
    /**
     *\var minx_,maxx_ space interval min and max
     *\var mint_,maxt_ time interval min and max
     *\var dx_,dt_ space and time interval length
     */
    double minx_,maxx_,mint_,maxt_,dx_,dt_;
    /**
     *\var M_ number of time intervals
     *\var N_ number of space intervals
     */
    unsigned int  M_,N_;
    /**
     *\var pnew_result latest iteration result for pde approximation
     *\var pold_result previous iteration result for pde approximation
     */
    VectorColumn *pnew_result,*pold_result;
  };
  /**
   *\class FDMImplicit
   *\brief class implementing implicit method
   */
  class FDMImplicit : public FDM{
  public:
    FDMImplicit(unsigned int,unsigned int,const ReducedBlackScholesPDE& rpde);
    /**
     *\fn ~FDMImplicit()
     *\brief overrided destructor
     */
    ~FDMImplicit() override;
    /**
     *\fn execute()
     *\brief overrided execute()
     */
    void execute() override final;
  private:
    /**
     *\var pointer to pde object
     */
    const ReducedBlackScholesPDE *ppde_;
    /**
     *\var lambda_ implicit parameters
     */
    std::vector<double> lambda_;
    /**
     *\var pointers to implicit matrice and vector
     */
    TriDiag_Matrix_Sparse *pA;
    VectorColumn *pb;
  };
  /**
   *\class FDMCrankNicholson
   *\brief class implementing Crank-Nicholson method
   */
  class FDMCrankNicholson : public FDM{
  public:
    /**
     *\fn FDMCrankNicholson()
     *\brief parameterized constructor
     *\param M_ number of time intervals
     *\param N_ number of space intervals
     *\param black scholes object
     */
    FDMCrankNicholson(unsigned int,unsigned int,const CompleteBlackScholesPDE& rpde);
    /**
     *\fn ~FDMCrankNicholson()
     *\brief overrided destructor
     */
    ~FDMCrankNicholson() override;
    /**
     *\fn execute()
     *\brief overrided execute()
     */
    void execute() override final;
  private:
    /**
     *\var pointer to pde object
     */
    const CompleteBlackScholesPDE *ppde_;
    /**
     *\var theta_,gamma_ Crank-Nicholson parameters
     */
    double theta_,gamma_;
    /**
     *\var pointers to Crank-Nicholson matrices and vector
     */
    TriDiag_Matrix_Sparse *pA,*pB;
    VectorColumn *pb;
  };
}

#endif
