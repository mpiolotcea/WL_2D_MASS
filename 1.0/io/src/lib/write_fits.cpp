/**
 * @file src/lib/write_fits.cpp
 * @date 12/14/15
 * @author user
 */

#include "io/write_fits.h"

namespace io {

std::string write_image(std::string pathname, float *array, std::string name, int naxis, long *naxes) {
  // this function writes a float array to a FITS image file
  TRACE_ENTER();
  // create new file
  fitsfile *fptr;
  int status = 0;
  fits_create_file(&fptr, pathname.c_str(), &status);
  if (status != 0) {
    // cannot create the file
    // likely, the file already exists
    // try to open it, delete it and create it anew
    // try to open the file
    status = 0;
    fits_open_file(&fptr, pathname.c_str(), READWRITE, &status);
    if (status != 0) {
      // cannot open the file, for some reason
      return FORMAT_STATUS(status);
    }
    // try to delete the file
    status = 0;
    fits_delete_file(fptr, &status);
    if (status != 0) {
      // cannot delete the file, for some reason
      return FORMAT_STATUS(status);
    }
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
  for (int i = 0; i < naxis; i++) {
    nelements = nelements * naxes[i];
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

std::string write_image_3D(std::string pathname_3D, float *array_2D_real, float *array_2D_imag, std::string name_3D, int naxis_2D, long *naxes_2D) {
  // this function writes a float array to a FITS image file
  TRACE_ENTER();
  // create new file
  fitsfile *fptr;
  int status = 0;
  fits_create_file(&fptr, pathname_3D.c_str(), &status);
  if (status != 0) {
    // cannot create the file
    // likely, the file already exists
    // try to open it, delete it and create it anew
    // try to open the file
    status = 0;
    fits_open_file(&fptr, pathname_3D.c_str(), READWRITE, &status);
    if (status != 0) {
      // cannot open the file, for some reason
      return FORMAT_STATUS(status);
    }
    // try to delete the file
    status = 0;
    fits_delete_file(fptr, &status);
    if (status != 0) {
      // cannot delete the file, for some reason
      return FORMAT_STATUS(status);
    }
    // try to create the file
    status = 0;
    fits_create_file(&fptr, pathname_3D.c_str(), &status);
    if (status != 0) {
      // cannot create the file, for some reason
      return FORMAT_STATUS(status);
    }
  }
  // create the primary array image
  int naxis_3D = naxis_2D+1;
  long *naxes_3D = new long [naxis_3D];
  for (int i = 0; i < naxis_2D; i++) {
    naxes_3D[i] = naxes_2D[i];
  }
  naxes_3D[naxis_3D-1] = 2;
  fits_create_img(fptr, FLOAT_IMG, naxis_3D, naxes_3D, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, name_3D.c_str(), array_2D_real, name_3D.c_str(), &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write the array of floats to the image
  long *fpixel = new long [naxis_3D];
  fpixel[0] = 1;
  fpixel[1] = 1;
  fpixel[2] = 1;
  long *lpixel = new long [naxis_3D];
  lpixel[0] = naxes_2D[0];
  lpixel[1] = naxes_2D[1];
  lpixel[2] = 1;
  fits_write_subset(fptr, TFLOAT, fpixel, lpixel, (void*)array_2D_real, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, name_3D.c_str(), array_2D_imag, name_3D.c_str(), &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // write the array of floats to the image
  fpixel[0] = 1;
  fpixel[1] = 1;
  fpixel[2] = 2;
  lpixel[0] = naxes_2D[0];
  lpixel[1] = naxes_2D[1];
  lpixel[2] = 2;
  fits_write_subset(fptr, TFLOAT, fpixel, lpixel, (void*)array_2D_imag, &status);
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
