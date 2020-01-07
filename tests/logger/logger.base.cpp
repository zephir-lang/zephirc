// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "logger/logger.hpp"
class LoggerBaseTest : public ::testing::Test {
 protected:
  LoggerBaseTest() = default;
};

TEST_F(LoggerBaseTest, SimpleLogInfo) {
  auto test_logger = new zephir::Logger();

  test_logger->info("zephir");
}
