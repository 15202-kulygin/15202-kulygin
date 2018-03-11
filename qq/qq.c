#include <stdio.h>
#include <math.h>
#include <ctype.h>
#define N 4
#define M 2

int F(char A[][M], int n, int m){
int z, s = 0, k = 0;
for (int i = 0; i < m; i++){
z = 0;
for (int j = 0; j < n - 1; j++){
if ((A[j][i] <= A[j + 1][i]) || (A[j][i] >= '0') && (A[j][i] <= '9'))
z++;//если не удовлетворяет условию, то прибавит 1
}
if (z == 0)
s++;//если столбец подходит прибавит 1
}
return s;
}

int main(){
FILE *f;
char A[N][M], c;
int count = 0, h = 0, K, i, j;
fopen_s(&f, "matr.txt", "r");
printf("Input K:");
scanf_s("%d", &K);
while (fscanf_s(f, "%c", &c) != EOF){
count++;//номер матрицы
for (i = 0; i < N; i++){
for (j = 0; j < M; j++){
if ((j == M - 1) && (i == N - 1))
A[i][j] = c;
else{
A[i][j] = c;
fscanf_s(f, "%c", &c);
}
}
}
printf("%d\n", F(A, N, M));//проверка как работает функция
if ((count>K) && (F(A, N, M) < (count % 10 - 1)))
h++;
}
printf("%d", h);
fclose(f);
return 0;
}