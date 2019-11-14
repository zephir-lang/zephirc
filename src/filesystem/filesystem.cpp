// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "filesystem.hpp"

#include <unistd.h>

#include <climits>
#include <sstream>

bool zephir::filesystem::exists(const std::string &name) {
  return (access(name.c_str(), F_OK) != -1);
}

std::string zephir::filesystem::current_path() {
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
