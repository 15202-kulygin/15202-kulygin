#include <xmmintrin.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#ifdef __INTEL_COMPILER
 #include<mkl_cblas.h> // C-интерфейс BLAS (заголовочный файл из MKL)
#else
 #include<cblas.h> // C-интерфейс BLAS (стандартный заголовочный файл)
#endif
#define N 800
#define M 10
std::ofstream fout("output3.txt");
std::ifstream fin("input3.txt");
void print_matrix(float* matrix){
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
     fout<<matrix[i*N+j]<<"  ";
    }
    fout<<std::endl;
  }
  fout<<std::endl;
}
float inner2(float* x, float* y){
  __m128 *xx, *yy;
  __m128 p, s;
  xx = (__m128*)x;
  yy = (__m128*)y;
  s = _mm_setzero_ps();
  for(int i=0; i<N/4; i++){
    p = _mm_mul_ps(xx[i],yy[i]);
    s = _mm_add_ps(s,p);
  }
  p = _mm_movehl_ps(p,s);
  s = _mm_add_ps(s,p);
  p = _mm_shuffle_ps(s,s,1);
  s = _mm_add_ss(s,p);
  float sum;
  _mm_store_ss(&sum,s);
  return sum;
}
float* Matrix_Transporation(float* input_matrix){
  int i,j;
  float *result = new float[N*N]();
  for (i=0;i<N;i++){
    for(j=0;j<N;j++){
      result[i*N+j]=input_matrix[j*N+i];
    }
  }
  return result;
}
float* MatrixMult(float* first_matrix,float* second_matrix){
  float *result = new float[N*N]();
  cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,
 N,N,N,1.0,first_matrix,N,second_matrix,N,0.0,result,N);
  return result;
}
float* MatrixSub(float* first_matrix,float* second_matrix){
  float *result = new float[N*N]();
  __m128 *m1 = (__m128*)first_matrix;
  __m128 *m2 = (__m128*)second_matrix;
  __m128 *m3 = (__m128*)result;
    for(unsigned j = 0; j < N*N/4; j++) {
      m3[j]=_mm_sub_ps(m1[j],m2[j]);
    }
  return result;
}
float* MatrixAdd(float* first_matrix,float* second_matrix){
  float *result = new float[N*N]();
  __m128 *m1 = (__m128*)first_matrix;
  __m128 *m2 = (__m128*)second_matrix;
  __m128 *m3 = (__m128*)result;
    for(unsigned j = 0; j < N*N/4; j++) {
      m3[j]=_mm_add_ps(m1[j],m2[j]);
    }
  return result;
}
float* Div_Matrix_By_Float(float* matrix,float number){
  float *result = new float[N*N]();
  __m128 *m1 = (__m128*)matrix;
  __m128 m2 = {number, number, number ,number};
  __m128 *m3 = (__m128*)result;
  for(unsigned j = 0; j < N*N/4; j++) {
    m3[j]=_mm_div_ps(m1[j],m2);
  }
  return result;
}
float Find_A1(float* matrix){
  __m128 *d = (__m128*)matrix;
  __m128 tmp,tmp2;
  float sum = 0;
  float max = 0;
  for(unsigned i = 0; i < N; ++i) {
    tmp = _mm_setzero_ps();
    for(unsigned j=0; j < N/4; ++j) {
      tmp = _mm_add_ps(tmp, d[i*N/4+j]);
    }
    tmp2 = _mm_shuffle_ps(tmp,tmp,1);
    tmp = _mm_add_ss(tmp,tmp2);
    tmp2 = _mm_shuffle_ps(tmp,tmp,2);
    tmp = _mm_add_ss(tmp,tmp2);
    tmp2 = _mm_shuffle_ps(tmp,tmp,3);
    tmp = _mm_add_ss(tmp,tmp2);
    _mm_store_ss(&sum, tmp);
    if(max < sum) {
      max = sum;
    }
  }
  return max;
}
float Find_A_Infinite(float* matrix){
  return Find_A1(Matrix_Transporation(matrix));
}
float* Create_Identity_Matrix(){
  int i;
  float *result = new float[N*N]();
  for (i=0;i<N;i++){
    result[i*N+i]=1;
  }
  //print_matrix(result);
  return result;
}
float* Find_Invert_Matrix(float* input_matrix){
  int i,j,k,l;
  float* matrix_B;
  float* matrix_I;
  float* matrix_R;
  float* matrix_R_temp;
  float* result = new float[N*N]();
  result = Create_Identity_Matrix();
  matrix_B = Div_Matrix_By_Float(Matrix_Transporation(input_matrix),Find_A_Infinite(input_matrix)*Find_A1(input_matrix));
  fout<<Find_A_Infinite(input_matrix)<<' '<<Find_A1(input_matrix)<<std::endl;
  print_matrix(Matrix_Transporation(input_matrix));fout<<Find_A_Infinite(input_matrix)*Find_A1(input_matrix)<<std::endl;;
  print_matrix(matrix_B);
  matrix_R = MatrixSub(result,MatrixMult(matrix_B,input_matrix));
  matrix_R_temp=Div_Matrix_By_Float(matrix_R,1);
  for (i=0;i<M;i++){
    result=MatrixAdd(result,matrix_R_temp);
    matrix_R_temp=MatrixMult(matrix_R,matrix_R_temp);
    fout<<"i="<<i<<std::endl;
    print_matrix(matrix_R_temp);
  }
  result = MatrixMult(result,matrix_B);
  return result;
}
int main(){
  srand(time(NULL));
  float* matrix_A=new float[N*N]();
  float* matrix_B=new float[N*N]();
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix_A[i*N+j]=rand()%1000;
    }
  }
  // for (size_t i = 0; i < N; i++) {
  //   for (size_t j = 0; j < N; j++) {
  //     fin>>matrix_A[i*N+j];
  //   }
  // }
  float* matrix_invert_A = Find_Invert_Matrix(matrix_A);
  float* matrix_C=MatrixMult(matrix_A,matrix_invert_A);
  print_matrix(matrix_A);
  print_matrix(matrix_invert_A);
  print_matrix(matrix_C);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (((i==j) && abs(1-matrix_C[i*N+j])>0.1) || (i!=j) && (abs(matrix_C[i*N+j])>0.1)){
        std::cout<<"UNCORRECT";
        return 0;
      }
    }
  }
  std::cout<<"CORRECT";
  return 0;
}
