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
#include <io/read_fits.h>
#include <io/write_fits.h>

#include "Tools/ShearInversions.h"


//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (ShearInversions_test)

//-----------------------------------------------------------------------------


BOOST_AUTO_TEST_CASE( gamma2kappa_test ) {
  // this test only calls gamma2kappa, does not check anything.
  TRACE_ENTER();
  std::string pathname_input ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = io::read_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input;
    }
    if (naxes_input != nullptr) {
      delete [] naxes_input;
    }
    BOOST_FAIL(read_input);
  }
  // nelements
  long nelements_input = 1;
  for (int naxe_input = 0; naxe_input < naxis_input; naxe_input++) {
    nelements_input = nelements_input * naxes_input[naxe_input];
  }
  {
    std::ostringstream oss;
    oss << "nelements = " << nelements_input;
    TRACE_DEBUG(oss.str());
  }
  // write gamma_input
  std::string name_gamma_input("gamma_input");
  std::string write_gamma_input = io::write_image("../Tools/tests/src/gamma_B.1_input.fits", &gamma_input[0], name_gamma_input, naxis_input, naxes_input);
  if (write_gamma_input != "WRITE_OK") {
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_gamma_input);
  }  
  // write gamma_input_1
  std::string name_gamma_input_1("gamma_input_1");
  std::string write_gamma_input_1 = io::write_image("../Tools/tests/src/gamma_B.1_input.1.fits", &gamma_input[0], name_gamma_input_1, naxis_input-1, naxes_input);
  if (write_gamma_input_1 != "WRITE_OK") {
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_gamma_input_1);
  }
  // write gamma_input_2
  std::string name_gamma_input_2("gamma_input_2");
  std::string write_gamma_input_2 = io::write_image("../Tools/tests/src/gamma_B.1_input.2.fits", &gamma_input[nelements_input/2], name_gamma_input_2, naxis_input-1, naxes_input);
  if (write_gamma_input_2 != "WRITE_OK") {
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_gamma_input_2);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  double *kappa_input = new double[nelements_input/2];
  si.gamma2kappa(&gamma_input[0], &gamma_input[nelements_input/2], kappa_input, naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // write kappa_input
  std::string name_input("kappa_input");
  std::string write_input = io::write_image("../Tools/tests/src/kappa_B.1_new.fits", kappa_input, name_input, naxis_input-1, naxes_input);
  if (write_input != "WRITE_OK") {
    delete [] kappa_input;
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_input);
  }
  // free arrays
  delete [] kappa_input;
  delete [] gamma_input;
  delete [] naxes_input;
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input
  TRACE_ENTER();
  std::string pathname_input ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = io::read_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input;
    }
    if (naxes_input != nullptr) {
      delete [] naxes_input;
    }
    BOOST_FAIL(read_input);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  long nelements_input = 1;
  for (int naxe_input = 0; naxe_input < naxis_input; naxe_input++) {
    {
      std::ostringstream oss;
      oss << "naxes_input[" << naxe_input << "] = " << naxes_input[naxe_input];
      TRACE_DEBUG(oss.str());
    }
    nelements_input = nelements_input * naxes_input[naxe_input];
  }
  {
    std::ostringstream oss;
    oss << "nelements_input = " << nelements_input;
    TRACE_DEBUG(oss.str());
  }
  double *kappa_input = new double [nelements_input/2];
  si.gamma2kappa(&gamma_input[0], &gamma_input[nelements_input/2], kappa_input, naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // kappa2gamma
  double *gamma_output = new double [nelements_input];
  si.kappa2gamma(kappa_input, &gamma_output[0], &gamma_output[nelements_input/2], naxes_input[0], naxes_input[1], naxes_input[2]/2);
  // write gamma_output
  std::string name_output = "gamma_output";
  std::string write_output = io::write_image("../Tools/tests/src/gamma_B.1_output.fits", gamma_output, name_output, naxis_input, naxes_input);
  if (write_output != "WRITE_OK") {
    delete [] gamma_output;
    delete [] kappa_input;
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_output);
  }
  // compare input vs output
  for (int i = 0; i < nelements_input; i++) {
    BOOST_CHECK(fabs(gamma_output[i]-gamma_input[i]) < fabs(gamma_input[i])*0.01);
  }
  // free arrays
  delete [] gamma_output;
  delete [] kappa_input;
  delete [] gamma_input;
  delete [] naxes_input;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
