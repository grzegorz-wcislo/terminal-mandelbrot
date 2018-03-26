#include <cstdio>

struct Complex {
    float re, im;

    Complex square() {
        return {re*re - im*im, 2*re*im};
    }

    Complex operator+(Complex c) {
        return {re + c.re, im + c.im};
    }

    int square_absolute() {
        return re*re + im*im;
    }
};

const int width = 123;
const int heigth = 41;

const float bottom_y = -1;
const float left_x = -2.2;
const float x_len = 3;
const float y_len = 2;

Complex complex_plane[heigth][width];
int mandelbrot_set[heigth][width];

int in_set = width*heigth;

void init_complex_plane() {
    for (int y = 0; y < heigth; ++y)
        for(int x = 0; x < width; ++x)
            complex_plane[y][x] = {
                float(x)/(width-1)*(x_len) + left_x,
                float(y)/(heigth-1)*(y_len) + bottom_y
            };
}

int mandelbrot(int iterations) {
    int new_in_set = width*heigth;
    for (int y = 0; y < heigth; ++y)
        for(int x = 0; x < width; ++x) {
            mandelbrot_set[y][x] = -1;
            Complex z = complex_plane[y][x];
            for (int i = 0; i < iterations; ++i) {
                z = z.square() + complex_plane[y][x];
                if (z.square_absolute() > 4) {
                    mandelbrot_set[y][x] = float(i)/iterations*7;
                    new_in_set--;
                    break;
                }
            }
        }
    if (new_in_set != in_set) {
        in_set = new_in_set;
        return true;
    } else {
        return false;
    }
}

void show_plane() {
    for (int y = 0; y < heigth; ++y) {
        for(int x = 0; x < width; ++x) {
            if (mandelbrot_set[y][x] == -1) {
                printf("\033[0m");
                putchar('#');
                printf("\033[0m");
            }
            else {
                switch(mandelbrot_set[y][x]) {
                    case 0:
                        printf("\033[31m");
                        break;
                    case 1:
                        printf("\033[32m");
                        break;
                    case 2:
                        printf("\033[33m");
                        break;
                    case 3:
                        printf("\033[34m");
                        break;
                    case 4:
                        printf("\033[35m");
                        break;
                    case 5:
                        printf("\033[36m");
                        break;
                    case 6:
                        printf("\033[36m");
                        break;
                }
                putchar('@');
                printf("\033[0m");
            }
        }
        putchar('\n');
    }
}

int main() {
    init_complex_plane();
    for (int i = 5; mandelbrot(i); ++i)
        printf("%d", i);
    show_plane();
    return 0;
}
