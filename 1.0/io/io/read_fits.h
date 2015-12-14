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
 * reads an image FITS file and stores it into a double array
 * @param[in] pathname name of the image FITS file to be read
 * @param[out] array double array to store the image FITS file's contents
 * @param[out] naxis number of axes in the image
 * @param[out] naxes array of the axes of the image
 * @return READ_OK if all went well; an error message else
 */
std::string read_image(std::string pathname, double *&array, int &naxis, long *&naxes);

/**
 * reads an image FITS file and stores it into a double array
 * @param[in] pathname name of the image FITS file to be read
 * @param[out] array double array to store the image FITS file's contents
 * @param[out] naxis number of axes in the image
 * @param[out] naxes array of the axes of the image
 * @return READ_OK if all went well; an error message else
 */
std::string read_3D_image(std::string pathname, double **&array, int &naxis, long *&naxes);


} /* namespace io */


#endif