// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "FileSystem.hpp"

#include <unistd.h>  // access(), getcwd()

bool zephir::filesystem::exists(const std::string &name) noexcept {
  return (access(name.c_str(), F_OK) != -1);
}

std::string zephir::filesystem::current_path() {
  auto cwd = getcwd(nullptr, 0);
  return cwd ? std::string(cwd) : std::string();
}
