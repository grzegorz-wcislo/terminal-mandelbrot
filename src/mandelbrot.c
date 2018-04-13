/* Copyright (C) 2018 Grzegorz Wcisło */

#include <stdlib.h>
#include <stdio.h>
#include "complex.h"

/* Colors used while drawing fractals */
#define RESET   "\033[0m"
#define REVERSE "\033[7m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/* Terminal characters are not perfect squares */
#define FONT_RATIO 1.8

int w;              /* number of terminal columns */
int h;              /* number of terminal rows */
double scale;       /* arbitrary zoom factor - smaller means greater zoom */
Complex center;     /* center of the visible fractal */
double max_iter;    /* number of iterations while calculating fractal */
int is_mandelbrot;  /* type of the fractal */
Complex c;          /* complex parameter used to calculate julia sets */

void parse_args(int argc, char *argv[]);
void init(Complex c_plane[h][w], int set[h][w]);
void calculate_fractal(Complex c_plane[h][w], int set[h][w]);
void show(int set[h][w]);

/* Arguments supplied via the command line:
 * 1) type of the fractal (m - Mandelbrot, j - Julia)
 * 2) image width
 * 3) image height
 * 4) zoom
 * 5) center x
 * 6) center y
 * 7) number of iterations to calculate
 * 8) (julia) parameter x
 * 9) (julia) parameter y
 */
int main(int argc, char *argv[])
{
    parse_args(argc, argv);

    Complex c_plane[h][w];  /* numbers on the complex plane */ 
    int set[h][w];          /* number of iterations before point diverges */

    init(c_plane, set);

    calculate_fractal(c_plane, set);

    show(set);

    return 0;
}

void parse_args(int argc, char *argv[])
{
    if (argc < 8) exit(1);

    is_mandelbrot = argv[1][0] == 'm' ? 1 : 0;
    w = atoi(argv[2]);
    h = atoi(argv[3]);
    scale = 1/atof(argv[4]);
    center.re = atof(argv[5]);
    center.im = atof(argv[6]);
    max_iter = atoi(argv[7]);

    if (!is_mandelbrot) {
        if (argc < 10) exit(2);

        c.re = atof(argv[8]);
        c.im = atof(argv[9]);
    }
}

/* Initializes the complex plane and divergence
 * Center of the plane lies at (center.re, center.im)
 * Each other point is offset according to scale in the appropriate direction
 */
void init(Complex c_plane[h][w], int set[h][w])
{
    int y, x;
    double m_w = ((double)w - 1)/2;  /* middle column (can be fractional) */
    double m_h = ((double)h - 1)/2;  /* middle row (can be fractional) */

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            c_plane[y][x].re = (x - m_w) * scale + center.re;
            c_plane[y][x].im = ((m_h - y) * scale + center.im) * FONT_RATIO;
            set[y][x] = -1;
        }
    }
}

void calculate_fractal(Complex c_plane[h][w], int set[h][w])
{
    int y, x, i;
    Complex z;

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            z = c_plane[y][x];
            for (i = 0; i < max_iter; ++i) {
                z = add(square(z), (is_mandelbrot ? c_plane[y][x] : c));
                if (cabs_sq(z) > 4) {
                    set[y][x] = i;
                    break;
                }
            }
        }
    }
}

void show(int set[h][w])
{
    int y, x;

    printf(REVERSE);
    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            if (set[y][x] == -1) {
                printf(BLACK);
            } else {
                switch(set[y][x] % 6) {
                case 0: printf(RED); break;
                case 1: printf(GREEN); break;
                case 2: printf(YELLOW); break;
                case 3: printf(BLUE); break;
                case 4: printf(MAGENTA); break;
                case 5: printf(CYAN); break;
                }
            }
            putchar(' ');
        }
        putchar('\n');
    }
    printf(RESET);
    fflush(stdout);
}
