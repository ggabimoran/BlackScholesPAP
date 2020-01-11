#ifndef MATRIX_H
#define MATRIX_H

#include <iostream> //for testing
#include <vector>

namespace master{
  class BMatrix{
  protected:
    unsigned int nl_,nc_;
  public:
    BMatrix(unsigned int nl,unsigned int nc){nl_ = nl; nc_ = nc;}
    virtual ~BMatrix() {}
    int get_nl() const{return nl_;}
    int get_nc() const{return nc_;}
    bool same_size(const BMatrix& m){return (nl_ == m.get_nl())&&(nc_ == m.get_nc());}
    virtual double operator() (unsigned int,unsigned int) const = 0;
    virtual double& operator() (unsigned int,unsigned int) = 0;
  };
  class VectorColumn : public BMatrix{
  private:
    double *data_;
    double operator() (unsigned int,unsigned int) const override final;
    double& operator() (unsigned int,unsigned int) override final;
  public:
    VectorColumn(unsigned int);
    ~VectorColumn() override;
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
  public:
    Matrix_Sparse(unsigned int,unsigned int);
    ~Matrix_Sparse() override;
    virtual double operator() (unsigned int,unsigned int) const override final;
    virtual double& operator() (unsigned int,unsigned int) override final;
  };
  class Square_Matrix_Sparse : public Matrix_Sparse{
  public:
    Square_Matrix_Sparse(unsigned int);
    ~Square_Matrix_Sparse() override {};
    virtual const Matrix_Sparse& inv() const=0;
  };
  class TriDiag_Matrix_Sparse : public Square_Matrix_Sparse{
  public:
    TriDiag_Matrix_Sparse(unsigned int);
    ~TriDiag_Matrix_Sparse() override {};
    const Matrix_Sparse& inv() const override final;
  };
  class VectorColumn_Sparse : public Matrix_Sparse{
  public:
    VectorColumn_Sparse(unsigned int);
    ~VectorColumn_Sparse() override;
    double operator[] (unsigned int) const;
    double& operator[] (unsigned int);
    unsigned int get_size() const {return nl_;}
  };

  VectorColumn& operator+(const VectorColumn&,const VectorColumn_Sparse&);
  VectorColumn& operator+(const VectorColumn_Sparse&,const VectorColumn&);
  VectorColumn& operator-(const VectorColumn&,const VectorColumn_Sparse&);
  VectorColumn& operator-(const VectorColumn_Sparse&,const VectorColumn&);
  VectorColumn& operator*(const TriDiag_Matrix_Sparse&,const VectorColumn&);
  VectorColumn& operator*(const Matrix_Sparse&,const VectorColumn&);
  //for testing
  std::ostream& operator<<(std::ostream&,const VectorColumn&);
  std::ostream& operator<<(std::ostream&,const VectorColumn_Sparse&);
  std::ostream& operator<<(std::ostream&,const TriDiag_Matrix_Sparse&);
}



#endif
