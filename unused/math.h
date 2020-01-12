#ifndef MATH_H
#define MATH_H

/**
 *\file math.h
 *\brief Math functions useful for program
 *\authors Gabriel Moran, Julien Malfoy
 */

/**
 *\namespace master
 *\brief namespace used for project
 */
namespace master{
  /**
   *\class Math
   *\brief class for math functions used in program
   */
  class Math{
  public:
    /**
     *\fn double max(double,double)
     *\brief compute maximum of doubles
     *
     *\param double
     *\param double
     *\return double max of parameters
     */
    static double max(double,double);
    /**
     *\fn double abs(double)
     *\brief compute absolute value of double
     *
     *\param double
     *\return absolute value of double parameter
     */
    static double abs(double);
    /**
     *\fn double fact
     *\brief compute factorial
     *\param unsigned int
     *\return param factorial
     */
    static double fact(unsigned int);
    /**
     *\fn double exp(double)
     *\brief compute exponential
     *\param double
     *\return param exponential
     *
     *Approaches exponential by the first 10 terms of its series development
     *
     *Explanation :
     *Both the implicit and Crank-Nicholson schemes are consistent and 
     *numerically stable with local truncation errors equal respectively to
     *O(dt,dx^2) and O(dt^2,dx^2)
     *In our application, we will have dt~10^-3 and dx~10^-1
     *The error in exp approximation is x^N/N!
     *Since exp will only be used for values less than 1 in absolute value
     *(see option class payoff functions) we need to add the first N terms such
     *that 1/N! ~ 10^-6 (10^-6 is dt^2), thus N=10.
     *Stability of both schemes insures round-off errors will not be amplified
     */
    static double exp(double);
    /**
     *\fn double pow(double,unsigned long)
     *\brief computes power function
     *\param double
     *\param unsigned long
     *\return double param exponent unsigned long
     */
    static double pow(double,unsigned long);
  };
}

#endif
