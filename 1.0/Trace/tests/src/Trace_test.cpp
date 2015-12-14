/**
 * @file tests/src/Trace_test.cpp
 * @date 12/09/15
 * @author user
 */

#include <boost/test/unit_test.hpp>

#include "Trace/Trace.h"

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE (Trace_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( trace_test ) {
  // enter
  TRACE_ENTER();
  // debug
  std::string s("Hello, world !");
  TRACE_DEBUG(s);
  // info
  TRACE_INFO(s);
  // warn
  TRACE_WARN(s);
  // error
  TRACE_ERROR(s);
  // status
  std::cout << FORMAT_STATUS(0) << std::endl;
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END ()


