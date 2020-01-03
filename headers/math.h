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
     *\brief returns max of doubles
     *
     *\param double
     *\param double
     *\return double max of parameters
     */
    static double max(double,double);
    /**
     *\fn double abs(double)
     *\brief returns abs of double
     *
     *\param double
     *\return absolute value of double parameter
     */
    static double abs(double);
    static double exp(double);
    static double pow(double,int);
    static double pow(double,double);
  };
}

#endif
