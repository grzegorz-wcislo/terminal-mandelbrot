#ifndef COMPLEX_H_
#define COMPLEX_H_

typedef struct {
    double re, im;
} Complex;

Complex square(Complex);
Complex add(Complex, Complex);
double cabs_sq(Complex);

#endif
