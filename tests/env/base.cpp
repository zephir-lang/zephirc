// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "base.hpp"

#include <unistd.h> /* getcwd */

#include <cassert> /* assert */
#include <climits> /* PATH_MAX */
#include <cstdlib> /* getenv */
#include <string>

void TestEnvironment::SetUp() {
  cwd();
  tests_root();
}

std::string TestEnvironment::cwd() {
  char path[PATH_MAX];
  assert(getcwd(path, PATH_MAX) != nullptr);

  return std::string(path);
}

std::string TestEnvironment::tests_root() {
  char* tests_root = getenv("ZEPHIR_TESTS_ROOT");
  if (tests_root == nullptr) {
    return "";
  }

  return std::string(tests_root);
}
