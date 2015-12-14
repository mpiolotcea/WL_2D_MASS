/**
 * @file src/lib/write_fits.cpp
 * @date 12/14/15
 * @author user
 */

#include "io/write_fits.h"

namespace io {

std::string write_image(std::string pathname, double *array, std::string name, int naxis, long *naxes) {
  // this function writes a double array to a FITS image file
  TRACE_ENTER();
  // create new file
  fitsfile *fptr;
  int status = 0;
  fits_create_file(&fptr, pathname.c_str(), &status);
  if (status != 0) {
    // cannot create the file
    // likely, the file already exists
    // open it and delete it
    status = 0;
    fits_open_file(&fptr, pathname.c_str(), READWRITE, &status);
    status = 0;
    fits_delete_file(fptr, &status);
    // try to create the file
    status = 0;
    fits_create_file(&fptr, pathname.c_str(), &status);
    if (status != 0) {
      // cannot create the file, for some reason
      return FORMAT_STATUS(status);
    }
  }
  // create the primary array image
  fits_create_img(fptr, FLOAT_IMG, naxis, naxes, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, name.c_str(), array, name.c_str(), &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write the array of floats to the image
  long fpixel = 1;
  long nelements = 1;
  for (int naxe = 0; naxe < naxis; naxe++) {
    nelements = nelements * naxes[naxe];
  }
  {
    std::ostringstream oss;
    oss << "nelements = " << nelements;
    TRACE_DEBUG(oss.str());
  }
  fits_write_img(fptr, TFLOAT, fpixel, nelements, (void*)array, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // close the file
  fits_close_file(fptr, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  return "WRITE_OK";
}

} // io namespace