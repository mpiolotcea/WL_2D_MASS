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
  // read gamma_input from pathname_input
  std::string pathname_input("../Tools/tests/src/gamma_B.1_new.fits");
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
  // write gamma_input into pathname_output
  std::string pathname_output("../Tools/tests/src/gamma_B.1_duplicate.fits");
  std::string name_output("gamma_output");
  std::string write_output = io::write_image(pathname_output, gamma_input, name_output, naxis_input, naxes_input);
  if (write_output != "WRITE_OK") {
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(write_output);
  }
  // read gamma_output from pathname_output
  double *gamma_output = nullptr;
  int naxis_output = 0;
  long *naxes_output = nullptr;
  std::string read_output = io::read_image(pathname_output, gamma_output, naxis_output, naxes_output);
  if (read_output != "READ_OK") {
    if (gamma_output != nullptr) {
      delete [] gamma_output;
    }
    delete [] gamma_input;
    delete [] naxes_input;
    BOOST_FAIL(read_output);
  }
  // compare output vs input
  BOOST_CHECK(naxis_output == naxis_input);
  for (int naxe = 0; naxe < naxis_output; naxe++) {
    BOOST_CHECK(naxes_output[naxe] == naxes_input[naxe]);
  }
  for (int x = 0; x < naxes_output[0]; x++) {
    for (int y = 0; y < naxes_output[1]; y++) {
      for (int z = 0; z < naxes_output[2]; z++) {
        BOOST_CHECK (fabs(gamma_output[z*naxes_output[1]*naxes_output[0]+x*naxes_output[1]+y]-gamma_input[z*naxes_input[1]*naxes_input[0]+x*naxes_input[1]+y]) <= fabs(gamma_input[z*naxes_input[1]*naxes_input[0]+x*naxes_input[1]+y]*0.01));
      }
    }
  }
  // free arrays
  delete [] gamma_output;
  delete [] gamma_input;
  delete [] naxes_input;
}

BOOST_AUTO_TEST_CASE( read3Dwriteread3D_test ) {
  TRACE_ENTER();
  // read gamma_input from pathname_input
  std::string pathname_input("../Tools/tests/src/gamma_B.1_new.fits");
  double **gamma_input = nullptr;
  int naxis_input = 0;
  long *naxes_input = nullptr;
  std::string read_input = io::read_3D_image(pathname_input, gamma_input, naxis_input, naxes_input);
  if (read_input != "READ_OK") {
    if (gamma_input != nullptr) {
      delete [] gamma_input[1];
      delete [] gamma_input[0];
    }
    if (naxes_input != nullptr) {
      delete [] naxes_input;
    }
    BOOST_FAIL(read_input);
  }
  // write gamma_input into pathname_output
  std::string pathname_output("../Tools/tests/src/gamma_B.1_new.read3dim.fits");
  std::string name_output("gamma_output");
  std::string write_output = io::write_image(pathname_output, &gamma_input[0][0], name_output, naxis_input, naxes_input);
  if (write_output != "WRITE_OK") {
    delete [] gamma_input[1];
    delete [] gamma_input[0];
    delete [] naxes_input;
    BOOST_FAIL(write_output);
  }
  // write gamma_input into pathname_output
  std::string pathname_output_1("../Tools/tests/src/gamma_B.1_new.read3dim.1.fits");
  std::string name_output_1("gamma_output_1");
  std::string write_output_1 = io::write_image(pathname_output_1, &gamma_input[0][0], name_output_1, naxis_input-1, naxes_input);
  if (write_output_1 != "WRITE_OK") {
    delete [] gamma_input[1];
    delete [] gamma_input[0];
    delete [] naxes_input;
    BOOST_FAIL(write_output_1);
  }
  // write gamma_input into pathname_output
  std::string pathname_output_2("../Tools/tests/src/gamma_B.1_new.read3dim.2.fits");
  std::string name_output_2("gamma_output_2");
  std::string write_output_2 = io::write_image(pathname_output_2, &gamma_input[1][0], name_output_2, naxis_input-1, naxes_input);
  if (write_output_2 != "WRITE_OK") {
    delete [] gamma_input[1];
    delete [] gamma_input[0];
    delete [] naxes_input;
    BOOST_FAIL(write_output_2);
  }
  // read gamma_output from pathname_output
  double *gamma_output = nullptr;
  int naxis_output = 0;
  long *naxes_output = nullptr;
  std::string read_output = io::read_image(pathname_output, gamma_output, naxis_output, naxes_output);
  if (read_output != "READ_OK") {
    if (gamma_output != nullptr) {
      delete [] gamma_output;
    }
    delete [] gamma_input[1];
    delete [] gamma_input[0];
    delete [] naxes_input;
    BOOST_FAIL(read_output);
  }
  // free arrays
  delete [] gamma_output;
  delete [] gamma_input[1];
  delete [] gamma_input[0];
  delete [] naxes_input;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()
