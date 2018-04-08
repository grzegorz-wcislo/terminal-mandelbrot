#include <stdlib.h>
#include <stdio.h>

#define RESET "\033[0m"
#define REVERSE "\033[7m"
#define WHITE "\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

int w;
int h;
double scale;
double x_offset;
double y_offset;
double max_iter;

typedef struct {
    double re, im;
} Complex;

void init(Complex[h][w], int[h][w]);
void calculate(Complex[h][w], int[h][w], int);
void show(int[h][w]);

Complex square(Complex);
Complex add(Complex, Complex);
double cabs_sq(Complex);

int main(int argc, char *argv[]) {
    w = atoi(argv[1]);
    h = atoi(argv[2]);
    scale = 1/(double)atol(argv[3]);
    x_offset = atof(argv[4]);
    y_offset = atof(argv[5]);
    max_iter = atoi(argv[6]);

    int set[h][w];
    Complex c_plane[h][w];
    init(c_plane, set);
    calculate(c_plane, set, max_iter);

    show(set);
    return 0;
}

void init(Complex c_plane[h][w], int set[h][w]) {
    int i, j;
    double m_w = ((double)w - 1)/2;
    double m_h = ((double)h - 1)/2;
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            c_plane[i][j].re = (j - m_w) * scale + x_offset;
            c_plane[i][j].im = ((m_h - i) * scale + y_offset) * 2;
            set[i][j] = -1;
        }
    }
}

void calculate(Complex c_plane[h][w], int set[h][w], int iter) {
    int i, j, k;
    Complex z;
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            z = c_plane[i][j];
            for (k = 0; k < iter; ++k) {
                z = add(square(z), c_plane[i][j]);
                if (cabs_sq(z) > 4) {
                    set[i][j] = k;
                    break;
                }
            }
        }
    }
}

void show(int set[h][w]) {
    int i, j;
    printf(REVERSE);
    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            if (set[i][j] == -1) {
                printf(WHITE);
            } else {
                switch(set[i][j] % 6) {
                case 0:
                    printf(RED);
                    break;
                case 1:
                    printf(GREEN);
                    break;
                case 2:
                    printf(YELLOW);
                    break;
                case 3:
                    printf(BLUE);
                    break;
                case 4:
                    printf(MAGENTA);
                    break;
                case 5:
                    printf(CYAN);
                    break;
                }
            }
            putchar(' ');
        }
        putchar('\n');
    }
    printf(RESET);
    fflush(stdout);
}

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
