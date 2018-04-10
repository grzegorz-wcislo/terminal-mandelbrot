#include <stdlib.h>
#include <stdio.h>

typedef struct {
    double re, im;
} Complex;

Complex square(Complex);
Complex add(Complex, Complex);
double cabs_sq(Complex);

Complex square(Complex c) {
    Complex res = {c.re*c.re - c.im*c.im, 2*c.re*c.im};
    return res;
}

Complex add(Complex c1, Complex c2) {
    Complex res = {c1.re + c2.re, c1.im + c2.im};
    return res;
}

double cabs_sq(Complex c) {
    return c.re*c.re + c.im*c.im;
}
