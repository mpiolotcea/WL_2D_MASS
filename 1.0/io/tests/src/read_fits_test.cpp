/**
 * @file tests/src/read_fits_test.cpp
 * @date 12/14/15
 * @author user
 */

#include <boost/test/unit_test.hpp>

#include <Trace/Trace.h>

#include "io/read_fits.h"
#include "io/write_fits.h"

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (read_fits_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( readwriteread_test ) {
  TRACE_ENTER();

  // read gamma_3D from pathname_gamma_3D
  std::string pathname_gamma_3D("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_3D = nullptr;
  int naxis_gamma_3D = 0;
  long *naxes_gamma_3D = nullptr;
  std::string read_gamma_3D = io::read_image(pathname_gamma_3D, gamma_3D, naxis_gamma_3D, naxes_gamma_3D);
  if (read_gamma_3D != "READ_OK") {
    if (gamma_3D != nullptr) {
      delete [] gamma_3D;
    }
    if (naxes_gamma_3D != nullptr) {
      delete [] naxes_gamma_3D;
    }
    BOOST_FAIL(read_gamma_3D);
  }

  // write gamma_3D into pathname_gamma_3D_rw
  std::string pathname_gamma_3D_rw("../Tools/tests/src/gamma_B.rw.fits");
  std::string name_gamma_3D_rw("gamma_3D_rw");
  std::string write_gamma_3D_rw = io::write_image(pathname_gamma_3D_rw, gamma_3D, name_gamma_3D_rw, naxis_gamma_3D, naxes_gamma_3D);
  if (write_gamma_3D_rw != "WRITE_OK") {
    delete [] gamma_3D;
    delete [] naxes_gamma_3D;
    BOOST_FAIL(write_gamma_3D_rw);
  }

  // read gamma_3D_rwr from pathname_gamma_3D_rw
  double *gamma_3D_rwr = nullptr;
  int naxis_gamma_3D_rwr = 0;
  long *naxes_gamma_3D_rwr = nullptr;
  std::string read_gamma_3D_rwr = io::read_image(pathname_gamma_3D_rw, gamma_3D_rwr, naxis_gamma_3D_rwr, naxes_gamma_3D_rwr);
  if (read_gamma_3D_rwr != "READ_OK") {
    if (gamma_3D_rwr != nullptr) {
      delete [] gamma_3D_rwr;
    }
    if (naxes_gamma_3D_rwr != nullptr) {
      delete [] naxes_gamma_3D_rwr;
    }
    delete [] gamma_3D;
    delete [] naxes_gamma_3D;
    BOOST_FAIL(read_gamma_3D_rwr);
  }

  // compare output vs input
  BOOST_CHECK(naxis_gamma_3D_rwr == naxis_gamma_3D);
  for (int i = 0; i < naxis_gamma_3D; i++) {
    BOOST_CHECK(naxes_gamma_3D_rwr[i] == naxes_gamma_3D[i]);
  }
  for (int x = 0; x < naxes_gamma_3D[0]; x++) {
    for (int y = 0; y < naxes_gamma_3D[1]; y++) {
      for (int z = 0; z < naxes_gamma_3D[2]; z++) {
        BOOST_CHECK (fabs(gamma_3D_rwr[z*naxes_gamma_3D[1]*naxes_gamma_3D[0]+x*naxes_gamma_3D[1]+y]-gamma_3D[z*naxes_gamma_3D[1]*naxes_gamma_3D[0]+x*naxes_gamma_3D[1]+y]) <= fabs(gamma_3D[z*naxes_gamma_3D[1]*naxes_gamma_3D[0]+x*naxes_gamma_3D[1]+y]*0.01));
      }
    }
  }

  // free arrays
  delete [] gamma_3D_rwr;
  delete [] naxes_gamma_3D_rwr;
  delete [] gamma_3D;
  delete [] naxes_gamma_3D;
}

BOOST_AUTO_TEST_CASE( read3Dwriteread_test ) {
  TRACE_ENTER();

  // read gamma_2D_1 and gamma_2D_2 from pathname_gamma_3D
  std::string pathname_gamma_3D("../Tools/tests/src/gamma_B.1_new.fits");
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

  // write gamma_2D_1 into pathname_gamma_2D_1
  std::string pathname_gamma_2D_1_r3Dw("../Tools/tests/src/gamma_B.r3Dw.1.fits");
  std::string name_gamma_2D_1_r3Dw("gamma_2D_1_r3Dw");
  std::string write_gamma_2D_1_r3Dw = io::write_image(pathname_gamma_2D_1_r3Dw, gamma_2D_1, name_gamma_2D_1_r3Dw, naxis_gamma_2D, naxes_gamma_2D);
  if (write_gamma_2D_1_r3Dw != "WRITE_OK") {
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(write_gamma_2D_1_r3Dw);
  }
  // write gamma_2D_2 into pathname_gamma_2D_2
  std::string pathname_gamma_2D_2_r3Dw("../Tools/tests/src/gamma_B.r3Dw.2.fits");
  std::string name_gamma_2D_2_r3Dw("gamma_2D_2");
  std::string write_gamma_2D_2_r3Dw = io::write_image(pathname_gamma_2D_2_r3Dw, gamma_2D_2, name_gamma_2D_2_r3Dw, naxis_gamma_2D, naxes_gamma_2D);
  if (write_gamma_2D_2_r3Dw != "WRITE_OK") {
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(write_gamma_2D_2_r3Dw);
  }

  // read gamma_2D_1_r3Dwr from pathname_gamma_2D_1
  double *gamma_2D_1_r3Dwr = nullptr;
  int naxis_gamma_2D_1_r3Dwr = 0;
  long *naxes_gamma_2D_1_r3Dwr = nullptr;
  std::string read_gamma_2D_1 = io::read_image(pathname_gamma_2D_1_r3Dw, gamma_2D_1_r3Dwr, naxis_gamma_2D_1_r3Dwr, naxes_gamma_2D_1_r3Dwr);
  if (read_gamma_2D_1 != "READ_OK") {
    if (gamma_2D_1_r3Dwr != nullptr) {
      delete [] gamma_2D_1_r3Dwr;
    }
    if (naxes_gamma_2D_1_r3Dwr != nullptr) {
      delete [] naxes_gamma_2D_1_r3Dwr;
    }
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(read_gamma_2D_1);
  }
  // read gamma_2D_2_r3Dwr from pathname_gamma_2D_2
  double *gamma_2D_2_r3Dwr = nullptr;
  int naxis_gamma_2D_2_r3Dwr = 0;
  long *naxes_gamma_2D_2_r3Dwr = nullptr;
  std::string read_gamma_2D_2 = io::read_image(pathname_gamma_2D_2_r3Dw, gamma_2D_2_r3Dwr, naxis_gamma_2D_2_r3Dwr, naxes_gamma_2D_2_r3Dwr);
  if (read_gamma_2D_2 != "READ_OK") {
    if (gamma_2D_2_r3Dwr != nullptr) {
      delete [] gamma_2D_2_r3Dwr;
    }
    if (naxes_gamma_2D_2_r3Dwr != nullptr) {
      delete [] naxes_gamma_2D_2_r3Dwr;
    }
    delete [] gamma_2D_1_r3Dwr;
    delete [] naxes_gamma_2D_1_r3Dwr;
    delete [] gamma_2D_2;
    delete [] gamma_2D_1;
    delete [] naxes_gamma_2D;
    BOOST_FAIL(read_gamma_2D_2);
  }

  // compare output vs input
  // array_1
  BOOST_CHECK(naxis_gamma_2D == naxis_gamma_2D_1_r3Dwr);
  for (int i = 0; i < naxis_gamma_2D; i++) {
    BOOST_CHECK(naxes_gamma_2D[i] == naxes_gamma_2D_1_r3Dwr[i]);
  }
  for (int x = 0; x < naxes_gamma_2D[0]; x++) {
    for (int y = 0; y < naxes_gamma_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_2D_1_r3Dwr[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]-gamma_2D_1[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]) <= fabs(gamma_2D_1[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]*0.01));
    }
  }
  // array_2
  BOOST_CHECK(naxis_gamma_2D == naxis_gamma_2D_2_r3Dwr);
  for (int i = 0; i < naxis_gamma_2D; i++) {
    BOOST_CHECK(naxes_gamma_2D[i] == naxes_gamma_2D_2_r3Dwr[i]);
  }
  for (int x = 0; x < naxes_gamma_2D[0]; x++) {
    for (int y = 0; y < naxes_gamma_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_2D_2_r3Dwr[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]-gamma_2D_2[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]) <= fabs(gamma_2D_2[0*naxes_gamma_2D[1]*naxes_gamma_2D[0]+x*naxes_gamma_2D[1]+y]*0.01));
    }
  }

  // free arrays
  delete [] gamma_2D_2_r3Dwr;
  delete [] naxes_gamma_2D_2_r3Dwr;
  delete [] gamma_2D_1_r3Dwr;
  delete [] naxes_gamma_2D_1_r3Dwr;
  delete [] gamma_2D_2;
  delete [] gamma_2D_1;
  delete [] naxes_gamma_2D;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
