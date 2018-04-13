/* Copyright (C) 2018 Grzegorz Wcisło */

#include "complex.h"

/* Returns the square of a complex number */
Complex square(Complex c)
{
    return (Complex) {c.re*c.re - c.im*c.im, 2*c.re*c.im};
}

/* Returns the sum of two complex numbers */
Complex add(Complex c1, Complex c2)
{
    return (Complex) {c1.re + c2.re, c1.im + c2.im};
}

/* Returns the absolute value of a complex number squared */
double cabs_sq(Complex c)
{
    return c.re*c.re + c.im*c.im;
}
