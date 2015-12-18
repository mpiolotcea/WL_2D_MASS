/**
 * @file io/write_fits.h
 * @date 12/14/15
 * @author user
 */

#ifndef _IO_WRITE_FITS_H
#define _IO_WRITE_FITS_H

#include <string>

#include <fitsio.h>

#include <Trace/Trace.h>

namespace io {

/**
 * writes a double array into an image FITS file
 * @param[in] pathname name of the image FITS file to be written
 * @param[in] array double array to be written into the FITS file
 * @param[in] name describes the content of the image
 * @param[in] naxis number of axes in the image
 * @param[in] naxes array of the axes of the image
 * @return WRITE_OK if all went well; an error message else
 */
std::string write_image(std::string pathname, double *array, std::string name, int naxis, long *naxes);

/**
 *
 * @param pathname_3D
 * @param array_2D_real
 * @param array_2D_imag
 * @param name_3D
 * @param naxis_2D
 * @param naxes_2D
 * @return
 */
std::string write_image_3D(std::string pathname_3D, double *array_2D_real, double *array_2D_imag, std::string name_3D, int naxis_2D, long *naxes_2D);

} /* namespace io */

#endif
