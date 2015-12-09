/**
 * @file src/lib/Trace.cpp
 * @date 12/09/15
 * @author user
 */

#include "Trace/Trace.h"

namespace Trace {

std::string trace_enter(int &nb_spaces) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "ENTER ";
  nb_spaces++;
  return log_header.str();
}

std::string trace_exit(int &nb_spaces) {
  nb_spaces--;
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "EXIT ";
  return log_header.str();
}

std::string trace_debug(int nb_spaces, std::ostringstream &debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "DEBUG " << debug_message.str();
  return log_header.str();
}

std::string trace_debug(int nb_spaces, std::string debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "DEBUG " << debug_message;
  return log_header.str();
}

std::string trace_debug(int nb_spaces, char *debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "DEBUG " << debug_message;
  return log_header.str();
}

std::string trace_debug(int nb_spaces, int debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  log_header << "DEBUG " << debug_message;
  return log_header.str();
}

} // Trace namespace
