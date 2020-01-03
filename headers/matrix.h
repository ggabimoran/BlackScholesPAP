#ifndef MATRIX_H
#define MATRIX_H

namespace master{
  class BMatrix{
    unsigned long nl_,nc_;
  public:
    unsigned long get_nl() const{return nl_;}
    unsigned long get_nc() const{return nc_;}
  };
  class FullMatrix : public BMatrix{
  };
  class VectorColumn : public FullMatrix{
  public:
    VectorColumn(unsigned long);
    double operator() (double) const;
    double& operator() (double);
  };
  class Matrix_Sparse : public BMatrix{
  };
  class Square_Matrix_Sparse : public Matrix_Sparse{
  public:
    Square_Matrix_Sparse(unsigned long);
    double operator() (double,double) const;
    double& operator() (double,double);
    Square_Matrix_Sparse& inv();
  };
  class VectorColumn_Sparse : public Matrix_Sparse{
  public:
    VectorColumn_Sparse(unsigned long);
    double operator() (double) const;
    double& operator() (double);
  };

  VectorColumn& operator+(const VectorColumn&,const VectorColumn_Sparse&);
  VectorColumn& operator+(const VectorColumn_Sparse&,const VectorColumn&);
  VectorColumn& operator-(const VectorColumn&,const VectorColumn_Sparse&);
  VectorColumn& operator-(const VectorColumn_Sparse&,const VectorColumn&);
  VectorColumn& operator*(const Square_Matrix_Sparse&,const VectorColumn&);
}

#endif
