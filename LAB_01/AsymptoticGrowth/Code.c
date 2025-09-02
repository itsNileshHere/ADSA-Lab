#include <stdio.h>
#include <math.h>
#include <string.h>
#define INPUT_N 1000.0

typedef struct {
   char name[20];
   double (*func)(double);
   double value;
} Function;

// Mathematical functions
double f1(double n) { return 1.0/n; }
double f2(double n) { return 12.0/sqrt(n); }
double f3(double n) { return log2(n); }
double f4(double n) { return n * log2(n); }
double f5(double n) { return pow(n, log2(n)); }
double f6(double n) { return 100*n*n + 6*n; }
double f7(double n) { return pow(n, 0.51); }
double f8(double n) { return n*n - 324; }
double f9(double n) { return 50*sqrt(n); }
double f10(double n) { return 2*n*n*n; }
double f11(double n) { return pow(3, n); }
double f12(double n) { return pow(2, 32) * n; }

int main() {
   Function functions[] = {
    {"1/n", f1, 0},
    {"12/sqrt(n)", f2, 0},
    {"log2(n)", f3, 0},
    {"n*log2(n)", f4, 0},
    {"n^(log2(n))", f5, 0},
    {"100*n^2 + 6*n", f6, 0},
    {"n^0.51", f7, 0},
    {"n^2 - 324", f8, 0},
    {"50*sqrt(n)", f9, 0},
    {"2*n^3", f10, 0},
    {"3^n", f11, 0},
    {"(2^32)*n", f12, 0}
   };
   
   int n = sizeof(functions) / sizeof(functions[0]);
   
   // Calculate values
   for (int i = 0; i < n; i++) {
       functions[i].value = functions[i].func(INPUT_N);
   }
   
   // Sorting
   for (int i = 0; i < n-1; i++) {
       for (int j = 0; j < n-i-1; j++) {
           if (functions[j].value > functions[j+1].value) {
               Function temp = functions[j];
               functions[j] = functions[j+1];
               functions[j+1] = temp;
           }
       }
   }
   
    printf("Sorted by growth (n=%.0f):\n", INPUT_N);
    for (int i = 0; i < n; i++) {
        printf("%s", functions[i].name);
        if (i < n - 1) {
            printf(" < ");
        }
    }
    printf("\n");
    
   return 0;
}