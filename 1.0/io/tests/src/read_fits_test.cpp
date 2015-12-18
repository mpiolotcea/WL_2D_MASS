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

  // read gamma_complex from pathname_gamma_complex
  std::string pathname_gamma_complex("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_complex = nullptr;
  int naxis_complex = 0;
  long *naxes_complex = nullptr;
  std::string read_gamma_complex = io::read_image(pathname_gamma_complex, gamma_complex, naxis_complex, naxes_complex);
  if (read_gamma_complex != "READ_OK") {
    if (gamma_complex != nullptr) {
      delete [] gamma_complex;
    }
    if (naxes_complex != nullptr) {
      delete [] naxes_complex;
    }
    BOOST_FAIL(read_gamma_complex);
  }

  // write gamma_complex into pathname_gamma_complex_rw
  std::string pathname_gamma_complex_rw("../Tools/tests/src/gamma_B.rw.fits");
  std::string name_gamma_complex_rw("gamma_complex_rw");
  std::string write_gamma_complex_rw = io::write_image(pathname_gamma_complex_rw, gamma_complex, name_gamma_complex_rw, naxis_complex, naxes_complex);
  if (write_gamma_complex_rw != "WRITE_OK") {
    delete [] gamma_complex;
    delete [] naxes_complex;
    BOOST_FAIL(write_gamma_complex_rw);
  }

  // read gamma_complex_rwr from pathname_gamma_complex_rw
  double *gamma_complex_rwr = nullptr;
  int naxis_complex_rwr = 0;
  long *naxes_complex_rwr = nullptr;
  std::string read_gamma_complex_rwr = io::read_image(pathname_gamma_complex_rw, gamma_complex_rwr, naxis_complex_rwr, naxes_complex_rwr);
  if (read_gamma_complex_rwr != "READ_OK") {
    if (gamma_complex_rwr != nullptr) {
      delete [] gamma_complex_rwr;
    }
    if (naxes_complex_rwr != nullptr) {
      delete [] naxes_complex_rwr;
    }
    delete [] gamma_complex;
    delete [] naxes_complex;
    BOOST_FAIL(read_gamma_complex_rwr);
  }

  // compare output vs input
  BOOST_CHECK(naxis_complex_rwr == naxis_complex);
  for (int i = 0; i < naxis_complex; i++) {
    BOOST_CHECK(naxes_complex_rwr[i] == naxes_complex[i]);
  }
  for (int x = 0; x < naxes_complex[0]; x++) {
    for (int y = 0; y < naxes_complex[1]; y++) {
      for (int z = 0; z < naxes_complex[2]; z++) {
        BOOST_CHECK (fabs(gamma_complex_rwr[z*naxes_complex[1]*naxes_complex[0]+x*naxes_complex[1]+y]-gamma_complex[z*naxes_complex[1]*naxes_complex[0]+x*naxes_complex[1]+y]) <= fabs(gamma_complex[z*naxes_complex[1]*naxes_complex[0]+x*naxes_complex[1]+y]*0.01));
      }
    }
  }

  // free arrays
  delete [] gamma_complex_rwr;
  delete [] naxes_complex_rwr;
  delete [] gamma_complex;
  delete [] naxes_complex;
}

BOOST_AUTO_TEST_CASE( read3Dwriteread_test ) {
  TRACE_ENTER();

  // read gamma_real and gamma_imag from pathname_gamma_complex
  std::string pathname_gamma_complex("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis_2D = 0;
  long *naxes_2D = nullptr;
  std::string read_gamma_complex = io::read_image_3D(pathname_gamma_complex, gamma_real, gamma_imag, naxis_2D, naxes_2D);
  if (read_gamma_complex != "READ_OK") {
    if (gamma_imag != nullptr) {
      delete [] gamma_imag;
    }
    if (gamma_real != nullptr) {
      delete [] gamma_real;
    }
    if (naxes_2D != nullptr) {
      delete [] naxes_2D;
    }
    BOOST_FAIL(read_gamma_complex);
  }

  // write gamma_real into pathname_gamma_real
  std::string pathname_gamma_real_r3Dw("../Tools/tests/src/gamma_B.r3Dw.real.fits");
  std::string name_gamma_real_r3Dw("gamma_real_r3Dw");
  std::string write_gamma_real_r3Dw = io::write_image(pathname_gamma_real_r3Dw, gamma_real, name_gamma_real_r3Dw, naxis_2D, naxes_2D);
  if (write_gamma_real_r3Dw != "WRITE_OK") {
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(write_gamma_real_r3Dw);
  }
  // write gamma_imag into pathname_gamma_imag
  std::string pathname_gamma_imag_r3Dw("../Tools/tests/src/gamma_B.r3Dw.imag.fits");
  std::string name_gamma_imag_r3Dw("gamma_imag");
  std::string write_gamma_imag_r3Dw = io::write_image(pathname_gamma_imag_r3Dw, gamma_imag, name_gamma_imag_r3Dw, naxis_2D, naxes_2D);
  if (write_gamma_imag_r3Dw != "WRITE_OK") {
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(write_gamma_imag_r3Dw);
  }

  // read gamma_real_r3Dwr from pathname_gamma_real
  double *gamma_real_r3Dwr = nullptr;
  int naxis_real_r3Dwr = 0;
  long *naxes_real_r3Dwr = nullptr;
  std::string read_gamma_real_r3Dwr = io::read_image(pathname_gamma_real_r3Dw, gamma_real_r3Dwr, naxis_real_r3Dwr, naxes_real_r3Dwr);
  if (read_gamma_real_r3Dwr != "READ_OK") {
    if (gamma_real_r3Dwr != nullptr) {
      delete [] gamma_real_r3Dwr;
    }
    if (naxes_real_r3Dwr != nullptr) {
      delete [] naxes_real_r3Dwr;
    }
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(read_gamma_real_r3Dwr);
  }
  // read gamma_imag_r3Dwr from pathname_gamma_imag
  double *gamma_imag_r3Dwr = nullptr;
  int naxis_imag_r3Dwr = 0;
  long *naxes_imag_r3Dwr = nullptr;
  std::string read_gamma_imag_r3Dwr = io::read_image(pathname_gamma_imag_r3Dw, gamma_imag_r3Dwr, naxis_imag_r3Dwr, naxes_imag_r3Dwr);
  if (read_gamma_imag_r3Dwr != "READ_OK") {
    if (gamma_imag_r3Dwr != nullptr) {
      delete [] gamma_imag_r3Dwr;
    }
    if (naxes_imag_r3Dwr != nullptr) {
      delete [] naxes_imag_r3Dwr;
    }
    delete [] gamma_real_r3Dwr;
    delete [] naxes_real_r3Dwr;
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(read_gamma_imag_r3Dwr);
  }

  // compare output vs input
  // gamma_real
  BOOST_CHECK(naxis_2D == naxis_real_r3Dwr);
  for (int i = 0; i < naxis_2D; i++) {
    BOOST_CHECK(naxes_2D[i] == naxes_real_r3Dwr[i]);
  }
  for (int x = 0; x < naxes_2D[0]; x++) {
    for (int y = 0; y < naxes_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_real_r3Dwr[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]-gamma_real[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]) <= fabs(gamma_real[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]*0.01));
    }
  }
  // gamma_imag
  BOOST_CHECK(naxis_2D == naxis_imag_r3Dwr);
  for (int i = 0; i < naxis_2D; i++) {
    BOOST_CHECK(naxes_2D[i] == naxes_imag_r3Dwr[i]);
  }
  for (int x = 0; x < naxes_2D[0]; x++) {
    for (int y = 0; y < naxes_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_imag_r3Dwr[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]-gamma_imag[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]) <= fabs(gamma_imag[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]*0.01));
    }
  }

  // free arrays
  delete [] gamma_imag_r3Dwr;
  delete [] naxes_imag_r3Dwr;
  delete [] gamma_real_r3Dwr;
  delete [] naxes_real_r3Dwr;
  delete [] gamma_imag;
  delete [] gamma_real;
  delete [] naxes_2D;
}

BOOST_AUTO_TEST_CASE( read3Dwrite3Dread3D_test ) {
  TRACE_ENTER();

  // read gamma_real and gamma_imag from pathname_gamma_complex
  std::string pathname_gamma_complex("../Tools/tests/src/gamma_B.1_new.fits");
  double *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis_2D = 0;
  long *naxes_2D = nullptr;
  std::string read_gamma_complex = io::read_image_3D(pathname_gamma_complex, gamma_real, gamma_imag, naxis_2D, naxes_2D);
  if (read_gamma_complex != "READ_OK") {
    if (gamma_imag != nullptr) {
      delete [] gamma_imag;
    }
    if (gamma_real != nullptr) {
      delete [] gamma_real;
    }
    if (naxes_2D != nullptr) {
      delete [] naxes_2D;
    }
    BOOST_FAIL(read_gamma_complex);
  }

  // write gamma_real and gamma_imag into pathname_gamma_r3Dw3D
  std::string pathname_gamma_r3Dw3D("../Tools/tests/src/gamma_B.r3Dw3D.fits");
  std::string name_gamma_r3Dw3D("gamma_r3Dw3D");
  std::string write_gamma_r3Dw3D = io::write_image_3D(pathname_gamma_r3Dw3D, gamma_real, gamma_imag, name_gamma_r3Dw3D, naxis_2D, naxes_2D);
  if (write_gamma_r3Dw3D != "WRITE_OK") {
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(write_gamma_r3Dw3D);
  }

  // read gamma_real_r3Dw3Dr3D from pathname_gamma_real
  double *gamma_real_r3Dw3Dr3D = nullptr, *gamma_imag_r3Dw3Dr3D = nullptr;
  int naxis_2D_r3Dw3Dr3D = 0;
  long *naxes_2D_r3Dw3Dr3D = nullptr;
  std::string read_gamma_r3Dw3Dr3D = io::read_image_3D(pathname_gamma_r3Dw3D, gamma_real_r3Dw3Dr3D, gamma_imag_r3Dw3Dr3D, naxis_2D_r3Dw3Dr3D, naxes_2D_r3Dw3Dr3D);
  if (read_gamma_r3Dw3Dr3D != "READ_OK") {
    if (gamma_imag_r3Dw3Dr3D != nullptr) {
      delete [] gamma_imag_r3Dw3Dr3D;
    }
    if (gamma_real_r3Dw3Dr3D != nullptr) {
      delete [] gamma_real_r3Dw3Dr3D;
    }
    if (naxes_2D_r3Dw3Dr3D != nullptr) {
      delete [] naxes_2D_r3Dw3Dr3D;
    }
    delete [] gamma_imag;
    delete [] gamma_real;
    delete [] naxes_2D;
    BOOST_FAIL(read_gamma_r3Dw3Dr3D);
  }

  // compare output vs input
  BOOST_CHECK(naxis_2D == naxis_2D_r3Dw3Dr3D);
  for (int i = 0; i < naxis_2D; i++) {
    BOOST_CHECK(naxes_2D[i] == naxes_2D_r3Dw3Dr3D[i]);
  }
  // gamma_real
  for (int x = 0; x < naxes_2D[0]; x++) {
    for (int y = 0; y < naxes_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_real_r3Dw3Dr3D[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]-gamma_real[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]) <= fabs(gamma_real[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]*0.01));
    }
  }
  // gamma_imag
  for (int x = 0; x < naxes_2D[0]; x++) {
    for (int y = 0; y < naxes_2D[1]; y++) {
      BOOST_CHECK (fabs(gamma_imag_r3Dw3Dr3D[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]-gamma_imag[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]) <= fabs(gamma_imag[0*naxes_2D[1]*naxes_2D[0]+x*naxes_2D[1]+y]*0.01));
    }
  }

  // free arrays
  delete [] gamma_imag_r3Dw3Dr3D;
  delete [] gamma_real_r3Dw3Dr3D;
  delete [] naxes_2D_r3Dw3Dr3D;
  delete [] gamma_imag;
  delete [] gamma_real;
  delete [] naxes_2D;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
