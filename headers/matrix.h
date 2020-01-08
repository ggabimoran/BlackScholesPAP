#ifndef MATRIX_H
#define MATRIX_H

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
    Matrix_Sparse(unsigned int,unsigned int);
    ~Matrix_Sparse() override;
    virtual double operator() (unsigned int,unsigned int) const=0;
    virtual double& operator() (unsigned int,unsigned int)=0;
  };
  class Square_Matrix_Sparse : public Matrix_Sparse{
  public:
    Square_Matrix_Sparse(unsigned int);
    ~Square_Matrix_Sparse() override;
    double operator() (unsigned int,unsigned int) const override final;
    double& operator() (unsigned int,unsigned int) override final;
    Square_Matrix_Sparse& inv() const;
  };
  class VectorColumn_Sparse : public Matrix_Sparse{
  private:
    double operator() (unsigned int,unsigned int) const override final;
    double& operator() (unsigned int,unsigned int) override final;
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
  VectorColumn& operator*(const Square_Matrix_Sparse&,const VectorColumn&);
}

#endif
