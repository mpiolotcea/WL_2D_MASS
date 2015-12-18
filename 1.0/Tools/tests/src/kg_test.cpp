/**
 * @file tests/src/kg_test.cpp
 * @date 12/18/15
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

#include "Tools/kg.h"

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (kg_test)

//-----------------------------------------------------------------------------

void init_test(std::string pathname_gamma_complex, float *&gamma_real, float *&gamma_imag, int &naxis, long *&naxes)
{
  // read gamma and stores it into two arrays
  std::string read_gamma_complex = io::read_image_3D(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);
  if (read_gamma_complex != "READ_OK") {
    if (gamma_imag != nullptr) {
      delete [] gamma_imag;
    }
    if (gamma_real != nullptr) {
      delete [] gamma_real;
    }
    if (naxes != nullptr) {
      delete [] naxes;
    }
    BOOST_FAIL(read_gamma_complex);
  }
}

void exit_test(float *gamma_real, float *gamma_imag, long *naxes)
{
  delete [] gamma_imag;
  delete [] gamma_real;
  delete [] naxes;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( real2complex2real_test ) {
  TRACE_ENTER();

  // read gamma and stores it into two arrays
  std::string pathname_gamma_complex ("../Tools/tests/src/gamma_B.1_new.fits");
  float *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);

  // real2complex and complex2real
  fftw_complex* gamma_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::real2complex(gamma_real, gamma_complex, naxes[0], naxes[1]);
  float *gamma_real_r2c2r = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2real(gamma_complex, gamma_real_r2c2r, naxes[0], naxes[1]);

  // compare input vs output
  for (int i = 0; i < naxes[0]; i++) {
    BOOST_CHECK(fabs(gamma_real_r2c2r[i]-gamma_real[i]) < fabs(gamma_real[i])*0.01);
  }

  // free arrays
  delete [] gamma_real_r2c2r;
  fftw_free(gamma_complex);
  exit_test(gamma_real, gamma_imag, naxes);
}

BOOST_AUTO_TEST_CASE( realandimag2complex2realandimag_test ) {
  TRACE_ENTER();

  // read gamma and stores it into two arrays
  std::string pathname_gamma_complex ("../Tools/tests/src/gamma_B.1_new.fits");
  float *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);

  // real2complex and complex2real
  fftw_complex* gamma_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::realandimag2complex(gamma_real, gamma_imag, gamma_complex, naxes[0], naxes[1]);
  float *gamma_real_ri2c2ri = new float [naxes[0]*naxes[1]];
  float *gamma_imag_ri2c2ri = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2realandimag(gamma_complex, gamma_real_ri2c2ri, gamma_imag_ri2c2ri, naxes[0], naxes[1]);

  // compare input vs output
  for (int i = 0; i < naxes[0]; i++) {
    BOOST_CHECK(fabs(gamma_real_ri2c2ri[i]-gamma_real[i]) < fabs(gamma_real[i])*0.01);
    BOOST_CHECK(fabs(gamma_imag_ri2c2ri[i]-gamma_imag[i]) < fabs(gamma_imag[i])*0.01);
  }

  // free arrays
  delete [] gamma_imag_ri2c2ri;
  delete [] gamma_real_ri2c2ri;
  fftw_free(gamma_complex);
  exit_test(gamma_real, gamma_imag, naxes);
}

BOOST_AUTO_TEST_CASE( fftw_sin_test ) {
  TRACE_ENTER();

  // create sin image
  float *array_cos = new float [1024*1024];
  float *array_sin = new float [1024*1024];
  for (int x = 0; x < 1024; x++) {
    for (int y = 0; y < 1024; y++) {
      array_cos[x*1024+y] = cos(2*M_PI*(x*1024+y)/(1024*1024));
      array_sin[x*1024+y] = sin(2*M_PI*(x*1024+y)/(1024*1024));
    }
  }
  std::string pathname_array_sin("../Tools/tests/src/sin.fits");
  std::string name_array_sin("sin(x+y)");
  int naxis_sin = 2;
  long *naxes_sin = new long[2];
  naxes_sin[0] = 1024;
  naxes_sin[1] = 1024;
  std::string write_array_sin = io::write_image_3D(pathname_array_sin, array_cos, array_sin, name_array_sin, naxis_sin, naxes_sin);
  if (write_array_sin != "WRITE_OK") {
    delete [] naxes_sin;
    delete [] array_sin;
    delete [] array_cos;
    BOOST_FAIL(write_array_sin);
  }
  delete [] naxes_sin;
  delete [] array_sin;
  delete [] array_cos;

  // read the image and stores it into two arrays
  std::string pathname_sin_complex ("../Tools/tests/src/sin.fits");
  float *sin_real = nullptr, *sin_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_sin_complex, sin_real, sin_imag, naxis, naxes);

  // realandimag2complex
  fftw_complex* sin_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::realandimag2complex(sin_real, sin_imag, sin_complex, naxes[0], naxes[1]);

  // fftw_forward
  fftw_complex* sin_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::fftw_forward(sin_complex, sin_circumflex, naxes[0], naxes[1]);

  // write sin_circumflex
  std::string pathname_sin_circumflex("../Tools/tests/src/sin.circumflex.fits");
  std::string name_sin_circumflex("sin_circumflex");
  float *sin_circumflex_real = new float [naxes[0]*naxes[1]];
  float *sin_circumflex_imag = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2realandimag(sin_circumflex, sin_circumflex_real, sin_circumflex_imag, naxes[0], naxes[1]);
  std::string write_sin_circumflex = io::write_image_3D(pathname_sin_circumflex, sin_circumflex_real, sin_circumflex_imag, name_sin_circumflex, naxis, naxes);
  if (write_sin_circumflex != "WRITE_OK") {
    delete [] sin_circumflex_imag;
    delete [] sin_circumflex_real;
    fftw_free(sin_circumflex);
    fftw_free(sin_complex);
    exit_test(sin_real, sin_imag, naxes);
    BOOST_FAIL(write_sin_circumflex);
  }

  // fft_backward
  fftw_complex* sin_fb_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::fftw_backward(sin_circumflex, sin_fb_complex, naxes[0], naxes[1]);

  // compare input vs output
  float *sin_fb_real = new float [naxes[0]*naxes[1]];
  float *sin_fb_imag = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2realandimag(sin_fb_complex, sin_fb_real, sin_fb_imag, naxes[0], naxes[1]);
  for (int i = 0; i < naxes[0]; i++) {
    BOOST_CHECK(fabs(sin_fb_real[i]-sin_real[i]) < fabs(sin_real[i]*0.01));
  }
  for (int i = 0; i < naxes[1]; i++) {
    BOOST_CHECK(fabs(sin_fb_imag[i]-sin_imag[i]) < fabs(sin_imag[i]*0.01));
  }

  // free arrays
  delete [] sin_fb_imag;
  delete [] sin_fb_real;
  fftw_free(sin_fb_complex);
  delete [] sin_circumflex_imag;
  delete [] sin_circumflex_real;
  fftw_free(sin_circumflex);
  fftw_free(sin_complex);
  exit_test(sin_real, sin_imag, naxes);

}

BOOST_AUTO_TEST_CASE( fftw_test ) {
  TRACE_ENTER();

  // read gamma and stores it into two arrays
  std::string pathname_gamma_complex ("../Tools/tests/src/gamma_B.1_new.fits");
  float *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);

  // realandimag2complex
  fftw_complex* gamma_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::realandimag2complex(gamma_real, gamma_imag, gamma_complex, naxes[0], naxes[1]);

  // fftw_forward
  fftw_complex* gamma_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::fftw_forward(gamma_complex, gamma_circumflex, naxes[0], naxes[1]);

  // write gamma_circumflex
  std::string pathname_gamma_circumflex("../Tools/tests/src/gamma_B.circumflex.fits");
  std::string name_gamma_circumflex("gamma_circumflex");
  float *gamma_circumflex_real = new float [naxes[0]*naxes[1]];
  float *gamma_circumflex_imag = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2realandimag(gamma_circumflex, gamma_circumflex_real, gamma_circumflex_imag, naxes[0], naxes[1]);
  std::string write_gamma_circumflex = io::write_image_3D(pathname_gamma_circumflex, gamma_circumflex_real, gamma_circumflex_imag, name_gamma_circumflex, naxis, naxes);
  if (write_gamma_circumflex != "WRITE_OK") {
    delete [] gamma_circumflex_imag;
    delete [] gamma_circumflex_real;
    fftw_free(gamma_circumflex);
    fftw_free(gamma_complex);
    exit_test(gamma_real, gamma_imag, naxes);
    BOOST_FAIL(write_gamma_circumflex);
  }

  // fft_backward
  fftw_complex* gamma_fb_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*naxes[0]*naxes[1]);
  Tools::kg::fftw_backward(gamma_circumflex, gamma_fb_complex, naxes[0], naxes[1]);

  // compare input vs output
  float *gamma_fb_real = new float [naxes[0]*naxes[1]];
  float *gamma_fb_imag = new float [naxes[0]*naxes[1]];
  Tools::kg::complex2realandimag(gamma_fb_complex, gamma_fb_real, gamma_fb_imag, naxes[0], naxes[1]);
  for (int i = 0; i < naxes[0]; i++) {
    BOOST_CHECK(fabs(gamma_fb_real[i]-gamma_real[i]) < fabs(gamma_real[i]*0.01));
  }
  for (int i = 0; i < naxes[1]; i++) {
    BOOST_CHECK(fabs(gamma_fb_imag[i]-gamma_imag[i]) < fabs(gamma_imag[i]*0.01));
  }

  // free arrays
  delete [] gamma_fb_imag;
  delete [] gamma_fb_real;
  fftw_free(gamma_fb_complex);
  delete [] gamma_circumflex_imag;
  delete [] gamma_circumflex_real;
  fftw_free(gamma_circumflex);
  fftw_free(gamma_complex);
  exit_test(gamma_real, gamma_imag, naxes);
}

BOOST_AUTO_TEST_CASE( gamma2kappa_test ) {
  // this test only calls gamma2kappa, does not check anything.
  TRACE_ENTER();

  // read gamma and stores it into two arrays
  std::string pathname_gamma_complex ("../Tools/tests/src/gamma_B.1_new.fits");
  float *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);

  // gamma2kappa
  long nelements = 1;
  for (int i = 0; i < naxis; i++) {
    nelements = nelements*naxes[i];
  }
  float *kappaE = new float [nelements];
  float *kappaB = new float [nelements];
  Tools::kg::gamma2kappa(gamma_real, gamma_imag, kappaE, kappaB, naxes[0], naxes[1]);

  // write kappaE and kappaB
  std::string name_kappaE("kappaE");
  std::string write_kappaE = io::write_image("../Tools/tests/src/kappaE.fits", kappaE, name_kappaE, naxis, naxes);
  if (write_kappaE != "WRITE_OK") {
    delete [] kappaB;
    delete [] kappaE;
    exit_test(gamma_real, gamma_imag, naxes);
    BOOST_FAIL(write_kappaE);
  }
  std::string name_kappaB("kappaB");
  std::string write_kappaB = io::write_image("../Tools/tests/src/kappaB.fits", kappaB, name_kappaB, naxis, naxes);
  if (write_kappaB != "WRITE_OK") {
    delete [] kappaB;
    delete [] kappaE;
    exit_test(gamma_real, gamma_imag, naxes);
    BOOST_FAIL(write_kappaB);
  }

  // free arrays
  delete [] kappaB;
  delete [] kappaE;
  exit_test(gamma_real, gamma_imag, naxes);
}

BOOST_AUTO_TEST_CASE( gamma2kappa2gamma_test ) {
  // this test calls gamma2kappa and then kappa2gamma then checks that the output is similar to the input
  TRACE_ENTER();

  // read gamma and stores it into two arrays
  std::string pathname_gamma_complex ("../Tools/tests/src/gamma_B.1_new.fits");
  float *gamma_real = nullptr, *gamma_imag = nullptr;
  int naxis = 0;
  long *naxes = nullptr;
  init_test(pathname_gamma_complex, gamma_real, gamma_imag, naxis, naxes);

  // gamma2kappa
  long nelements = 1;
  for (int i = 0; i < naxis; i++) {
    nelements = nelements*naxes[i];
  }
  float *kappaE = new float [nelements];
  float *kappaB = new float [nelements];
  Tools::kg::gamma2kappa(gamma_real, gamma_imag, kappaE, kappaB, naxes[0], naxes[1]);

  // kappa2gamma
  float *gamma_g2k2g_real = new float [nelements];
  float *gamma_g2k2g_imag = new float [nelements];
  Tools::kg::kappa2gamma(kappaE, kappaB, gamma_g2k2g_real, gamma_g2k2g_imag, naxes[0], naxes[1]);

  // write gamma_g2k2g
  std::string name_gamma_g2k2g_real = "gamma_g2k2g_real";
  std::string write_gamma_g2k2g_real = io::write_image("../Tools/tests/src/gamma_B.g2k2g.real.fits", gamma_g2k2g_real, name_gamma_g2k2g_real, naxis, naxes);
  if (write_gamma_g2k2g_real != "WRITE_OK") {
    delete [] gamma_g2k2g_imag;
    delete [] gamma_g2k2g_real;
    delete [] kappaB;
    delete [] kappaE;
    exit_test(gamma_real, gamma_imag, naxes);
    BOOST_FAIL(write_gamma_g2k2g_real);
  }
  // write gamma_g2k2g
  std::string name_gamma_g2k2g_imag = "gamma_g2k2g_imag";
  std::string write_gamma_g2k2g_imag = io::write_image("../Tools/tests/src/gamma_B.g2k2g.imag.fits", gamma_g2k2g_imag, name_gamma_g2k2g_imag, naxis, naxes);
  if (write_gamma_g2k2g_imag != "WRITE_OK") {
    delete [] gamma_g2k2g_imag;
    delete [] gamma_g2k2g_real;
    delete [] kappaB;
    delete [] kappaE;
    exit_test(gamma_real, gamma_imag, naxes);
    BOOST_FAIL(write_gamma_g2k2g_imag);
  }

  // compare input vs output
  for (int i = 0; i < nelements; i++) {
    BOOST_CHECK(fabs(gamma_g2k2g_real[i]-gamma_real[i]) < fabs(gamma_real[i])*0.01);
  }
  for (int i = 0; i < nelements; i++) {
    BOOST_CHECK(fabs(gamma_g2k2g_imag[i]-gamma_imag[i]) < fabs(gamma_imag[i])*0.01);
  }

  // free arrays
  delete [] gamma_g2k2g_imag;
  delete [] gamma_g2k2g_real;
  delete [] kappaB;
  delete [] kappaE;
  exit_test(gamma_real, gamma_imag, naxes);
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
