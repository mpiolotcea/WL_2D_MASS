/**
 * @file io/read_fits.h
 * @date 12/14/15
 * @author user
 */

#ifndef _IO_READ_FITS_H
#define _IO_READ_FITS_H

#include <string>

#include <fitsio.h>

#include <Trace/Trace.h>

namespace io {

/**
 * reads an image FITS file and stores it into a float array
 * @param[in] pathname name of the image FITS file to be read
 * @param[out] array float array to store the image FITS file's contents
 * @param[out] naxis number of axes in the image
 * @param[out] naxes array of the axes of the image
 * @return READ_OK if all went well; an error message else
 */
std::string read_image(std::string pathname, float *&array, int &naxis, long *&naxes);

/**
 * splits a 3D image with two sub-images into two 2D images
 * and stores them into two float arrays
 * @param[in] pathname_3D name of the image FITS file to be read
 * @param[out] array_2D_real float array to store the 2D-image's contents
 * @param[out] array_2D_imag float array to store the 2D-image's contents
 * @param[out] naxis_2D number of axes in the 2D-image
 * @param[out] naxes_2D array of the axes of the 2D-image
 * @return READ_OK if all went well; an error message else
 */
std::string read_image_3D(std::string pathname_3D, float *&array_2D_real, float *&array_2D_imag, int &naxis_2D, long *&naxes_2D);


} /* namespace io */

#endif
