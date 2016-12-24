#include <fstream>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#define N 4
#define M 10000
std::ofstream fout("output1.txt");
std::ifstream fin("input.txt");
void print_matrix(float** matrix){
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
     fout<<matrix[i][j]<<"  ";
    }
    fout<<std::endl;
  }
  fout<<std::endl;
}
float** MatrixMult(float** first_matrix,float** second_matrix){
  int i,j,k;
  float **result = new float*[N]();
  for (i=0;i<N;i++){
    result[i]=new float[N]();
    for (j=0;j<N;j++){
      for (k=0;k<N;k++){
        result[i][j]+=first_matrix[i][k]*second_matrix[k][j];
      }
    }
  }
  return result;
}
float** Create_Identity_Matrix(){
  int i;
  float **result = new float*[N]();
  for (i=0;i<N;i++){
    result[i]=new float[N]();
    result[i][i]=1;
  }
  return result;
}
float** Matrix_Transporation(float** input_matrix){
  int i,j;
  float **result = new float*[N]();
  for (i=0;i<N;i++){
    result[i]=new float[N]();
    for (j=0;j<N;j++){
      result[i][j]=input_matrix[j][i];
    }
  }
  return result;
}
float** MatrixAdd(float** first_matrix,float** second_matrix){
  int i,j;
  float **result = new float*[N]();
  for (i=0;i<N;i++){
    result[i]=new float[N]();
    for (j=0;j<N;j++){
      result[i][j]=first_matrix[i][j]+second_matrix[i][j];
    }
  }
  return result;
}
float** MatrixSub(float** first_matrix,float** second_matrix){
  int i,j;
  float **result = new float*[N]();
  for (i=0;i<N;i++){
    result[i]=new float[N]();
    for (j=0;j<N;j++){
      result[i][j]=first_matrix[i][j]-second_matrix[i][j];
    }
  }
  return result;
}
float Find_A1(float** matrix){
  int i,j,max=0,sum_temp=0;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      sum_temp+=std::abs(matrix[i][j]);
    }
    if (sum_temp>max) {
      max=sum_temp;
    }
    sum_temp=0;
  }
  return max;
}
float Find_A_Infinite(float** matrix){
  int i,j,max=0,sum_temp=0;
  for (j = 0; j < N; j++) {
    for (i = 0; i < N; i++) {
      sum_temp+=std::abs(matrix[i][j]);
    }
    if (sum_temp>max) {
      max=sum_temp;
    }
    sum_temp=0;
  }
  return max;
}
float** Div_Matrix_By_Float(float** matrix,float number){
  int i,j;
  float **result = new float*[N]();
  for (i = 0; i < N; i++) {
    result[i]=new float[N]();
    for (j = 0; j < N; j++) {
      result[i][j]=(float)matrix[i][j]/number;
    }
  }
  return result;
}
float** Find_Invert_Matrix(float** input_matrix){
  int i,j,k,l;
  float** matrix_B;
  float** matrix_I;
  float** matrix_R;
  float** matrix_R_temp;
  float **result = new float*[N]();
  for (i = 0; i < N; i++) {
    result[i]=new float[N]();
  }
  result = Create_Identity_Matrix();
  matrix_B = Div_Matrix_By_Float(Matrix_Transporation(input_matrix),Find_A_Infinite(input_matrix)*Find_A1(input_matrix));
  matrix_R = MatrixSub(result,MatrixMult(matrix_B,input_matrix));
  matrix_R_temp=Div_Matrix_By_Float(matrix_R,1);
  for (i=0;i<M;i++){
    result=MatrixAdd(result,matrix_R_temp);
    matrix_R_temp=MatrixMult(matrix_R,matrix_R_temp);
  }
  result = MatrixMult(result,matrix_B);
  return result;
}
int main(){
  srand(time(NULL));
  float** matrix_A=new float*[N]();
  for (size_t i = 0; i < N; i++) {
    matrix_A[i]=new float[N]();
  }
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      matrix_A[i][j]=rand()%10;
    }
  }
  // for (size_t i = 0; i < N; i++) {
  //   for (size_t j = 0; j < N; j++) {
  //     fin>>matrix_A[i][j];
  //   }
  // }
  float** matrix_invert_A = Find_Invert_Matrix(matrix_A);
  float** matrix_C=MatrixMult(matrix_A,matrix_invert_A);
  print_matrix(matrix_A);
  print_matrix(matrix_invert_A);
  print_matrix(matrix_C);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      if (((i==j) && std::abs(1-matrix_C[i][j])>0.1) || ((i!=j) && (std::abs(matrix_C[i][j])>0.1))){
        std::cout<<"UNCORRECT";
        return 0;
      }
    }
  }
  std::cout<<"CORRECT";
  return 0;
}
