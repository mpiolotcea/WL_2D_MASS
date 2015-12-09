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

#define TRACE_ENTER() Trace::trace_enter(Trace::nb_spaces)
#define TRACE_EXIT() Trace::trace_exit(Trace::nb_spaces)
#define TRACE_DEBUG(debug_message) Trace::trace_debug(Trace::nb_spaces, debug_message)

namespace Trace {

static int nb_spaces = 0;

void trace_enter(int &nb_spaces);

void trace_exit(int &nb_spaces);

void trace_debug(int nb_spaces, std::ostringstream &debug_message);

void trace_debug(int nb_spaces, std::string &debug_message);

void trace_debug(int nb_spaces, char *&debug_message);

void trace_debug(int nb_spaces, int &debug_message);

} /* namespace Trace */

#endif
