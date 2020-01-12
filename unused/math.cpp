#include "../headers/math.h"

namespace master{
  double Math::max(double a,double b){return (a > b) ? a : b;}
  double Math::abs(double d){return (d > 0) ? d : -d;}
  double Math::fact(unsigned int n){
    if (n<=0) return 1;
    double prod=1;
    for (int i=2;i<=n;i++) prod *= i;
    return prod;
  }
  double Math::exp(double x){
    double sum=0;
    for (int i=0;i<=10;i++){
      sum+=pow(x,i)/fact(i);
    }
    return sum;
  }
  double Math::pow(double x,unsigned long d){
    if (d==0) return 1;
    if (x==0.) return 0;
    double prod=1;
    for (int i=1;i<=d;i++) prod *= x;
    return prod;
  }
}
