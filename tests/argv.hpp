// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TEST_ARGV_HPP_
#define ZEPHIR_TEST_ARGV_HPP_

#include <initializer_list>
#include <memory>
#include <vector>

class Argv {
 public:
  Argv(std::initializer_list<const char*> args);
  std::vector<const char*> argv() const;

 private:
  std::vector<const char*> m_argv;
};

#endif  // ZEPHIR_TEST_ARGV_HPP_
