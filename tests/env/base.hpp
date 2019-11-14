// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TESTS_ENV_BASE_HPP_
#define ZEPHIR_TESTS_ENV_BASE_HPP_

#include <gtest/gtest.h>

#include <string>

class TestEnvironment : public ::testing::Environment {
 public:
  void SetUp() override;
  static std::string cwd();
  static std::string tests_root();
};

#endif  // ZEPHIR_TESTS_ENV_BASE_HPP_
