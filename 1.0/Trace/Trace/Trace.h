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

#define TRACE_ENTER() std::cout << Trace::trace_enter(Trace::nb_spaces) << __func__ << std::endl
#define TRACE_EXIT() std::cout << Trace::trace_exit(Trace::nb_spaces) << __func__ << std::endl
#define TRACE_DEBUG(debug_message) std::cout << Trace::trace_debug(Trace::nb_spaces, debug_message) << std::endl

namespace Trace {

static int nb_spaces = 0;

std::string trace_enter(int &nb_spaces);

std::string trace_exit(int &nb_spaces);

std::string trace_debug(int nb_spaces, std::ostringstream &debug_message);

std::string trace_debug(int nb_spaces, std::string debug_message);

std::string trace_debug(int nb_spaces, char *debug_message);

std::string trace_debug(int nb_spaces, int debug_message);

} /* namespace Trace */

#endif
