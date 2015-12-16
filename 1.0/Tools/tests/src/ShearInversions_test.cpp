/**
 * @file tests/src/ShearInversions_gamma_g2k2g.cpp
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

  // read gamma and stores it into two arrays
  std::string pathname_gamma_3D ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_2D_1 = nullptr, *gamma_2D_2 = nullptr;
  int naxis_gamma_2D = 0;
  long *naxes_gamma_2D = nullptr;
  std::string read_gamma_3D = io::read_image_3D(pathname_gamma_3D, gamma_2D_1, gamma_2D_2, naxis_gamma_2D, naxes_gamma_2D);
  if (read_gamma_3D != "READ_OK") {
    if (gamma_2D_2 != nullptr) {
      delete [] gamma_2D_2;
    }
    if (gamma_2D_1 != nullptr) {
      delete [] gamma_2D_1;
    }
    if (naxes_gamma_2D != nullptr) {
      delete [] naxes_gamma_2D;
    }
    BOOST_FAIL(read_gamma_3D);
  }

  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  long nelements_gamma_2D = 1;
  for (int i = 0; i < naxis_gamma_2D; i++) {
    nelements_gamma_2D = nelements_gamma_2D*naxes_gamma_2D[i];
  }
  double *kappa = new double [nelements_gamma_2D];
  si.gamma2kappa(gamma_2D_1, gamma_2D_2, kappa, naxes_gamma_2D[0], naxes_gamma_2D[1], 1);

  // write kappa
  std::string name_kappa("kappa");
  std::string write_kappa = io::write_image("../Tools/tests/src/kappa_B.fits", kappa, name_kappa, naxis_gamma_2D, naxes_gamma_2D);
  if (write_kappa != "WRITE_OK") {
    delete [] kappa;
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(write_kappa);
  }

  // free arrays
  delete [] kappa;
  delete [] gamma_2D_2;
  delete [] gamma_2D_1;
  delete [] naxes_gamma_2D;
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input
  TRACE_ENTER();

  std::string pathname_gamma_3D ("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_2D_1 = nullptr, *gamma_2D_2 = nullptr;
  int naxis_gamma_2D = 0;
  long *naxes_gamma_2D = nullptr;
  std::string read_gamma_3D = io::read_image_3D(pathname_gamma_3D, gamma_2D_1, gamma_2D_2, naxis_gamma_2D, naxes_gamma_2D);
  if (read_gamma_3D != "READ_OK") {
    if (gamma_2D_2 != nullptr) {
      delete [] gamma_2D_2;
    }
    if (gamma_2D_1 != nullptr) {
      delete [] gamma_2D_1;
    }
    if (naxes_gamma_2D != nullptr) {
      delete [] naxes_gamma_2D;
    }
    BOOST_FAIL(read_gamma_3D);
  }

  // ShearInversions
  int NZeroPadded = 1024;
  Tools::ShearInversions si(NZeroPadded);
  // gamma2kappa
  long nelements_gamma_2D = 1;
  for (int i = 0; i < naxis_gamma_2D; i++) {
    nelements_gamma_2D = nelements_gamma_2D*naxes_gamma_2D[i];
  }
  double *kappa = new double [nelements_gamma_2D];
  si.gamma2kappa(gamma_2D_1, gamma_2D_2, kappa, naxes_gamma_2D[0], naxes_gamma_2D[1], 1);
  // kappa2gamma
  double *gamma_g2k2g_1 = new double [nelements_gamma_2D];
  double *gamma_g2k2g_2 = new double [nelements_gamma_2D];
  si.kappa2gamma(kappa, gamma_g2k2g_1, gamma_g2k2g_2, naxes_gamma_2D[0], naxes_gamma_2D[1], 1);

  // write gamma_g2k2g
  std::string name_gamma_g2k2g_1 = "gamma_g2k2g_1";
  std::string write_gamma_g2k2g_1 = io::write_image("../Tools/tests/src/gamma_B.g2k2g.1.fits", gamma_g2k2g_1, name_gamma_g2k2g_1, naxis_gamma_2D, naxes_gamma_2D);
  if (write_gamma_g2k2g_1 != "WRITE_OK") {
    delete [] gamma_g2k2g_2;
    delete [] gamma_g2k2g_1;
    delete [] kappa;
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(write_gamma_g2k2g_1);
  }
  // write gamma_g2k2g
  std::string name_gamma_g2k2g_2 = "gamma_g2k2g_2";
  std::string write_gamma_g2k2g_2 = io::write_image("../Tools/tests/src/gamma_B.g2k2g.2.fits", gamma_g2k2g_2, name_gamma_g2k2g_2, naxis_gamma_2D, naxes_gamma_2D);
  if (write_gamma_g2k2g_2 != "WRITE_OK") {
    delete [] gamma_g2k2g_2;
    delete [] gamma_g2k2g_1;
    delete [] kappa;
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(write_gamma_g2k2g_2);
  }

  // compare input vs output
  for (int i = 0; i < nelements_gamma_2D; i++) {
    BOOST_CHECK(fabs(gamma_g2k2g_1[i]-gamma_2D_1[i]) < fabs(gamma_2D_1[i])*0.01);
  }
  for (int i = 0; i < nelements_gamma_2D; i++) {
    BOOST_CHECK(fabs(gamma_g2k2g_2[i]-gamma_2D_2[i]) < fabs(gamma_2D_2[i])*0.01);
  }

  // free arrays
  delete [] gamma_g2k2g_2;
  delete [] gamma_g2k2g_1;
  delete [] kappa;
  delete [] gamma_2D_2;
  delete [] gamma_2D_1;
  delete [] naxes_gamma_2D;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
