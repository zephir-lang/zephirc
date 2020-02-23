// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "LoggerBaseTest.hpp"

#include <gtest/gtest.h>

#include <memory>

#include "Config/Context.hpp"
#include "Logger/Logger.hpp"

TEST_F(LoggerBaseTest, CreateSimpleLogLevels) {
  test_logger->info("Test message");
  test_logger->warn("Test message");
  test_logger->error("Test message");
}

TEST_F(LoggerBaseTest, LogFormatter) {
  testing::internal::CaptureStdout();
  test_logger->info("Test message");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ("info: Test message\n", output);
}

TEST_F(LoggerBaseTest, LogContext) {
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

TEST_F(LoggerBaseTest, LoggerLifeCycle) {
  auto test = new zephir::Logger(config);

  EXPECT_TRUE(nullptr != test)
      << "Logger instance should not be nullptr";

  delete test;
}
