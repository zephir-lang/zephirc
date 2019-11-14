// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TESTS_ARGV_HPP_
#define ZEPHIR_TESTS_ARGV_HPP_

#include <initializer_list>
#include <memory>
#include <vector>

class Argv {
 public:
  Argv();
  void assign(std::initializer_list<const char*> args);
  [[nodiscard]] char** argv() const;
  [[nodiscard]] int argc() const;

 private:
  std::vector<std::unique_ptr<char[]>> m_args;
  std::unique_ptr<char*[]> m_argv;
  int m_argc;
};

#endif  // ZEPHIR_TESTS_ARGV_HPP_
