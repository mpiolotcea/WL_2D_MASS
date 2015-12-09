/**
 * @file src/lib/Trace.cpp
 * @date 12/09/15
 * @author user
 */

#include "Trace/Trace.h"

namespace Trace {

void trace_enter(int &nb_spaces) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "ENTER " << __func__ << std::endl;
  nb_spaces++;
}

void trace_exit(int &nb_spaces) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "EXIT " << __func__ << std::endl;
  nb_spaces--;
}

void trace_debug(int nb_spaces, std::ostringstream& debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "DEBUG " << debug_message << std::endl;
}

void trace_debug(int nb_spaces, std::string& debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "DEBUG " << debug_message << std::endl;
}

void trace_debug(int nb_spaces, char *&debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "DEBUG " << debug_message << std::endl;
}

void trace_debug(int nb_spaces, int &debug_message) {
  std::ostringstream log_header;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    log_header << " ";
  }
  std::cout << log_header << "DEBUG " << debug_message << std::endl;
}

} // Trace namespace
