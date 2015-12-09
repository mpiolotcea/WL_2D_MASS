/**
 * @file tests/src/ShearInversions_test.cpp
 * @date 11/27/15
 * @author user
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include <boost/test/unit_test.hpp>

#include <fitsio.h>

#include <Trace/Trace.h>

#include "Tools/ShearInversions.h"

using namespace Tools;

#define TRACE_STATUS(status) status_is_not_zero(status)

std::string status_is_not_zero(int status) {
  char errstatus[30];
  fits_get_errstatus(status, errstatus);
  char errmsg[80];
  fits_read_errmsg(errmsg);
  std::ostringstream oss;
  oss << status << " " << errstatus << " " << errmsg;
  TRACE_DEBUG(oss);
  return oss.str();
}

std::string read_gamma(const std::string &pathname, double *&gammaE, int &Nx, int &Ny, int &Nz) {
  TRACE_ENTER();
  // open FITS file in READONLY mode
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
  {
    std::ostringstream oss;
    oss << "nhdus = " << nhdus;
    TRACE_DEBUG(oss.str());
  }
  // we expect only one HDU in the file
  if (nhdus != 1) {
    std::ostringstream exit_oss;
    exit_oss << "nhdus is " << nhdus << ", not 1";
    TRACE_DEBUG(exit_oss);
    TRACE_EXIT();
    return exit_oss.str();
  }
  // read the HDUs of the file
  for (int hdunum = 1; hdunum < nhdus+1; hdunum++) {
    {
      std::ostringstream oss;
      oss << "hdunum = " << hdunum;
      TRACE_DEBUG(oss);
    }
    // read the type of the HDU
    int hdutype = 0;
    fits_movabs_hdu(fptr, hdunum, &hdutype, &status);
    if (status == END_OF_FILE) {
      status = 0;
      break;
    }
    {
      std::ostringstream oss;
      oss << "hdutype = " << hdutype;
      TRACE_DEBUG(oss);
    }
    if (hdutype != IMAGE_HDU) {
      std::ostringstream exit_oss;
      exit_oss << "hdutype is " << hdutype << ", not IMAGE_HDU";
      TRACE_DEBUG(exit_oss);
      TRACE_EXIT();
      return exit_oss.str();
    }
    // read the type of data in the HDU
    int bitpix = 0;
    fits_get_img_type (fptr, &bitpix, &status);
    {
      std::ostringstream oss;
      oss << "bitpix = " << bitpix;
      TRACE_DEBUG(oss);
    }
    if (bitpix != FLOAT_IMG) {
      std::ostringstream exit_oss;
      exit_oss << "bitpix is " << bitpix << ", not FLOAT_IMG";
      TRACE_DEBUG(exit_oss);
      TRACE_EXIT();
      return exit_oss.str();
    }
    // get the number of dimensions in the image
    int naxis = 0;
    fits_get_img_dim (fptr, &naxis, &status);
    {
      std::ostringstream oss;
      oss << "naxis = " << naxis;
      TRACE_DEBUG(oss);
    }
    if (naxis != 3) {
      std::ostringstream exit_oss;
      exit_oss << "naxis is " << naxis << ", not 3";
      TRACE_DEBUG(exit_oss);
      TRACE_EXIT();
      return exit_oss.str();
    }
    // get the size of each dimension in the image
    long *naxes = new long[naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr, maxdim, naxes, &status);
    Nx = naxes[0];
    Ny = naxes[1];
    Nz = naxes[2];
    delete [] naxes;
    {
      std::ostringstream oss;
      oss << "Nx = " << Nx << " Ny = " << Ny << " Nz = " << Nz;
      TRACE_DEBUG(oss);
    }
    // fits_read_subset
    long fpixel[3];
    fpixel[0] = 1;
    fpixel[1] = 1;
    fpixel[2] = 1;
    long lpixel[3];
    lpixel[0] = Nx;
    lpixel[1] = Ny;
    lpixel[2] = Nz;
    long inc[3];
    inc[0] = 1;
    inc[1] = 1;
    inc[2] = 1;
    float nulval = 0;
    gammaE = new double[Nx*Ny*Nz];
    {
      std::ostringstream oss;
      oss << "sizeof(gammaE) = " << sizeof(gammaE);
      TRACE_DEBUG(oss);
    }
    int anynul = 0;
    {
      std::ostringstream oss;
      oss << "fptr = " << fptr << " TFLOAT = " << TFLOAT << " fpixel = " << fpixel << " lpixel = " << lpixel
          << " inc = " << inc << " nulval = " << nulval << " gammaE = " << gammaE << " anynul = " << anynul
          << " status = " << status;
      TRACE_DEBUG(oss);
    }
    fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, gammaE, &anynul, &status);
    if (status != 0) {
      std::string exit_string = TRACE_STATUS(status);
      TRACE_EXIT();
      return TRACE_STATUS(status);
    }
    int nb_zeros = 0, nb_nonzeros = 0;
    for (int i = 0; i < Nx*Ny*Nz; i++) {
      if (abs(gammaE[i]) < 0.01) {
        nb_zeros++;
      } else {
        nb_nonzeros++;
      }
    }
    {
      std::ostringstream oss;
      oss << "nb_zeros = " << nb_zeros << " nb_nonzeros = " << nb_nonzeros;
      TRACE_DEBUG(oss);
    }
  }
  fits_close_file(fptr, &status);
  TRACE_EXIT();
  return "READ_GAMMA_OK";
}

std::string write_image(const std::string &pathname, double *&gamma, const std::string &name, long naxis, long *naxes) {
  // this function writes a double array to a fits file
  TRACE_ENTER();
  // create new file
  fitsfile *fptr;
  int status = 0;
  fits_create_file(&fptr, pathname.c_str(), &status);
  if (status != 0) {
    if (status == FILE_NOT_CREATED) {
      status = 0;
      fits_delete_file(fptr, &status);
      if (status != 0) {
        TRACE_EXIT();
        return TRACE_STATUS(status);
      } else {
        fits_create_file(&fptr, pathname.c_str(), &status);
        if (status != 0) {
          TRACE_EXIT();
          return TRACE_STATUS(status);
        }
      }
    } else {
      TRACE_EXIT();
      return TRACE_STATUS(status);
    }
  }
  // create the primary array image
  fits_create_img(fptr, FLOAT_IMG, naxis, naxes, &status);
  if (status != 0) {
    TRACE_EXIT();
    return TRACE_STATUS(status);
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, name.c_str(), gamma, name.c_str(), &status);
  if (status != 0) {
    TRACE_EXIT();
    return TRACE_STATUS(status);
  }
  // write the array of floats to the image
  long fpixel = 1;
  long nelements = 1;
  for (int naxe = 0; naxe < naxis; naxe++) {
    nelements = nelements * naxes[naxe];
  }
  fits_write_img(fptr, TFLOAT, fpixel, nelements, (void*)gamma, &status);
  if (status != 0) {
    TRACE_EXIT();
    return TRACE_STATUS(status);
  }
  // close the file
  fits_close_file(fptr, &status);
  if (status != 0) {
    TRACE_EXIT();
    return TRACE_STATUS(status);
  }
  TRACE_EXIT();
  return "WRITE_OK";
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (ShearInversions_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( gamma2kappa_test ) {
  // this test only calls gamma2kappa, does not check anything.
  TRACE_ENTER();
  std::string pathname ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gammaE = nullptr;
  int Nx = 0, Ny = 0, Nz = 0;
  std::string res = read_gamma(pathname, gammaE, Nx, Ny, Nz);
  if (res != "READ_GAMMA_OK") {
    if (gammaE != nullptr) {
      delete [] gammaE;
    }
    BOOST_FAIL(res);
  }
  {
    std::ostringstream oss;
    oss << "gammaE = " << gammaE;
    TRACE_DEBUG(oss);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  std::ostringstream oss;
  oss << "Nx = " << Nx << " Ny = " << Ny << " Nz = " << Nz;
  TRACE_DEBUG(oss);
  double *kappaE = new double[Nx*Ny*Nz];
  oss.flush();
  oss << "kappaE = " << kappaE;
  TRACE_DEBUG(oss);
  si.gamma2kappa(&gammaE[0], &gammaE[Nx*Ny], kappaE, Nx, Ny, 1);
  // write kappa
  std::string name = "kappa";
  long naxis = 2;
  long naxes[2];
  naxes[0] = 1024;
  naxes[1] = 1024;
  std::string res_write_kappa = write_image("../Tools/tests/src/kappa_B.1_new.fits", kappaE, name, naxis, naxes);
  TRACE_DEBUG(res_write_kappa);
  // free arrays
  delete [] kappaE;
  delete [] gammaE;
  TRACE_EXIT();
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input

  std::string log_header = " ";
  std::string enter_exit_log_header = "";
  TRACE_ENTER();
  std::string pathname ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gammaE = nullptr;
  int Nx = 0, Ny = 0, Nz = 0;
  std::string res = read_gamma(pathname, gammaE, Nx, Ny, Nz);
  if (res != "READ_GAMMA_OK") {
    if (gammaE != nullptr) {
      delete [] gammaE;
    }
    TRACE_EXIT();
    BOOST_FAIL(res);
  }
  std::cout << log_header << "gammaE = " << gammaE << std::endl;
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  double *kappaE = new double[Nx*Ny*Nz];
  si.gamma2kappa(&gammaE[0], &gammaE[Nx*Ny], kappaE, Nx, Ny, 1);
  // kappa2gamma
  double *gammaE_output = new double [Nx*Ny*Nz];
  si.kappa2gamma(kappaE, &gammaE_output[0], &gammaE_output[Nx*Ny], Nx, Ny, 1);
  // output vs input
  int nb_same = 0;
  int nb_diff = 0;
  for (int i = 0; i < Nx*Ny*Nz; i++) {
    if (abs(gammaE_output[i] - gammaE[i]) < abs(gammaE[i]) * 0.01) {
      nb_same++;
    } else {
      nb_diff++;
    }
  }
  {
    std::ostringstream oss;
    oss << "nb_same = " << nb_same << " nb_diff = " << nb_diff;
    TRACE_DEBUG(oss);
  }
  // write gammaE_output
  std::string name = "gamma_output";
  long naxis = 2;
  long naxes[2];
  naxes[0] = 1024;
  naxes[1] = 1024;
  std::string res_write_kappa = write_image("../Tools/tests/src/gamma_B.1_output.fits", gammaE_output, name, naxis, naxes);
  TRACE_DEBUG(res_write_kappa);
  // free arrays
  delete [] gammaE_output;
  delete [] kappaE;
  delete [] gammaE;
  TRACE_EXIT();
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
