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


} /* namespace io */


#endif
