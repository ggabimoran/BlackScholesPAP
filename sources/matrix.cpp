#include "../headers/matrix.h"
#include <iostream>

namespace master{
  VectorColumn::VectorColumn(unsigned int nl)
    : BMatrix(nl,1), data_{nullptr}
  {
    data_ = new double[nl]{};
  }
  VectorColumn::~VectorColumn() {delete[] data_;}
  double VectorColumn::operator() (unsigned int l,unsigned int c) const {
    if (l>=nl_) throw "index out of bounds";
    return data_[l];
  }
  double& VectorColumn::operator() (unsigned int l,unsigned int c) {
    if (l>=nl_) throw "index out of bounds";
    return data_[l];
  }  
  double VectorColumn::operator[] (unsigned int l) const {return (*this)(l,1);}
  double& VectorColumn::operator[] (unsigned int l) {return (*this)(l,1);}
  VectorColumn& VectorColumn::operator= (const VectorColumn& v){
    if (!v.data_) throw "vector length cannot be null";
    delete[] data_;
    nl_ = v.nl_;
    data_ = new double[nl_]{};
    for (int i=0;i<nl_;i++) data_[i] = v.data_[i];
    return *this;
  }
  std::ostream& operator<<(std::ostream& out,const VectorColumn& v){
    for (unsigned int i=0;i<v.get_nl();i++) std::cout<<"["<<v[i]<<"]\n";
    return out;
  }

  Matrix_Sparse::Matrix_Sparse(unsigned int nl,unsigned int nc):BMatrix(nl,nc){
    start_ = new int[nl]{};
  }
  Matrix_Sparse::~Matrix_Sparse() {delete[] start_;}
  double Matrix_Sparse::operator() (unsigned int l,unsigned int c) const {
    if (l>=nl_ || c >= nc_) throw "index out of range";
    int end = (l == nl_-1) ? nc_ : start_[l+1];
    for (int i=start_[l];i<end;i++){
      if (idx_[i]==c) return val_[i];
    }
    return 0;
  }
  double& Matrix_Sparse::operator() (unsigned int l,unsigned int c){
    if (l>=nl_ || c >= nc_) throw "index out of range";
    int end = (l == nl_-1) ? nc_ : start_[l+1];
    int i = start_[l];
    while (i<end && idx_[i]<c) i++;
    if (i==end || idx_[i]!=c){
      val_.insert(val_.begin()+i,0);
      idx_.insert(idx_.begin()+i,c);
    }
    return val_[i];
  }
  Square_Matrix_Sparse::Square_Matrix_Sparse(unsigned int n)
    : Matrix_Sparse(n,n){}
  TriDiag_Matrix_Sparse::TriDiag_Matrix_Sparse(unsigned int n)
    : Square_Matrix_Sparse(n){}
  const Matrix_Sparse& TriDiag_Matrix_Sparse::inv() const{
    return *this;//TODO!!
  }
}
