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
  for (int i = 0; i < naxis; i++) {
    fpixel[i] = 1;
  }
  long *lpixel = new long[naxis];
  for (int i = 0; i < naxis; i++) {
    lpixel[i] = naxes[i];
  }
  long *inc = new long[naxis];
  for (int i = 0; i < naxis; i++) {
    inc[i] = 1;
  }
  float nulval = 0;
  long nelements = 1;
  for (int i = 0; i < naxis; i++) {
    nelements = nelements * naxes[i];
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

std::string read_image_3D(std::string pathname_3D, double *&array_2D_1, double *&array_2D_2, int &naxis_2D, long *&naxes_2D) {
  TRACE_ENTER();
  // open FITS image file in READONLY mode
  fitsfile *fptr;
  int status = 0;
  fits_open_image(&fptr, pathname_3D.c_str(), READONLY, &status);
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
  int naxis_3D = 0;
  fits_get_img_dim (fptr, &naxis_3D, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  naxis_2D = naxis_3D-1;
  // we expect 3 dimensions in the image
  if (naxis_3D != 3) {
    std::ostringstream exit_oss;
    exit_oss << "naxis_3D is " << naxis_3D << ", not 3";
    TRACE_ERROR(exit_oss.str());
    return exit_oss.str();
  }
  // get the size of each dimension in the image
  long *naxes_3D = new long[naxis_3D];
  int maxdim = naxis_3D;
  fits_get_img_size(fptr, maxdim, naxes_3D, &status);
  if (status != 0) {
    return FORMAT_STATUS(status);
  }
  naxes_2D = new long[naxis_2D];
  for (int i = 0; i < naxis_2D; i++) {
    naxes_2D[i] = naxes_3D[i];
  }
  // we expect two sub-images in the third dimension
  if (naxes_3D[2] != 2) {
    std::ostringstream exit_oss;
    exit_oss << "naxes_2D[2] is " << naxes_2D[2] << ", not 2";
    TRACE_ERROR (exit_oss.str());
    return exit_oss.str();
  }
  // fits_read_subset
  long *fpixel = new long[naxis_3D];
  for (int i = 0; i < naxis_3D; i++) {
    fpixel[i] = 1;
  }
  long *lpixel = new long[naxis_3D];
  for (int i = 0; i < naxis_3D; i++) {
    lpixel[i] = naxes_3D[i];
  }
  long *inc = new long[naxis_3D];
  for (int i = 0; i < naxis_3D; i++) {
    inc[i] = 1;
  }
  float nulval = 0;
  long nelements_2D = 1;
  for (int i = 0; i < naxis_2D; i++) {
    nelements_2D = nelements_2D*naxes_2D[i];
  }
  int anynul = 0;
  // read array_2D_1
  array_2D_1 = new double[nelements_2D];
  fpixel[2] = 1;
  lpixel[2] = 1;
  fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, array_2D_1, &anynul, &status);
  // read array_2D_2
  array_2D_2 = new double[nelements_2D];
  fpixel[2] = 2;
  lpixel[2] = 2;
  fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, array_2D_2, &anynul, &status);
  // free arrays
  delete [] inc;
  delete [] lpixel;
  delete [] fpixel;
  // test read result
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
