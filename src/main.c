#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
    /**
     * Parse arguments. The parsed image file name and threshold are available
     * in the image_file_name and threshold global variables (see argparser.h).
     */
    parse_arguments(argc, argv);
    printf("Computing edges for image file %s with threshold %i\n",
           image_file_name, threshold);

    /**
     * Read Image from given file.
     *
     * If the input file is broken terminate with return value 1.
     *
     * Hint: The width and height of the image have to be accessible in the
     * scope of this function.
     */
    // TODO: Implement me!

    float *img;
    int w, h;
    img = read_image_from_file(image_file_name, &w, &h);
    if (img == NULL)
    {
       return(1);
    }

    /**
     * Blur the image by using convolve with the given Gaussian kernel matrix
     * gaussian_k (defined in gaussian_kernel.h). The width of the matrix is
     * gaussian_w, the height is gaussian_h.
     *
     * Afterwards, write the resulting blurred image to the file out_blur.pgm.
     */
    // TODO: Implement me!

    float *result;
    result = array_init(w*h);
    const char filename[13] = {'o', 'u', 't', '_', 'b', 'l', 'u', 'r', '.', 'p', 'g', 'm', '\0'};
    convolve (result, img,w,h, gaussian_k, gaussian_w, gaussian_h);
    array_destroy(img);
    write_image_to_file(result,w,h, filename);

    /**
     * Compute the derivation of the blurred image computed above in both x and
     * y direction.
     *
     * Afterwards, rescale both results and write them to the files out_d_x.pgm
     * and out_d_y.pgm respectively.
     */
    // TODO: Implement me!
    float *x_dev, *y_dev, *x_rescal, *y_rescal;
    const char filex[12] = {'o', 'u', 't', '_', 'd', '_', 'x', '.', 'p', 'g', 'm', '\0'};
    const char filey[12] = {'o', 'u', 't', '_', 'd', '_', 'y', '.', 'p', 'g', 'm', '\0'};
    x_rescal = array_init(w*h);
    y_rescal = array_init(w*h);
    x_dev = array_init(w*h);
    y_dev = array_init(w*h);
    derivation_x_direction(x_dev, result,w,h);
    derivation_y_direction(y_dev, result,w,h);
    scale_image(x_rescal, x_dev,w,h);
    scale_image(y_rescal, y_dev,w,h);
    write_image_to_file(x_rescal,w,h, filex);
    write_image_to_file(y_rescal,w,h, filey);
    array_destroy(x_rescal);
    array_destroy(y_rescal);

    /**
     * Compute the gradient magnitude of the blurred image by using the
     * (unscaled!) derivations in x- and y-direction computed earlier.
     *
     * Afterwards, rescale the result and write it to out_gm.pgm.
     */
    // TODO: Implement me!

    gradient_magnitude(result, x_dev, y_dev,w,h);
    float *res;
    res = array_init(w*h);
    scale_image(res, result,w,h);
    const char filegm[11] = {'o', 'u', 't', '_', 'g', 'm', '.', 'p', 'g', 'm', '\0'};
    write_image_to_file(res,w,h, filegm);
    array_destroy(x_dev);
    array_destroy(y_dev);
    array_destroy(res);
    /**
     * Apply the threshold to the gradient magnitude.
     * Then write the result to the file out_edges.pgm.
     */
    // TODO: Implement me!

    apply_threshold(result, w, h, threshold);
    const char fileedges[14] = {'o', 'u', 't', '_', 'e', 'd', 'g', 'e', 's', '.', 'p', 'g', 'm', '\0'};
    write_image_to_file(result,w,h, fileedges);
    array_destroy(result);
    /**
     * Remember to free dynamically allocated memory when it is no longer used!
     */
}
