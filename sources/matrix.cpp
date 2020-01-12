#include "../headers/matrix.h"
#include <iostream>
#include <vector>

namespace master{
  FullMatrix::FullMatrix(unsigned int nl,unsigned int nc)
    : BMatrix(nl,nc)
  {
    data_ = new double*[nl];
    for(int i = 0; i < nl; ++i)
      data_[i] = new double[nc]{};
  }
  FullMatrix::FullMatrix(const FullMatrix& fm):BMatrix(fm.nl_,fm.nc_){
    data_ = new double*[nl_];
    for(int i = 0; i < nl_; ++i){
      data_[i] = new double[nc_]{};
      for (int j=0;j<nc_;j++)
	data_[i][j]=fm(i,j);
    }
  }
  FullMatrix::~FullMatrix(){
    for (int i=0;i<nl_;++i){
      delete[] data_[i];
    }
    delete[] data_;
  }
  FullMatrix& FullMatrix::operator=(const FullMatrix& fm){
    for (int i=0;i<nl_;++i){
      delete[] data_[i];
    }
    delete[] data_;
    data_ = new double*[nl_];
    for(int i = 0; i < nl_; ++i){
      data_[i] = new double[nc_]{};
      for (int j=0;j<nc_;j++)
	data_[i][j]=fm(i,j);
    }
    return *this;
  }
  double FullMatrix::operator() (unsigned int l,unsigned int c) const{
    if (l >= nl_ || c >= nc_) throw "index out of range";
    return data_[l][c];
  }
  double& FullMatrix::operator() (unsigned int l,unsigned int c){
    if (l >= nl_ || c >= nc_) throw "index out of range";
    return data_[l][c];
  }
  VectorColumn::VectorColumn(unsigned int nl)
    : FullMatrix(nl,1){}
  VectorColumn::VectorColumn(const VectorColumn& v):FullMatrix(v){}
  double VectorColumn::operator[] (unsigned int l) const {return (*this)(l,0);}
  double& VectorColumn::operator[] (unsigned int l) {return (*this)(l,0);}
  VectorColumn& VectorColumn::operator= (const VectorColumn& v){
    for (int i=0;i<nl_;++i){
      delete[] data_[i];
    }
    delete[] data_;
    data_ = new double*[nl_];
    for(int i = 0; i < nl_; ++i){
      data_[i] = new double[1]{};
      data_[i][0]=v[i];
    }
    return *this;
  }
  Matrix_Sparse::Matrix_Sparse(const FullMatrix& fm)
    :BMatrix(fm.get_nl(),fm.get_nc()){
    start_ = new int[nl_]{};
    bool line_started=false;
    bool one_non_null=false;
    for (int i=0;i<fm.get_nl();i++){
      line_started=false;
      for (int j=0;j<fm.get_nc();j++){
	if (fm(i,j)!=0){
	  val_.push_back(fm(i,j));
	  idx_.push_back(j);
	  if (!line_started){
	    start_[i]=idx_.size()-1;
	    line_started=true;
	  }
	  if (one_non_null){
	    for (int k=i+1;k<nl_;k++){
	      start_[k]+=1;
	    }
	  }
	  one_non_null=true;
	}
      }
    }
  }
  Matrix_Sparse::Matrix_Sparse(const Matrix_Sparse& sm)
    :BMatrix(sm.get_nl(),sm.get_nc())
  {
    start_ = new int[nl_]{};
    for (int i=0;i<nl_;i++){
      start_[i]=sm.start_[i];
    }
    val_=sm.val_;
    idx_=sm.idx_;
  }
  Matrix_Sparse::~Matrix_Sparse() {delete[] start_;}
  double Matrix_Sparse::operator() (unsigned int l,unsigned int c) const {
    if (l>=nl_ || c >= nc_) throw "index out of range";
    int endl = (l == nl_-1) ? idx_.size() : start_[l+1];
    int j=start_[l];
    while (j<idx_.size() && idx_[j]<c && j<endl) j++;
    if (j==idx_.size()) return 0;
    if (j==endl) return 0;
    if (idx_[j]>c) return 0;
    return val_[j];
  }
  double& Matrix_Sparse::operator() (unsigned int l,unsigned int c){
      if (l>=nl_ || c >= nc_) throw "index out of range";
      int endl = (l == nl_-1) ? idx_.size() : start_[l+1];
      int j=start_[l];
      while (j<idx_.size() && idx_[j]<c && j<endl) j++;
      if (j==idx_.size()){
	val_.insert(val_.end()-1,0);
        idx_.insert(idx_.end()-1,c);
      }
      else if (j==endl || idx_[j]>c) {
	val_.insert(val_.begin()+j,0);
        idx_.insert(idx_.begin()+j,c);
      }
      return val_[j];
  }
  Matrix_Sparse& Matrix_Sparse::operator= (const Matrix_Sparse& sm){
    delete[] start_;
    nl_=sm.get_nl();
    nc_=sm.get_nc();
    start_ = new int[nl_]{};
    for (int i=0;i<nl_;i++){
      start_[i]=sm.start_[i];
    }
    val_=sm.val_;
    idx_=sm.idx_;
    return *this;
  }
  Matrix_Sparse& Matrix_Sparse::operator= (const FullMatrix& fm){
    delete[] start_;
    nl_=fm.get_nl();
    nc_=fm.get_nc();
    start_ = new int[nl_]{};
    val_=std::vector<double>{};
    idx_=std::vector<int>{};
    bool line_started=false;
    bool one_non_null=false;
    for (int i=0;i<fm.get_nl();i++){
      line_started=false;
      for (int j=0;j<fm.get_nc();j++){
	if (fm(i,j)!=0){
	  val_.push_back(fm(i,j));
	  idx_.push_back(j);
	  if (!line_started){
	    start_[i]=idx_.size()-1;
	    line_started=true;
	  }
	  if (one_non_null){
	    for (int k=i+1;k<nl_;k++){
	      start_[k]+=1;
	    }
	  }
	  one_non_null=true;
	}
      }
    }
    return *this;
  }
  TriDiag_Matrix_Sparse::TriDiag_Matrix_Sparse(const FullMatrix& fm)
    :Matrix_Sparse(fm){
    for (int i=0;i<nl_;i++){
      for (int k=start_[i];(k<idx_.size() && k<start_[i+1]);k++){
	if (std::abs(idx_[k]-i)>1) throw "matrix not tridiagonal";
      }
    }
  }
  TriDiag_Matrix_Sparse::TriDiag_Matrix_Sparse(const TriDiag_Matrix_Sparse& sm)
    :Matrix_Sparse{sm}{}
  TriDiag_Matrix_Sparse& TriDiag_Matrix_Sparse::operator= (const TriDiag_Matrix_Sparse& tm){
    delete[] start_;
    nl_= tm.nl_;
    nc_=tm.nc_;
    start_ = new int[nl_]{};
    for (int i=0;i<nl_;i++){
      start_[i]=tm.start_[i];
    }
    val_=tm.val_;
    idx_=tm.idx_;
    return *this;
  }
  VectorColumn solInf(const TriDiag_Matrix_Sparse& tm,const VectorColumn& v){
    unsigned int n=v.get_size();
    VectorColumn sol{n};
    sol[0]=v[0]/tm(0,0);
    for (int i=1;i<n;i++){
      sol[i]=(v[i]-tm(i,i-1)*sol[i-1])/tm(i,i);
    }
    return sol;
  }

  VectorColumn solSup(const TriDiag_Matrix_Sparse& tm,const VectorColumn& v){
    unsigned int n=v.get_size();
    VectorColumn sol{n};
    sol[n-1]=v[n-1]/tm(n-1,n-1);
    for (int i=n-2;i>=0;i--){
      sol[i]=(v[i]-tm(i,i+1)*sol[i+1])/tm(i,i);
    }
    return sol;
  }

  VectorColumn resolutionLUTriDiag(const TriDiag_Matrix_Sparse& tm,const VectorColumn& v){
    unsigned int n=v.get_size();
    std::vector<double> delta;
    delta.push_back(1);
    delta.push_back(tm(0,0));
    for (int k=2;k<=n;k++){
      delta.push_back(tm(k-1,k-1)*delta[k-1]-tm(k-1,k-2)*tm(k-2,k-1)*delta[k-2]);
      if (delta[k]==0) throw "LU decomposition impossible";
    }
    FullMatrix L{n,n};
    FullMatrix U{n,n};
    L(0,0)=1;
    L(n-1,n-1)=1;
    L(n-1,n-2)=tm(n-1,n-2)*delta[n-2]/delta[n-1];
    U(0,0)=delta[1]/delta[0];
    U(0,1)=tm(0,1);
    U(n-1,n-1)=delta[n]/delta[n-1];
    for (int i=1;i<n-1;i++){
      L(i,i)=1;
      L(i,i-1)=tm(i,i-1)*delta[i-1]/delta[i];
      U(i,i)=delta[i+1]/delta[i];
      U(i,i+1)=tm(i,i+1);
    }
    const TriDiag_Matrix_Sparse sL{L};
    const TriDiag_Matrix_Sparse sU{U};
    VectorColumn y{solInf(sL,v)};
    return solSup(sU,y);
  }

  VectorColumn operator+(const VectorColumn& v1,const VectorColumn& v2){
    if (v1.same_size(v2)){
      VectorColumn newv{v1.get_nl()};
      for (int i=0;i<v1.get_nl();i++){
	newv[i]=v1[i]+v2[i];
      }
      return newv;
    }
    else throw "vectors are of different sizes";
  }
  VectorColumn operator-(const VectorColumn& v1,const VectorColumn& v2){
    if (v1.same_size(v2)){
      VectorColumn newv{v1.get_nl()};
      for (int i=0;i<newv.get_nl();i++){
	newv[i]=v1[i]-v2[i];
      }
      return newv;
    }
    else throw "vectors are of different sizes";
  }
  VectorColumn operator*(const TriDiag_Matrix_Sparse& tm,const VectorColumn& v){
    if (tm.get_nc()!=v.get_size()) throw "matrix multiplication impossible";
    VectorColumn newv{v.get_size()};
    double sum;
    for (int i=0;i<v.get_size();i++){
      sum=0;
      for (int k=0;k<v.get_size();k++){
	sum+=tm(i,k)*v[k];
      }
      newv[i]=sum;
    }
    return newv;
  }
  VectorColumn operator*(const FullMatrix& fm,const VectorColumn& v){
    if (fm.get_nc()!=v.get_size()) throw "matrix multiplication impossible";
    VectorColumn newv{v.get_size()};
    double sum;
    for (int i=0;i<v.get_size();i++){
      sum=0;
      for (int k=0;k<v.get_size();k++){
	sum+=fm(i,k)*v[k];
      }
      newv[i]=sum;
    }
    return newv;
  }
  
  std::ostream& operator<<(std::ostream& out,const VectorColumn& v){ 
    for (int i=0;i<v.get_size();i++){
      std::cout<<"["<<v[i]<<"]\n";
    }
    return out;
  }
  std::ostream& operator<<(std::ostream& out,const TriDiag_Matrix_Sparse& tm){
    for (int i=0;i<tm.get_nl();i++){
      for (int j=0;j<tm.get_nc();j++){
	std::cout<<((j==0)?"[":",")<<tm(i,j);
      }
      std::cout<<"]\n";
    }
    return out;
  }
  std::ostream& operator<<(std::ostream& out,const FullMatrix& fm){
    for (int i=0;i<fm.get_nl();i++){
      for (int j=0;j<fm.get_nc();j++){
	std::cout<<((j==0)?"[":",")<<fm(i,j);
      }
      std::cout<<"]\n";
    }
    return out;
  }
}
