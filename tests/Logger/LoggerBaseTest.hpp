// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_TESTS_LOGGER_LOGGER_BASE_TEST_HPP_
#define ZEPHIR_TESTS_LOGGER_LOGGER_BASE_TEST_HPP_

#include <gtest/gtest.h>

#include <memory>

#include <Config/Config.hpp>
#include <Logger/Logger.hpp>
#include <Logger/Ptr.hpp>

class LoggerBaseTest : public ::testing::Test {
 protected:
  zephir::ConfigPtr config;
  std::unique_ptr<zephir::Logger> test_logger;

  LoggerBaseTest() : config(){};

  void SetUp() override {
    config = std::make_shared<zephir::Config>("fake");
    test_logger = std::make_unique<zephir::Logger>(config);
  }

  void TearDown() override {
    test_logger.reset();
    config.reset();
  }
};

#endif  // ZEPHIR_TESTS_LOGGER_LOGGER_BASE_TEST_HPP_
