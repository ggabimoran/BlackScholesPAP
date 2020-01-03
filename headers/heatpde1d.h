#ifndef HEATPDE1D_H
#define HEATPDE1D_H

/**
 *\file heatpde1d.h
 *\brief 
 *\authors Gabriel Moran, Julien Malfoy
 */
#include "option.h"
/**
 *\namespace master
 *\brief namespace used for project
 */
namespace master{
  /**
   *\class BackHeatPDE1D
   *\brief abstract class for one-dimensional heat partial differential
   * equation with terminal condition
   */
  class BackHeatPDE1D{
  public:
    /**
     *\fn virtual double upper_boundary(double,double) const
     *\brief upper spatial boundary function
     *\param spatial
     *\param temporal
     */
    virtual double upper_boundary(double) const = 0;
    /**
     *\fn virtual double lower_boundary(double,double) const
     *\brief lower spatial boundary function
     *\param spatial
     *\param temporal
     */
    virtual double lower_boundary(double) const = 0;
    /**
     *\fn virtual double terminal_boundary(double) const
     *\brief terminal (temporal) condition
     *\param spatial
     */
    virtual double terminal_boundary(double) const = 0;
  };
  class BlackScholesPDE : public BackHeatPDE1D{
  public:
    BlackScholesPDE(const Option&);
    virtual double upper_boundary(double) const = 0;
    virtual double lower_boundary(double) const = 0;
    virtual double terminal_boundary(double) const = 0;
    const Option* get_pOption() const{return pOption_;}
  protected:
    const Option* pOption_;
  };
  class CompleteBlackScholesPDE : public BlackScholesPDE{
  public:
    CompleteBlackScholesPDE(const Option&);
    double upper_boundary(double) const override final;
    double lower_boundary(double) const override final;
    double terminal_boundary(double) const override final;
  };
  class ReducedBlackScholesPDE : public BlackScholesPDE{
  public:
    ReducedBlackScholesPDE(const Option&);
    double upper_boundary(double) const override final;
    double lower_boundary(double) const override final;
    double terminal_boundary(double) const override final;
  };
}

#endif
