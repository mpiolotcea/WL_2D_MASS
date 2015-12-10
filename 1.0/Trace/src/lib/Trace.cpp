/**
 * @file src/lib/Trace.cpp
 * @date 12/09/15
 * @author user
 */

#include "Trace/Trace.h"

namespace Trace {

int Trace::nb_instances = 0;

Trace::Trace() { nb_instances++; }

Trace::~Trace() { nb_instances--; std::cout << format_exit(nb_instances) << std::endl; }

std::string Trace::format_enter(int nb_spaces) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "ENTER ";
  return oss.str();
}

std::string Trace::format_exit(int nb_spaces) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "EXIT";
  return oss.str();
}

std::string Trace::format_debug(int nb_spaces, std::string debug_message) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "DEBUG " << debug_message;
  return oss.str();
}

std::string Trace::format_info(int nb_spaces, std::string info_message) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "INFO " << info_message;
  return oss.str();
}

std::string Trace::format_warn(int nb_spaces, std::string warn_message) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "WARN " << warn_message;
  return oss.str();
}

std::string Trace::format_error(int nb_spaces, std::string error_message) {
  std::ostringstream oss;
  for (int nb_space = 0; nb_space < nb_spaces; nb_space++) {
    oss << " ";
  }
  oss << "ERROR " << error_message;
  return oss.str();
}

} // Trace namespace
