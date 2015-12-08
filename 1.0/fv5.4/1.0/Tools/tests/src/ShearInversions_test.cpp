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

#include "Tools/ShearInversions.h"

using namespace Tools;

std::string status_is_not_zero(int status, std::string log_header = "   ", std::string enter_exit_log_header = "  ") {
  std::cout << enter_exit_log_header << "ENTER status_is_not_zero" << std::endl;
  char errstatus[30];
  fits_get_errstatus(status, errstatus);
  char errmsg[80];
  fits_read_errmsg(errmsg);
  std::ostringstream oss;
  oss << status << " " << errstatus << " " << errmsg;
  std::cout << log_header << oss.str() << std::endl;
  std::cout << enter_exit_log_header << "EXIT status_is_not_zero" << std::endl;
  return oss.str();
}

std::string read_gamma(const std::string &pathname, double *&gammaE, int &Nx, int &Ny, int &Nz, std::string log_header = "  ", std::string enter_exit_log_header = " ") {
  std::cout << enter_exit_log_header << "ENTER read_gamma" << std::endl;
  // open FITS file in READONLY mode
  fitsfile *fptr;
  int status = 0;
  fits_open_image(&fptr, pathname.c_str(), READONLY, &status);
  std::cout << log_header << "fptr = " << fptr << std::endl;
  // error case
  if (status != 0) {
    std::string exit_string = status_is_not_zero(status);
    std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
    return exit_string;
  }
  // read number of HDUs in the file
  int nhdus = 0;
  fits_get_num_hdus(fptr, &nhdus, &status);
  std::cout << log_header << "nhdus = " << nhdus << std::endl;
  // we expect only one HDU in the file
  if (nhdus != 1) {
    std::ostringstream oss;
    oss << "nhdus is " << nhdus << ", not 1";
    std::cout << log_header << oss << std::endl;
    std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
    return oss.str();
  }
  // read the HDUs of the file
  for (int hdunum = 1; hdunum < nhdus+1; hdunum++) {
    std::cout << log_header << "hdunum = " << hdunum << std::endl;
    // read the type of the HDU
    int hdutype = 0;
    fits_movabs_hdu(fptr, hdunum, &hdutype, &status);
    if (status == END_OF_FILE) {
      status = 0;
      break;
    }
    std::cout << log_header << "hdutype = " << hdutype << std::endl;
    if (hdutype != IMAGE_HDU) {
      std::ostringstream oss;
      oss << "hdutype is " << hdutype << ", not IMAGE_HDU";
      std::cout << log_header << oss << std::endl;
      std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
      return oss.str();
    }
    // read the type of data in the HDU
    int bitpix = 0;
    fits_get_img_type (fptr, &bitpix, &status);
    std::cout << log_header << "bitpix = " << bitpix << std::endl;
    if (bitpix != FLOAT_IMG) {
      std::ostringstream oss;
      oss << "bitpix is " << bitpix << ", not FLOAT_IMG";
      std::cout << log_header << oss << std::endl;
      std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
      return oss.str();
    }
    // get the number of dimensions in the image
    int naxis = 0;
    fits_get_img_dim (fptr, &naxis, &status);
    std::cout << log_header << "naxis = " << naxis << std::endl;
    if (naxis != 3) {
      std::ostringstream oss;
      oss << "naxis is " << naxis << ", not 3";
      std::cout << log_header << oss << std::endl;
      std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
      return oss.str();
    }
    // get the size of each dimension in the image
    long *naxes = new long[naxis];
    int maxdim = naxis;
    fits_get_img_size(fptr, maxdim, naxes, &status);
    Nx = naxes[0];
    Ny = naxes[1];
    Nz = naxes[2];
    delete [] naxes;
    std::cout << log_header << "Nx = " << Nx << " Ny = " << Ny << " Nz = " << Nz << std::endl;
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
    std::cout << log_header << "sizeof(gammaE) = " << sizeof(gammaE) << std::endl;
    int anynul = 0;
    std::cout << log_header << "fptr = " << fptr << " TFLOAT = " << TFLOAT << " fpixel = " << fpixel << " lpixel = " << lpixel
        << " inc = " << inc << " nulval = " << nulval << " gammaE = " << gammaE << " anynul = " << anynul
        << " status = " << status << std::endl;
    fits_read_subset(fptr, TFLOAT, fpixel, lpixel, inc, &nulval, gammaE, &anynul, &status);
    if (status != 0) {
      std::string exit_string = status_is_not_zero(status);
      std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
      return exit_string;
    }
    int nb_zeros = 0, nb_nonzeros = 0;
    for (int i = 0; i < Nx*Ny*Nz; i++) {
      if (abs(gammaE[i]) < 0.01) {
        nb_zeros++;
      } else {
        nb_nonzeros++;
      }
    }
    std::cout << log_header << "nb_zeros = " << nb_zeros << " nb_nonzeros = " << nb_nonzeros << std::endl;
  }
  fits_close_file(fptr, &status);
  std::cout << enter_exit_log_header << "EXIT read_gamma" << std::endl;
  return "READ_GAMMA_OK";
}

std::string write_kappa(const std::string &pathname, double *kappa, std::string log_header = "  ", std::string enter_exit_log_header = " ") {
  std::cout << enter_exit_log_header << "ENTER write_kappa" << std::endl;
  // create new file
  fitsfile *fptr;
  int status = 0;
  fits_create_file(&fptr, pathname.c_str(), &status);
  if (status != 0) {
    if (status == FILE_NOT_CREATED) {
      status = 0;
      fits_delete_file(fptr, &status);
      if (status != 0) {
        std::string exit_string = status_is_not_zero(status);
        std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
        return exit_string;
      } else {
        fits_create_file(&fptr, pathname.c_str(), &status);
        if (status != 0) {
          std::string exit_string = status_is_not_zero(status);
          std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
          return exit_string;
        }
      }
    } else {
      std::string exit_string = status_is_not_zero(status);
      std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
      return exit_string;
    }
  }
  // create the primary array image
  int naxis = 3;
  long naxes[3];
  naxes[0] = 1024;
  naxes[1] = 1024;
  naxes[2] = 2;
  fits_create_img(fptr, FLOAT_IMG, naxis, naxes, &status);
  if (status != 0) {
    std::string exit_string = status_is_not_zero(status);
    std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
    return exit_string;
  }
  // write a keyword
  fits_update_key(fptr, TFLOAT, "kappa", kappa, "kappa", &status);
  if (status != 0) {
    std::string exit_string = status_is_not_zero(status);
    std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
    return exit_string;
  }
  // write the array of floats to the image
  long fpixel = 1;
  long nelements = 1024*1024*2;
  fits_write_img(fptr, TFLOAT, fpixel, nelements, (void*)kappa, &status);
  if (status != 0) {
    std::string exit_string = status_is_not_zero(status);
    std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
    return exit_string;
  }
  // close the file
  fits_close_file(fptr, &status);
  if (status != 0) {
    std::string exit_string = status_is_not_zero(status);
    std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
    return exit_string;
  }
  std::cout << enter_exit_log_header << "EXIT write_kappa" << std::endl;
  return "WRITE_KAPPA_OK";
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (ShearInversions_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( gamma2kappa_test ) {
  // this test only calls gamma2kappa, does not check anything.

  std::string log_header = " ";
  std::string enter_exit_log_header = "";
  std::cout << enter_exit_log_header << "ENTER gamma2kappa_test" << std::endl;
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
  std::cout << log_header << "gammaE = " << gammaE << std::endl;
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  std::cout << log_header << "Nx = " << Nx << " Ny = " << Ny << " Nz = " << Nz << std::endl;
  double *kappaE = new double[Nx*Ny*Nz];
  std::cout << log_header << "kappaE = " << kappaE << std::endl;
  si.gamma2kappa(&gammaE[0], &gammaE[Nx*Ny], kappaE, Nx, Ny, 1);
  // free arrays
  delete [] kappaE;
  delete [] gammaE;
  std::cout << enter_exit_log_header << "EXIT gamma2kappa_test" << std::endl;
}

BOOST_AUTO_TEST_CASE( gamma2kappaandwritekappa_test ) {
  // this test calls gamma2kappa then writes the result kappa to a fits file

  std::string log_header = " ";
  std::string enter_exit_log_header = "";
  std::cout << enter_exit_log_header << "ENTER gamma2kappaandwritekappa_test" << std::endl;
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
  std::cout << log_header << "gammaE = " << gammaE << std::endl;
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  std::cout << log_header << "Nx = " << Nx << " Ny = " << Ny << " Nz = " << Nz << std::endl;
  double *kappaE = new double[Nx*Ny*Nz];
  std::cout << log_header << "kappaE = " << kappaE << std::endl;
  si.gamma2kappa(&gammaE[0], &gammaE[Nx*Ny], kappaE, Nx, Ny, 1);
  // write kappa
  std::string res_write_kappa = write_kappa("../Tools/tests/src/kappa_B.1_new.fits", kappaE);
  std::cout << log_header << res_write_kappa << std::endl;
  // free arrays
  delete [] kappaE;
  delete [] gammaE;
  std::cout << enter_exit_log_header << "EXIT gamma2kappaandwritekappa_test" << std::endl;
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input

  std::string log_header = " ";
  std::string enter_exit_log_header = "";
  std::cout << enter_exit_log_header << "ENTER gamma2kappa2gamma_test" << std::endl;
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
  std::cout << log_header << "gammaE = " << gammaE << std::endl;
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  double *kappaE = new double[Nx*Ny*Nz];
  si.gamma2kappa((double*)&gammaE[0], (double*)&gammaE[Nx*Ny], kappaE, Nx, Ny, 1);
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
  std::cout << log_header << "nb_same = " << nb_same << " nb_diff = " << nb_diff << std::endl;
  // free arrays
  delete [] gammaE_output;
  delete [] kappaE;
  delete [] gammaE;
  std::cout << enter_exit_log_header << "EXIT gamma2kappa2gamma_test" << std::endl;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
