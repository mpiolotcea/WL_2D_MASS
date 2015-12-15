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
  // read gamma_r from pathname_gamma
  std::string pathname_gamma("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_r = nullptr;
  int naxis_gamma_r = 0;
  long *naxes_gamma_r = nullptr;
  std::string read_gamma = io::read_image(pathname_gamma, gamma_r, naxis_gamma_r, naxes_gamma_r);
  if (read_gamma != "READ_OK") {
    if (gamma_r != nullptr) {
      delete [] gamma_r;
    }
    if (naxes_gamma_r != nullptr) {
      delete [] naxes_gamma_r;
    }
    BOOST_FAIL(read_gamma);
  }
  // write gamma_r into pathname_gamma_rw
  std::string pathname_gamma_rw("../Tools/tests/src/gamma_B.1_new.rw.fits");
  std::string name_gamma_rw("gamma_rw");
  std::string write_output = io::write_image(pathname_gamma_rw, gamma_r, name_gamma_rw, naxis_gamma_r, naxes_gamma_r);
  if (write_output != "WRITE_OK") {
    delete [] gamma_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(write_output);
  }
  // read gamma_rwr from pathname_gamma_rw
  double *gamma_rwr = nullptr;
  int naxis_gamma_rwr = 0;
  long *naxes_gamma_rwr = nullptr;
  std::string read_gamma_rwr = io::read_image(pathname_gamma_rw, gamma_rwr, naxis_gamma_rwr, naxes_gamma_rwr);
  if (read_gamma_rwr != "READ_OK") {
    if (gamma_rwr != nullptr) {
      delete [] gamma_rwr;
    }
    delete [] gamma_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(read_gamma_rwr);
  }
  // compare output vs input
  BOOST_CHECK(naxis_gamma_rwr == naxis_gamma_r);
  for (int num_axis = 0; num_axis < naxis_gamma_r; num_axis++) {
    BOOST_CHECK(naxes_gamma_rwr[num_axis] == naxes_gamma_r[num_axis]);
  }
  for (int x = 0; x < naxes_gamma_r[0]; x++) {
    for (int y = 0; y < naxes_gamma_r[1]; y++) {
      for (int z = 0; z < naxes_gamma_r[2]; z++) {
        BOOST_CHECK (fabs(gamma_rwr[z*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]-gamma_r[z*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]) <= fabs(gamma_r[z*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]*0.01));
      }
    }
  }
  // free arrays
  delete [] gamma_rwr;
  delete [] naxes_gamma_rwr;
  delete [] gamma_r;
  delete [] naxes_gamma_r;
}

BOOST_AUTO_TEST_CASE( read3Dwriteread_test ) {
  TRACE_ENTER();

  // read gamma_1_r and gamma_2_r from pathname_gamma
  std::string pathname_gamma("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_1_r = nullptr, *gamma_2_r = nullptr;
  int naxis_gamma_r = 0;
  long *naxes_gamma_r = nullptr;
  std::string read_gamma_3D = io::read_image_3D(pathname_gamma, gamma_1_r, gamma_2_r, naxis_gamma_r, naxes_gamma_r);
  if (read_gamma_3D != "READ_OK") {
    if (gamma_2_r != nullptr) {
      delete [] gamma_2_r;
    }
    if (gamma_1_r != nullptr) {
      delete [] gamma_1_r;
    }
    if (naxes_gamma_r != nullptr) {
      delete [] naxes_gamma_r;
    }
    BOOST_FAIL(read_gamma_3D);
  }

  // write gamma_1_r into pathname_gamma_1
  std::string pathname_gamma_1("../Tools/tests/src/gamma_B.1_new.rw.1.fits");
  std::string name_gamma_1_rw("gamma_1_rw");
  std::string write_gamma_1 = io::write_image(pathname_gamma_1, gamma_1_r, name_gamma_1_rw, naxis_gamma_r-1, naxes_gamma_r);
  if (write_gamma_1 != "WRITE_OK") {
    delete [] gamma_2_r;
    delete [] gamma_1_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(write_gamma_1);
  }
  // write gamma_2_r into pathname_gamma_2
  std::string pathname_gamma_2("../Tools/tests/src/gamma_B.1_new.rw.2.fits");
  std::string name_gamma_2_rw("gamma_2_rw");
  std::string write_gamma_2 = io::write_image(pathname_gamma_2, gamma_2_r, name_gamma_2_rw, naxis_gamma_r-1, naxes_gamma_r);
  if (write_gamma_2 != "WRITE_OK") {
    delete [] gamma_2_r;
    delete [] gamma_1_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(write_gamma_2);
  }

  // read gamma_1_rwr from pathname_gamma_1
  double *gamma_1_rwr = nullptr;
  int naxis_gamma_1_rwr = 0;
  long *naxes_gamma_1_rwr = nullptr;
  std::string read_gamma_1 = io::read_image(pathname_gamma_1, gamma_1_rwr, naxis_gamma_1_rwr, naxes_gamma_1_rwr);
  if (read_gamma_1 != "READ_OK") {
    if (gamma_1_rwr != nullptr) {
      delete [] gamma_1_rwr;
    }
    if (naxes_gamma_1_rwr != nullptr) {
      delete [] naxes_gamma_1_rwr;
    }
    delete [] gamma_2_r;
    delete [] gamma_1_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(read_gamma_1);
  }
  // read gamma_2_rwr from pathname_gamma_2
  double *gamma_2_rwr = nullptr;
  int naxis_gamma_2_rwr = 0;
  long *naxes_gamma_2_rwr = nullptr;
  std::string read_gamma_2 = io::read_image(pathname_gamma_2, gamma_2_rwr, naxis_gamma_2_rwr, naxes_gamma_2_rwr);
  if (read_gamma_2 != "READ_OK") {
    if (gamma_2_rwr != nullptr) {
      delete [] gamma_2_rwr;
    }
    if (naxes_gamma_2_rwr != nullptr) {
      delete [] naxes_gamma_2_rwr;
    }
    delete [] gamma_1_rwr;
    delete [] naxes_gamma_1_rwr;
    delete [] gamma_2_r;
    delete [] gamma_1_r;
    delete [] naxes_gamma_r;
    BOOST_FAIL(read_gamma_2);
  }

  // compare output vs input
  // array_1
  BOOST_CHECK(naxis_gamma_r == naxis_gamma_1_rwr+1);
  for (int num_axis = 0; num_axis < naxis_gamma_r-1; num_axis++) {
    BOOST_CHECK(naxes_gamma_r[num_axis] == naxes_gamma_1_rwr[num_axis]);
  }
  // array_2
  BOOST_CHECK(naxis_gamma_r == naxis_gamma_2_rwr+1);
  for (int num_axis = 0; num_axis < naxis_gamma_r-1; num_axis++) {
    BOOST_CHECK(naxes_gamma_r[num_axis] == naxes_gamma_2_rwr[num_axis]);
  }
  for (int x = 0; x < naxes_gamma_r[0]; x++) {
    for (int y = 0; y < naxes_gamma_r[1]; y++) {
      BOOST_CHECK (fabs(gamma_1_rwr[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]-gamma_1_r[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]) <= fabs(gamma_1_r[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]*0.01));
    }
  }
  for (int x = 0; x < naxes_gamma_r[0]; x++) {
    for (int y = 0; y < naxes_gamma_r[1]; y++) {
      BOOST_CHECK (fabs(gamma_2_rwr[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]-gamma_2_r[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]) <= fabs(gamma_2_r[0*naxes_gamma_r[1]*naxes_gamma_r[0]+x*naxes_gamma_r[1]+y]*0.01));
    }
  }

  // free arrays
  delete [] gamma_2_rwr;
  delete [] naxes_gamma_2_rwr;
  delete [] gamma_1_rwr;
  delete [] naxes_gamma_1_rwr;
  delete [] gamma_2_r;
  delete [] gamma_1_r;
  delete [] naxes_gamma_r;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
