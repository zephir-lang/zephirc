#include "zephir/filesystem.hpp"

#include <unistd.h>

#include <cerrno>
#include <climits>
#include <sstream>

bool compiler::filesystem::exists(const std::string &name) {
  return (access(name.c_str(), F_OK) != -1);
}

std::string compiler::filesystem::current_path() {
  char temp[PATH_MAX];

  if (getcwd(temp, PATH_MAX) != nullptr) {
    return std::string(temp);
  }

  int error = errno;
  std::string err_prefix = "An error occurred related to";
  std::string err_suffix = "when obtaining current working directory";

  switch (error) {
    case EACCES:
      throw std::runtime_error(err_prefix + " access rights " + err_suffix);
    case ENOMEM:
      throw std::runtime_error(err_prefix + " insufficient storage " +
                               err_suffix);
    default: {
      std::ostringstream str;
      str << "Unrecognised error occurred " << err_suffix << ": " << error;
      throw std::runtime_error(str.str());
    }
  }
}
