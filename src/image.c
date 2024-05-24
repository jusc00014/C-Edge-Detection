#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float maxi(const float *img, int wh);
float mini(const float *img, int wh);

void apply_threshold(float *img, int w, int h, int T) {
    (void)img;
    (void)w;
    (void)h;
    (void)T;
    for (int i = 0; i < w*h; i++)
    {
        img[i] = (img[i] > T)*255.0f;
    }
    return;
}

void scale_image(float *result, const float *img, int w, int h) {
    (void)result;
    (void)img;
    (void)w;
    (void)h;
    float max = 0.0f, min = 255.0f, scale, l;
    int k = w*h;
    max = maxi(img, k);
    min = mini(img, k);
    l = (max - min);
    scale = 255.0f/l;
//    printf("%f\n", scale);
    if (l)
    {
        for(int i = 0; i<k; i++)
        {
            result[i] = ((img[i] - min) * scale);
        }
    }
    else
    {
         for(int i = 0; i<k; i++)
        {
            result[i] = 0.0f;
        }
    }
    return;
}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    (void)img;
    (void)w;
    (void)h;
    (void)x;
    (void)y;
    if (x < 0)
    {
        x = -x-1;
    }
    else if (x >= w)
    {
        x = 2*w-x-1;
    }

    if (y < 0)
    {
        y = -y-1;
    }
    else if (y >= h)
    {
        y = 2*h-y-1;
    }
    return(img[x+y*w]);
}

float *array_init(int size) {
    (void)size;
    float *x;
    x = (float *) calloc(size, sizeof(float));
    if (x == NULL)
    {
        return(NULL);
    } 
    return(x);
}

void array_destroy(float *m) {
    (void)m;
    free(m);
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    (void)filename;
    (void)w;
    (void)h;

    FILE *data;
    data = fopen(filename, "r");
    if (data == NULL)
    {
        return(NULL);

    }
    char y[4];
    if (fscanf(data, "%3s", y) != 1)
    {
        fclose(data);
        return(NULL);
    };
    if (strcmp(y, "P2"))
    {
        fclose(data);
        return(NULL);
    }
    if (fscanf(data, "%d", w) != 1)
    {
        fclose(data);
        return(NULL);
    }
    if (fscanf(data, "%d", h) != 1)
    {
        fclose(data);
        return(NULL);
    }
    if (*w < 0 || *h < 0)                           //Wenn negative Zeile oder Spaltenzahl
    {
        fclose(data);
        return(NULL);
    }
    float k;
    if (fscanf(data, "%f", &k) != 1)
    {
        fclose(data);
        return(NULL);
    }
    if (k < 0.0f || k > 255.0f)
    {
        fclose(data);
        return(NULL);
    }
    float *x;
    x = array_init((*w)*(*h));
    if (x == NULL)
    {
        fclose(data);
        return(NULL);
    }
    for (int i = 0; i < (*w)*(*h); i++)
    {
            if (fscanf(data, "%f", &x[i]) != 1)      //Wenn weniger Werte als angegeben
            {
                array_destroy(x);
                fclose(data);
                return(NULL);
            }
            if (0.0f > x[i] || 255.0f < x[i])
            {
                array_destroy(x);
                fclose(data);
                return(NULL);
            }
    }
    if (fscanf(data, "%f", &k) == 1)                 //Wenn mehr Werte als angegeben
    {
        fclose(data);
        return(NULL);
    }
    fclose(data);
    return(x);
}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
    (void)img;
    (void)w;
    (void)h;
    (void)filename;

    FILE *data;
    data = fopen(filename, "w");
    if (data == NULL)
    {
        return;
    }
    char y[2] = {'P', '2'};
    fprintf(data, "%s ", y);
    char z = '\n';
    fprintf(data, "%c", z);
    fprintf(data, "%d ", w);
    fprintf(data, "%c", z);
    fprintf(data, "%d ", h);
    fprintf(data, "%c", z);
    fprintf(data, "%d ", 255);
    fprintf(data, "%c", z);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            fprintf(data, "%d ", (int)(img[j+i*w]));
        }
        fprintf(data, "%c", z);
    }
    fclose(data);
    return;
}



float maxi(const float *img, int wh)
{
    (void)img;
    (void)wh;
    float k = 0;
    for(int i = 0; i < wh; i++)
    {
        if (k < img[i])
        {
            k = img[i];
        }
    }
    return(k);
}

float mini(const float *img, int wh)
{
    (void)img;
    (void)wh;
    float k = 255.0f;
    for(int i = 0; i < wh; i++)
    {
        if (k > img[i])
        {
            k = img[i];
        }
    }
    return(k);
}
