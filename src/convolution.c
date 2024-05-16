#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m) {
    (void)result;
    (void)img;
    (void)w;
    (void)h;
    (void)matrix;
    (void)w_m;
    (void)h_m;


    int m = w_m/2, n = h_m/2;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            float sum = 0;
            int t = 0; 
            for (int l = (j-n); l < (j+n+1); l++)
            {
                for (int k = (i-m); k < (i+m+1); k++)
                {
                    sum = sum + matrix[t] * (get_pixel_value(img, w, h, k,l));
                    t++;
                }
            }
            result[i+j*w] = sum;
        }
    }
    return;
}
