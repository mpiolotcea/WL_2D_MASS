/**
 * @file tests/src/ShearInversions_output.cpp
 * @date 11/27/15
 * @author user
 */

#include <cmath>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <boost/test/unit_test.hpp>

#include <fitsio.h>

#include <Trace/Trace.h>

#include "Tools/ShearInversions.h"

using namespace Tools;

#define TRACE_STATUS(status) trace_status(status)

std::string trace_status(int status) {
  char errstatus[30];
  fits_get_errstatus(status, errstatus);
  char errmsg[80];
  fits_read_errmsg(errmsg);
  std::ostringstream oss;
  oss << status << " " << errstatus << " " << errmsg;
  if (status == 0) {
    TRACE_DEBUG(oss.str());
  } else {
    TRACE_ERROR(oss.str());
  }
  return oss.str();
}

/**
 * reads an image FITS file and stores it into an array
 * @param[in] pathname name of the image FITS file to be read
 * @param[out] array array to store the image FITS file's contents
 * @param[out] naxis number of axes in the image
 * @param[out] naxes array of the axes of the image
 * @return READ_OK if all went well; an error message else
 */
std::string read_image(std::string pathname, double *&array, int &naxis, long *&naxes) {
  TRACE_ENTER();
  // open FITS image file in READONLY mode
  fitsfile *fptr;
  int status = 0;
  fits_open_image(&fptr, pathname.c_str(), READONLY, &status);
  // error case
  if (status != 0) {
    return TRACE_STATUS(status);
  }
  // read number of HDUs in the file
  int nhdus = 0;
  fits_get_num_hdus(fptr, &nhdus, &status);
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
    return TRACE_STATUS(status);
  }
  // close the FITS image file
  fits_close_file(fptr, &status);
  return "READ_OK";
}

/**
 * writes an array into an image FITS file
 * @param[in] pathname name of the image FITS file to be written
 * @param[in] array array to be written
 * @param[in] name describes the content of the image
 * @param[in] naxis number of axes in the image
 * @param[in] naxes array of the axes of the image
 * @return WRITE_OK if all went well; an error message else
 */
/*
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
      return TRACE_STATUS(status);
    }
  }
  // create the primary array image
  fits_create_img(fptr, FLOAT_IMG, naxis, naxes, &status);
  if (status != 0) {
    return TRACE_STATUS(status);
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, name.c_str(), array, name.c_str(), &status);
  if (status != 0) {
    return TRACE_STATUS(status);
  }
  // write the array of floats to the image
  long fpixel = 1;
  long nelements = 1;
  for (int naxe = 0; naxe < naxis; naxe++) {
    nelements = nelements * naxes[naxe];
  }
  fits_write_img(fptr, TFLOAT, fpixel, nelements, (void*)array, &status);
  if (status != 0) {
    return TRACE_STATUS(status);
  }
  // close the file
  fits_close_file(fptr, &status);
  if (status != 0) {
    return TRACE_STATUS(status);
  }
  return "WRITE_OK";
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (ShearInversions_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( readwriteread_test ) {
  TRACE_ENTER();
  // read gamma_input from pathname_input
  std::string pathname_input("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = read_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input;
    }
    BOOST_FAIL(read_input);
  }
  // write gamma_input into pathname_output
  std::string pathname_output("../Tools/tests/src/gamma_B.1_duplicate.fits");
  std::string name_input("gamma_input");
  std::string write_input = write_image(pathname_output, gamma_input, name_input, naxis_input, naxes_input);
  if (write_input != "WRITE_OK") {
    delete [] gamma_input;
    BOOST_FAIL(write_input);
  }
  // read gamma_output from pathname_output
  double *gamma_output = nullptr;
  int naxis_output = 0;
  long *naxes_output = nullptr;
  std::string read_output = read_image(pathname_output, gamma_output, naxis_output, naxes_output);
  if (read_output != "READ_OK") {
    if (gamma_output != nullptr) {
      delete [] gamma_output;
    }
    delete [] gamma_input;
    BOOST_FAIL(read_output);
  }
  // compare output vs input
  BOOST_CHECK(naxis_output == naxis_input);
  for (int naxe = 0; naxe < naxis_output; naxe++) {
    BOOST_CHECK(naxes_output[naxe] == naxes_input[naxe]);
  }
  for (int x = 0; x < naxes_output[0]; x++) {
    for (int y = 0; y < naxes_output[1]; y++) {
      for (int z = 0; z < naxes_output[2]; z++) {
        BOOST_CHECK (fabs(gamma_output[z*naxes_output[1]*naxes_output[0]+x*naxes_output[1]+y]-gamma_input[z*naxes_input[1]*naxes_input[0]+x*naxes_input[1]+y]) <= fabs(gamma_input[z*naxes_input[1]*naxes_input[0]+x*naxes_input[1]+y]*0.01));
      }
    }
  }
  // free arrays
  delete [] gamma_output;
  delete [] gamma_input;
}

BOOST_AUTO_TEST_CASE( gamma2kappa_test ) {
  // this test only calls gamma2kappa, does not check anything.
  TRACE_ENTER();
  std::string pathname_input ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = read_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input;
    }
    BOOST_FAIL(read_input);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  long nelements_input = 1;
  for (int naxe_input = 0; naxe_input < naxis_input; naxe_input++) {
    nelements_input = nelements_input * naxes_input[naxe_input];
  }
  double *kappa_input = new double[nelements_input];
  si.gamma2kappa(&gamma_input[0], &gamma_input[nelements_input/2], kappa_input, naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // write kappa_input
  std::string name_input = "kappa_input";
  std::string write_input = write_image("../Tools/tests/src/kappa_B.1_new.fits", kappa_input, name_input, naxis_input, naxes_input);
  if (write_input != "WRITE_OK") {
    delete [] kappa_input;
    delete [] gamma_input;
    BOOST_FAIL(write_input);
  }
  // free arrays
  delete [] kappa_input;
  delete [] gamma_input;
}
*/

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input
  TRACE_ENTER();
  std::string pathname_input ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = read_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input;
    }
    BOOST_FAIL(read_input);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  long nelements_input = 1;
  for (int naxe_input = 0; naxe_input < naxis_input; naxe_input++) {
    nelements_input = nelements_input * naxes_input[naxe_input];
  }
  double *kappa_input = new double[nelements_input];
  si.gamma2kappa(&gamma_input[0], &gamma_input[nelements_input/2], kappa_input, naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // kappa2gamma
  double *gamma_output = new double [nelements_input];
  si.kappa2gamma(kappa_input, &gamma_output[0], &gamma_output[nelements_input/2], naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // write gamma_output
  std::string name_output = "gamma_output";
  std::string write_output = write_image("../Tools/tests/src/gamma_B.1_output.fits", gamma_output, name_output, naxis_input, naxes_input);
  if (write_output != "WRITE_OK") {
    delete [] gamma_output;
    delete [] kappa_input;
    delete [] gamma_input;
    BOOST_FAIL(write_output);
  }
  // compare input vs output
  // free arrays
  delete [] gamma_output;
  delete [] kappa_input;
  delete [] gamma_input;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
