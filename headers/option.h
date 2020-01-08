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
   *\brief abstract class representing the option object 
   *
   *Contains option parameters, payoff as well as upper and
   *lower spatial time value (time value of the spatial boundaries) BOTH for
   *the option price AND heat value (for when the Black-Scholes equation is 
   *transformed to the heat equation)
   */
  class Option{
  public:
    /**
     *\fn Option(double,double,double,double,double)
     *\brief parameterized constructor
     *\param doubles K,T,sigma,r,L
     *Initializes option parameters, throws const char * exceptions 
     *when arguments do not conform to parameter characteristics
     */
    Option(double,double,double,double,double);
    /**
     *\fn ~Option()
     *\brief virtual destructor
     */
    virtual ~Option(){};
    /**
     *\fn get_K()
     *\brief K_ accessor
     */
    double get_K() const{return K_;}
    /**
     *\fn get_T()
     *\brief T_ accessor
     */
    double get_T() const{return T_;}
    /**
     *\fn get_sigma()
     *\brief sigma_ accessor
     */
    double get_sigma() const{return sigma_;}
    /**
     *\fn get_r()
     *\brief r_ accessor
     */
    double get_r() const{return r_;}
    /**
     *\fn get_L()
     *\brief L_ accessor
     */
    double get_L() const{return L_;}
    /**
     *\fn get_alpha()
     *\brief alpha_ accessor
     */
    double get_alpha() const{return alpha_;}
    /**
     *\fn get_beta()
     *\brief beta_ accessor
     */
    double get_beta() const{return beta_;}
    /**
     *\fn payoff(double)
     *\brief pure virtual option price at maturity (option payoff)
     *\param double S value of underlying asset at maturity
     *\return option price at maturity
     *If S is negative, throws const char * exception
     */
    virtual double payoff(double) const = 0;
    /**
     *\fn upper_spatial_time_value(double)
     *\brief pure virtual upper spatial time value
     *\param double t time since emission
     *\return underlying asset's upper boundary time value
     *if t is negative or greater than T_, throws const char * exception
     */
    virtual double upper_spatial_time_value(double) const=0;
    /**
     *\fn lower_spatial_time_value(double)
     *\brief pure virtual lower spatial time value
     *\param double t time since emission
     *\return underlying asset's lower boundary time value
     *if t is negative or greater than T_, throws const char * exception
     */
    virtual double lower_spatial_time_value(double) const=0;
    /**
     *\fn heat_payoff(double)
     *\brief pure virtual heat initial value
     *\param double 
     *
     */
    virtual double heat_payoff(double) const = 0;
    virtual double heat_upper_spatial_time_value(double) const=0;
    virtual double heat_lower_spatial_time_value(double) const=0;
  protected:
    /**
     *\var K_ strike, must be strictly positive
     *\var T_ time to maturity at emission, must be strictly positive
     *\var sigma_ volatility, measured as the standard deviation of the stock's
     *returns, must be strictly positive
     *\var r_ annualized risk-free interest rate, must be less than 1 in
     *absolute value
     *\var L_ underlying asset maximum value
     *\var alpha_ and beta_ are parameters for the transformation from option
     *price to heat value with : alpha_ = (r-sigma^2/2)/sigma^2 and
     *beta_ = (r-sigma^2/2)^2/(2*sigma^2)+r
     */
    double K_,T_,sigma_,r_,L_,alpha_,beta_;
  };
  class CallOption : public Option{
  public:
    /**
     *\fn CallOption(double,double,double,double,double)
     *\brief parameterized constructor
     *\param doubles K,T,sigma,r,L
     *Initializes call option parameters, throws const char * exceptions 
     *when arguments do not conform to parameter characteristics
     */
    CallOption(double,double,double,double,double);
    /**
     *\fn ~CallOption()
     *\brief overrided destructor
     */
    ~CallOption() override{};
    /**
     *\fn payoff(double)
     *\brief overrided payoff for call option
     *\param double S
     *\return max(S-K_,0)
     */
    double payoff(double) const override final;
    /**
     *\fn upper_spatial_time_value(double)
     *\brief overrided upper spatial time value for call option
     *\param double t
     *\return L_ - K_ * exp(-r_(T_-t))
     *For underlying asset's max value L_ great enough (relative to K_), 
     *put option price is assumed to be the difference between L_ and 
     *actualized value of K, thus L_ - K_ * exp(-r_(T_-t)), insuring continuity
     *with payoff boundary
     *Note : one can also find this condition via the put-call parity
     */
    double upper_spatial_time_value(double) const override final;
    /**
     *\fn lower_spatial_time_value(double)
     *\brief overrided lower spatial time value for call option
     *\param double t
     *\return 0
     *For underlying asset's min value (0), call option's price is assumed 
     *to be 0 (call option will never be exercised)
     */
    double lower_spatial_time_value(double) const override final;
    double heat_payoff(double) const override final;
    double heat_upper_spatial_time_value(double) const override final;
    double heat_lower_spatial_time_value(double) const override final;
  };
  class PutOption : public Option{
  public:
    /**
     *\fn PutOption(double,double,double,double,double)
     *\brief parameterized constructor
     *\param doubles K,T,sigma,r,L
     *Initializes put option parameters, throws const char * exceptions 
     *when arguments do not conform to parameter characteristics
     */
    PutOption(double,double,double,double,double);
    /**
     *\fn ~PutOption()
     *\brief overrided destructor
     */
    ~PutOption() override{};
    /**
     *\fn payoff(double)
     *\brief overrided payoff for put option
     *\param double S
     *\return max(K_-S,0)
     *If K_ is greater than S, buyer exercises put option and makes K_-S
     *benefit, else 0
     */
    double payoff(double) const override final;
    /**
     *\fn upper_spatial_time_value(double)
     *\brief overrided upper spatial time value for put option
     *\param double t
     *\return 0
     *For underlying asset's max value L_ great enough (relative to K_), 
     *put option price is assumed to be 0 (put option will never be exercised)
     */
    double upper_spatial_time_value(double) const override final;
    /**
     *\fn lower_spatial_time_value(double)
     *\brief overrided lower spatial time value for put option
     *\param double t
     *\return K_ * exp(-r_(T_-t))
     *For underlying asset's min value (0), put option price is assumed to be 
     *actualized value of K, thus K_ * exp(-r_(T_-t)) insuring continuity with
     *payoff boundary
     */
    double lower_spatial_time_value(double) const override final;
    double heat_payoff(double) const override final;
    double heat_upper_spatial_time_value(double) const override final;
    double heat_lower_spatial_time_value(double) const override final;
  };
}

#endif
