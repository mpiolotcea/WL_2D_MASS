/**
 * @file tests/src/write_fits_test.cpp
 * @date 12/14/15
 * @author user
 */

#include <boost/test/unit_test.hpp>

#include "io/write_fits.h"

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (write_fits_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( cossin_test ) {
  TRACE_ENTER();
  // create cossin image
  float *array_cos = new float [1024*1024];
  float *array_sin = new float [1024*1024];
  for (int x = 0; x < 1024; x++) {
    for (int y = 0; y < 1024; y++) {
      array_cos[x*1024+y] = cos(2*M_PI*(x*1024+y)/(1024*1024));
      array_sin[x*1024+y] = sin(2*M_PI*(x*1024+y)/(1024*1024));
    }
  }
  std::string pathname_array_cossin("../Tools/tests/src/cossin.fits");
  std::string name_array_cossin("cossin(x+y)");
  int naxis_cossin = 2;
  long *naxes_cossin = new long[2];
  naxes_cossin[0] = 1024;
  naxes_cossin[1] = 1024;
  std::string write_array_cossin = io::write_image_3D(pathname_array_cossin, array_cos, array_sin, name_array_cossin, naxis_cossin, naxes_cossin);
  if (write_array_cossin != "WRITE_OK") {
    delete [] naxes_cossin;
    delete [] array_sin;
    delete [] array_cos;
    BOOST_FAIL(write_array_cossin);
  }
  delete [] naxes_cossin;
  delete [] array_sin;
  delete [] array_cos;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()


