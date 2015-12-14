/**
 * @file src/lib/read_fits.cpp
 * @date 12/14/15
 * @author user
 */

#include "io/read_fits.h"

namespace io {

std::string read_image(std::string pathname, double *&array, int &naxis, long *&naxes) {
  TRACE_ENTER();
  // open FITS image file in READONLY mode
  fitsfile *fptr;
  int status = 0;
  fits_open_image(&fptr, pathname.c_str(), READONLY, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // read number of HDUs in the file
  int nhdus = 0;
  fits_get_num_hdus(fptr, &nhdus, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect only one HDU in the file
  if (nhdus != 1) {
    std::ostringstream exit_oss;
    exit_oss << "nhdus is " << nhdus << ", not 1";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // read the type of the HDU
  int hdutype = 0;
  fits_movabs_hdu(fptr, nhdus, &hdutype, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect the HDU to be an image
  if (hdutype != IMAGE_HDU) {
    std::ostringstream exit_oss;
    exit_oss << "hdutype is " << hdutype << ", not IMAGE_HDU";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // read the type of data in the HDU
  int bitpix = 0;
  fits_get_img_type (fptr, &bitpix, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect the data to be floats
  if (bitpix != FLOAT_IMG) {
    std::ostringstream exit_oss;
    exit_oss << "bitpix is " << bitpix << ", not FLOAT_IMG";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // get the number of dimensions in the image
  naxis = 0;
  fits_get_img_dim (fptr, &naxis, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect 2 or 3 dimensions in the image
  if ((naxis < 2) || (naxis > 3)) {
    std::ostringstream exit_oss;
    exit_oss << "naxis is " << naxis << ", neither 2 nor 3";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // get the size of each dimension in the image
  naxes = new long[naxis];
  int maxdim = naxis;
  fits_get_img_size(fptr, maxdim, naxes, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // fits_read_subset
  long *fpixel = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    fpixel[naxe] = 1;
  }
  long *lpixel = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    lpixel[naxe] = naxes[naxe];
  }
  long *inc = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    inc[naxe] = 1;
  }
  float nulval = 0;
  long nelements = 1;
  for (int naxe = 0; naxe < naxis; naxe++) {
    nelements = nelements * naxes[naxe];
  }
  array = new double[nelements];
  int anynul = 0;
  fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, array, &anynul, &status);
  delete [] inc;
  delete [] lpixel;
  delete [] fpixel;
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // close the FITS image file
  fits_close_file(fptr, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  return "READ_OK";
}

std::string read_3D_image(std::string pathname, double **&array, int &naxis, long *&naxes) {
  TRACE_ENTER();
  // open FITS image file in READONLY mode
  fitsfile *fptr;
  int status = 0;
  fits_open_image(&fptr, pathname.c_str(), READONLY, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // read number of HDUs in the file
  int nhdus = 0;
  fits_get_num_hdus(fptr, &nhdus, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect only one HDU in the file
  if (nhdus != 1) {
    std::ostringstream exit_oss;
    exit_oss << "nhdus is " << nhdus << ", not 1";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // read the type of the HDU
  int hdutype = 0;
  fits_movabs_hdu(fptr, nhdus, &hdutype, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect the HDU to be an image
  if (hdutype != IMAGE_HDU) {
    std::ostringstream exit_oss;
    exit_oss << "hdutype is " << hdutype << ", not IMAGE_HDU";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // read the type of data in the HDU
  int bitpix = 0;
  fits_get_img_type (fptr, &bitpix, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect the data to be floats
  if (bitpix != FLOAT_IMG) {
    std::ostringstream exit_oss;
    exit_oss << "bitpix is " << bitpix << ", not FLOAT_IMG";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // get the number of dimensions in the image
  naxis = 0;
  fits_get_img_dim (fptr, &naxis, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // we expect 3 dimensions in the image
  if (naxis != 3) {
    std::ostringstream exit_oss;
    exit_oss << "naxis is " << naxis << ", not 3";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // get the size of each dimension in the image
  naxes = new long[naxis];
  int maxdim = naxis;
  fits_get_img_size(fptr, maxdim, naxes, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // fits_read_subset
  long *fpixel = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    fpixel[naxe] = 1;
  }
  long *lpixel = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    lpixel[naxe] = naxes[naxe];
  }
  long *inc = new long[naxis];
  for (int naxe = 0; naxe < naxis; naxe++) {
    inc[naxe] = 1;
  }
  float nulval = 0;
  long nelements = 1;
  for (int naxe = 0; naxe < naxis-1; naxe++) {
    nelements = nelements*naxes[naxe];
  }
  array = new double*[2];
  array[0] = new double[nelements];
  array[1] = new double[nelements];
  int anynul = 0;
  fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, &array[0][0], &anynul, &status);
  delete [] inc;
  delete [] lpixel;
  delete [] fpixel;
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  // close the FITS image file
  fits_close_file(fptr, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  return "READ_OK";
}

} // io namespace
