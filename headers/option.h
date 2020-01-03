#ifndef OPTION_H
#define OPTION_H

/**
 *\file option.h
 *\brief Handles option
 *\authors Gabriel Moran, Julien Malfoy
 */

/**
 *\namespace master
 *\brief namespace used for project
 */
namespace master{
  /**
   *\class Option
   *\brief class representing the option object
   */
  class Option{
  public:
    Option(double,double,double,double,double);
    virtual ~Option(){};
    double get_K() const{return K_;}
    double get_T() const{return T_;}
    double get_sigma() const{return sigma_;}
    double get_r() const{return r_;}
    double get_L() const{return L_;}
    virtual double payoff(double) const = 0;
    virtual double upper_spatial_time_value(double) const=0;
    virtual double lower_spatial_time_value(double) const=0;
    virtual double heat_payoff(double) const = 0;
    virtual double heat_upper_spatial_time_value(double) const=0;
    virtual double heat_lower_spatial_time_value(double) const=0;
  protected:
    double K_,T_,sigma_,r_,L_;
  };
  class CallOption : public Option{
    CallOption(double,double,double,double,double);
    ~CallOption() override{};
    double payoff(double) const override final;
    double upper_spatial_time_value(double) const override final;
    double lower_spatial_time_value(double) const override final;
    double heat_payoff(double) const override final;
    double heat_upper_spatial_time_value(double) const override final;
    double heat_lower_spatial_time_value(double) const override final;
  };
  class PutOption : public Option{
    PutOption(double,double,double,double,double);
    ~PutOption() override{};
    double payoff(double) const override final;
    double upper_spatial_time_value(double) const override final;
    double lower_spatial_time_value(double) const override final;
    double heat_payoff(double) const override final;
    double heat_upper_spatial_time_value(double) const override final;
    double heat_lower_spatial_time_value(double) const override final;
  };
}

#endif
