// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "filesystem.hpp"

#include <unistd.h>

#include <climits>

bool zephir::filesystem::exists(const std::string &name) noexcept {
  return (access(name.c_str(), F_OK) != -1);
}

std::string zephir::filesystem::cwd() {
  char temp[PATH_MAX];
  return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}
