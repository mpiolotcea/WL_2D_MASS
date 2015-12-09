/**
 * @file tests/src/Trace_test.cpp
 * @date 12/09/15
 * @author user
 */

#include <boost/test/unit_test.hpp>

#include "Trace/Trace.h"

using namespace Trace;

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (Trace_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( example_test ) {
  // enter
  TRACE_ENTER();
  // std::string
  std::string s("Hello, world !");
  TRACE_DEBUG(s);
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()


