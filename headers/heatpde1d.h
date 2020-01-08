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
   *\class HeatPDE1D
   *\brief abstract class for one-dimensional heat partial differential
   * equation with initial condition
   */
  class HeatPDE1D{
  public:
    /**
     *\fn HeatPDE1D()
     *\brief default constructor
     */
    HeatPDE1D() {}
    /**
     *\fn ~HeatPDE1D()
     *\brief destructor
     */
    virtual ~HeatPDE1D(){}
    /**
     *\fn virtual double upper_boundary(double) const
     *\brief upper spatial boundary function
     *\param temporal
     *\return upper spatial boundary
     */
    virtual double upper_boundary(double) const = 0;
    /**
     *\fn virtual double lower_boundary(double) const
     *\brief lower spatial boundary function
     *\param temporal
     *\return lower spatial boundary
     */
    virtual double lower_boundary(double) const = 0;
    /**
     *\fn virtual double initial_boundary(double) const
     *\brief initial temporal condition 
     *\param spatial
     *\return initial temporal condition
     */
    virtual double initial_boundary(double) const = 0;
  };
  /**
   *\class CompleteBlackShcolesPDE
   *\brief class for Black Scholes partial differential equation
   */
  class CompleteBlackScholesPDE : public HeatPDE1D{
  public:
    /**
     *\fn CompleteBlackScholesPDE(const Option&)
     *\brief parameterized constructor
     *Passing parameter as a const reference insures pOption_ cannot be nullptr
     */
    CompleteBlackScholesPDE(const Option&);
    /**
     *\fn ~CompleteBlackScholesPDE()
     *\brief overrided destructor
     */
    ~CompleteBlackScholesPDE() override {}
    /**
     *\fn upper_boundary(double)
     *\brief overrided upper boundary
     */
    double upper_boundary(double) const override final;
    /**
     *\fn lower_bondary(double)
     *\brief overrided lower boundary
     */
    double lower_boundary(double) const override final;
    /**
     *\fn initial_bondary(double)
     *\brief overrided initial boundary
     */
    double initial_boundary(double) const override final;
    /**
     *\fn get_pOption()
     *\brief accessor to pOption_
     */
    const Option* get_pOption() const{return pOption_;}
  protected:
    /**
     *\var pOption_ pointer to option
     */
    const Option* pOption_;
  };
  class ReducedBlackScholesPDE : public HeatPDE1D{
  public:
    /**
     *\fn ReducedBlackScholesPDE(const Option&)
     *\brief parameterized constructor
     *Passing parameter as a const reference insures pOption_ cannot be nullptr
     */
    ReducedBlackScholesPDE(const Option&);
    /**
     *\fn ~ReducedBlackScholesPDE()
     *\brief overrided destructor
     */
    ~ReducedBlackScholesPDE() override {}
    /**
     *\fn upper_boundary(double)
     *\brief overrided upper boundary
     */
    double upper_boundary(double) const override final;
    /**
     *\fn lower_bondary(double)
     *\brief overrided lower boundary
     */
    double lower_boundary(double) const override final;
    /**
     *\fn initial_bondary(double)
     *\brief overrided initial boundary
     */
    double initial_boundary(double) const override final;
    /**
     *\fn get_pOption()
     *\brief accessor to pOption_
     */
    const Option* get_pOption() const{return pOption_;}
  protected:
    /**
     *\var pOption_ pointer to option
     */
    const Option* pOption_;
  };
}

#endif
