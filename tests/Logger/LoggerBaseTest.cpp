// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "Config/Context.hpp"
#include "Logger/Logger.hpp"

class LoggerBaseTest : public ::testing::Test {
 protected:
  LoggerBaseTest() = default;
};

TEST_F(LoggerBaseTest, CreateSimpleLogLevels) {
  auto test_logger = new zephir::Logger();

  test_logger->info("Test message");
  test_logger->warn("Test message");
  test_logger->error("Test message");
}

TEST_F(LoggerBaseTest, LogFormatter) {
  auto test_logger = new zephir::Logger();

  testing::internal::CaptureStdout();
  test_logger->info("Test message");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ("info: Test message\n", output);
}

TEST_F(LoggerBaseTest, LogContext) {
  auto test_logger = new zephir::Logger();
  auto ctx = new zephir::Context("./testfile.zep", 10, 42);

  std::string errorMsg =
      "incompatible pointer to integer conversion assigning to 'char' from "
      "'void *'";
  std::string category = "-Wint-conversion";

  testing::internal::CaptureStdout();
  test_logger->log(errorMsg, zephir::LogLevel::warn, category, ctx);
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(
      "warning: incompatible pointer to integer conversion assigning to 'char' "
      "from 'void *' in file ./testfile.zep on line 10:42 [-Wint-conversion]\n",
      output);
}
