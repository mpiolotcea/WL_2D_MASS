/**
 * @file Trace/Trace.h
 * @date 12/09/15
 * @author user
 */

#ifndef _TRACE_TRACE_H
#define _TRACE_TRACE_H

#include <iostream>
#include <string>
#include <sstream>

#define TRACE_ENTER() Trace::Trace trace; std::cout << trace.format_enter(Trace::Trace::nb_instances-1) << __func__ << std::endl
#define TRACE_DEBUG(debug_message) std::cout << Trace::Trace::format_debug(Trace::Trace::nb_instances, debug_message) << std::endl

namespace Trace {

/**
 * logs the entrance and exit of a method
 * logs debug messages
 */
class Trace {

public:

  /**
   * default constructor. Increases nb_instances
   */
  Trace();

  /**
   * destructor. Decreases nb_instances and calls format_exit
   */
  ~Trace();

  /**
   * writes an entrance message
   * @param nb_spaces number of spaces in the header of the output message
   * @return a formatted message to be logged
   */
  std::string format_enter(int nb_spaces);

  /**
   * writes an exit message
   * @param nb_spaces number of spaces in the header of the output message
   * @return a formatted message to be logged
   */
  std::string format_exit(int nb_spaces);

  /**
   * formats a debug message
   * @param nb_spaces number of spaces in the header of the output message
   * @param debug_message message to be formatted
   * @return a formatted message to be logged
   */
  static std::string format_debug(int nb_spaces, std::string debug_message);

  /**
   * number of instances of the class
   * warning : not thread-safe
   */
  static int nb_instances;

};

} /* namespace Trace */

#endif
