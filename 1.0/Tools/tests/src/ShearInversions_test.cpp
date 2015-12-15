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
  std::string pathname_gamma ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma = nullptr;
  int naxis_gamma = 0;
  long *naxes_gamma = nullptr;
  std::string read_gamma = io::read_image(pathname_gamma, gamma, naxis_gamma, naxes_gamma);
  if (read_gamma != "READ_OK") {
    if (gamma != nullptr) {
      delete [] gamma;
    }
    if (naxes_gamma != nullptr) {
      delete [] naxes_gamma;
    }
    BOOST_FAIL(read_gamma);
  }
  // nelements
  long nelements_gamma = 1;
  for (int num_axis = 0; num_axis < naxis_gamma; num_axis++) {
    nelements_gamma = nelements_gamma * naxes_gamma[num_axis];
  }
  {
    std::ostringstream oss;
    oss << "nelements = " << nelements_gamma;
    TRACE_DEBUG(oss.str());
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si (NZeroPadded);
  // gamma2kappa
  double *kappa = new double[nelements_gamma/2];
  si.gamma2kappa(&gamma[0], &gamma[nelements_gamma/2], kappa, naxes_gamma[0], naxes_gamma[1], naxes_gamma[2]/2);
  // write kappa
  std::string name_kappa("kappa");
  std::string write_kappa = io::write_image("../Tools/tests/src/kappa_B.1_new.fits", kappa, name_kappa, naxis_gamma-1, naxes_gamma);
  if (write_kappa != "WRITE_OK") {
    delete [] kappa;
    delete [] gamma;
    delete [] naxes_gamma;
    BOOST_FAIL(write_kappa);
  }
  // free arrays
  delete [] kappa;
  delete [] gamma;
  delete [] naxes_gamma;
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input
  TRACE_ENTER();
  std::string pathname_gamma ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma = nullptr;
  int naxis_gamma = 0;
  long *naxes_gamma = nullptr;
  std::string read_gamma = io::read_image(pathname_gamma, gamma, naxis_gamma, naxes_gamma);
  if (read_gamma != "READ_OK") {
    if (gamma != nullptr) {
      delete [] gamma;
    }
    if (naxes_gamma != nullptr) {
      delete [] naxes_gamma;
    }
    BOOST_FAIL(read_gamma);
  }
  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  long nelements_gamma = 1;
  for (int num_axis = 0; num_axis < naxis_gamma; num_axis++) {
    {
      std::ostringstream oss;
      oss << "naxes_gamma[" << num_axis << "] = " << naxes_gamma[num_axis];
      TRACE_DEBUG(oss.str());
    }
    nelements_gamma = nelements_gamma*naxes_gamma[num_axis];
  }
  {
    std::ostringstream oss;
    oss << "nelements_gamma = " << nelements_gamma;
    TRACE_DEBUG(oss.str());
  }
  double *kappa = new double [nelements_gamma/2];
  si.gamma2kappa(&gamma[0], &gamma[nelements_gamma/2], kappa, naxes_gamma[0], naxes_gamma[1], naxes_gamma[2]/2);
  // kappa2gamma
  double *gamma_g2k2g = new double [nelements_gamma];
  si.kappa2gamma(kappa, &gamma_g2k2g[0], &gamma_g2k2g[nelements_gamma/2], naxes_gamma[0], naxes_gamma[1], naxes_gamma[2]/2);
  // write gamma_g2k2g
  std::string name_output = "gamma_g2k2g";
  std::string write_output = io::write_image("../Tools/tests/src/gamma_B.1_new.g2k2g.fits", gamma_g2k2g, name_output, naxis_gamma, naxes_gamma);
  if (write_output != "WRITE_OK") {
    delete [] gamma_g2k2g;
    delete [] kappa;
    delete [] gamma;
    delete [] naxes_gamma;
    BOOST_FAIL(write_output);
  }
  // compare input vs output
  for (int i = 0; i < nelements_gamma; i++) {
    BOOST_CHECK(fabs(gamma_g2k2g[i]-gamma[i]) < fabs(gamma[i])*0.01);
  }
  // free arrays
  delete [] gamma_g2k2g;
  delete [] kappa;
  delete [] gamma;
  delete [] naxes_gamma;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
