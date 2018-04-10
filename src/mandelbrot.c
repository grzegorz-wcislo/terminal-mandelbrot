#include <stdlib.h>
#include <stdio.h>
#include "complex.h"

#define RESET   "\033[0m"
#define REVERSE "\033[7m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define FONT_RATIO 1.8

int w;
int h;
double scale;
double x_offset;
double y_offset;
double max_iter;
Complex c;

void init(Complex[h][w], int[h][w]);
void calculate_mandelbrot(Complex[h][w], int[h][w], int);
void calculate_julia(Complex[h][w], int[h][w], int);
void show(int[h][w]);

int main(int argc, char *argv[]) {
    int is_mandelbrot = argv[1][0] == 'm' ? 1 : 0;
    w = atoi(argv[2]);
    h = atoi(argv[3]);
    scale = 1/atof(argv[4]);
    x_offset = atof(argv[5]);
    y_offset = atof(argv[6]);
    max_iter = atoi(argv[7]);

    if (!is_mandelbrot) {
        c.re = atof(argv[8]);
        c.im = atof(argv[9]);
    }

    int set[h][w];
    Complex c_plane[h][w];

    init(c_plane, set);
    if (is_mandelbrot) 
        calculate_mandelbrot(c_plane, set, max_iter);
    else 
        calculate_julia(c_plane, set, max_iter);
    show(set);

    return 0;
}

void init(Complex c_plane[h][w], int set[h][w]) {
    int y, x;
    double m_w = ((double)w - 1)/2;
    double m_h = ((double)h - 1)/2;

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            c_plane[y][x].re = (x - m_w) * scale + x_offset;
            c_plane[y][x].im = ((m_h - y) * scale + y_offset) * FONT_RATIO;
            set[y][x] = -1;
        }
    }
}

void calculate_mandelbrot(Complex c_plane[h][w], int set[h][w], int iter) {
    int y, x, i;
    Complex z;

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            z = c_plane[y][x];
            for (i = 0; i < iter; ++i) {
                z = add(square(z), c_plane[y][x]);
                if (cabs_sq(z) > 4) {
                    set[y][x] = i;
                    break;
                }
            }
        }
    }
}

void calculate_julia(Complex c_plane[h][w], int set[h][w], int iter) {
    int y, x, i;
    Complex z;

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            z = c_plane[y][x];
            for (i = 0; i < iter; ++i) {
                z = add(square(z), c);
                if (cabs_sq(z) > 4) {
                    set[y][x] = i;
                    break;
                }
            }
        }
    }
}

void show(int set[h][w]) {
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
