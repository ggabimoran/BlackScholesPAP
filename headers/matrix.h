#ifndef MATRIX_H
#define MATRIX_H
/**
 *#include <iostream> for testing and overload << operator for testing
 */
#include <iostream> 
#include <vector>

namespace master{
  class BMatrix{
  protected:
    unsigned int nl_,nc_;
  public:
    BMatrix(unsigned int nl,unsigned int nc){nl_ = nl; nc_ = nc;}
    virtual ~BMatrix() {}
    unsigned int get_nl() const{return nl_;}
    unsigned int get_nc() const{return nc_;}
    bool same_size(const BMatrix& m) const{return (nl_ == m.get_nl())&&(nc_ == m.get_nc());}
    virtual double operator() (unsigned int,unsigned int) const = 0;
    virtual double& operator() (unsigned int,unsigned int) = 0;
  };
  class FullMatrix : public BMatrix{
  protected:
    double **data_;
  public:
    FullMatrix(unsigned int,unsigned int);
    FullMatrix(const FullMatrix&);
    ~FullMatrix() override;
    double operator() (unsigned int,unsigned int) const override final;
    double& operator() (unsigned int,unsigned int) override final;
    FullMatrix& operator= (const FullMatrix&);
  };
  class VectorColumn : public FullMatrix{
  public:
    VectorColumn(unsigned int);
    VectorColumn(const VectorColumn&);
    ~VectorColumn() override {};
    unsigned int get_size() const {return nl_;}
    double operator[] (unsigned int) const;
    double& operator[] (unsigned int);
    VectorColumn& operator= (const VectorColumn&);
  };
  class Matrix_Sparse : public BMatrix{
  protected:
    int *start_;
    std::vector<int> idx_;
    std::vector<double> val_;
    virtual double& operator() (unsigned int,unsigned int) override final;
  public:
    Matrix_Sparse(const FullMatrix&);
    Matrix_Sparse(const Matrix_Sparse&);
    ~Matrix_Sparse() override;
    virtual double operator() (unsigned int,unsigned int) const override final;
    Matrix_Sparse& operator= (const Matrix_Sparse&);
    Matrix_Sparse& operator= (const FullMatrix&);
  };
  class TriDiag_Matrix_Sparse : public Matrix_Sparse{
  public:
    TriDiag_Matrix_Sparse(const FullMatrix&);
    TriDiag_Matrix_Sparse(const TriDiag_Matrix_Sparse&);
    ~TriDiag_Matrix_Sparse() override {};
    TriDiag_Matrix_Sparse& operator= (const TriDiag_Matrix_Sparse&);
  };

  VectorColumn resolutionLUTriDiag(const TriDiag_Matrix_Sparse&,const VectorColumn&);
  VectorColumn solInf(const TriDiag_Matrix_Sparse&,const VectorColumn&);
  VectorColumn solSup(const TriDiag_Matrix_Sparse&,const VectorColumn&);
  

  VectorColumn operator+(const VectorColumn&,const VectorColumn&);
  VectorColumn operator-(const VectorColumn&,const VectorColumn&);
  VectorColumn operator*(const TriDiag_Matrix_Sparse&,const VectorColumn&);
  VectorColumn operator*(const FullMatrix&,const VectorColumn&);
  
  std::ostream& operator<<(std::ostream&,const VectorColumn&);
  std::ostream& operator<<(std::ostream&,const TriDiag_Matrix_Sparse&);
  std::ostream& operator<<(std::ostream&,const FullMatrix&);
}



#endif
