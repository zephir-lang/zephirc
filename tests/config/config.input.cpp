// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "config/config.hpp"
#include "config_tester.hpp"

TEST_F(ConfigBaseTest, DisableOptimizationFromCli) {
  argv.assign({"-fno-constant-folding"});
  auto config = zephir::Config::factory(argv, "fake");

  EXPECT_FALSE(config->get("constant-folding", "optimizations", true));
  EXPECT_TRUE(argv.empty());
}

TEST_F(ConfigBaseTest, EnableOptimizationFromCli) {
  argv.assign({"-fcheck-invalid-reads"});
  auto config = zephir::Config::factory(argv, "fake");

  EXPECT_TRUE(config->get("check-invalid-reads", "optimizations", false));
  EXPECT_TRUE(argv.empty());
}

TEST_F(ConfigBaseTest, DisableWarningFromCli) {
  argv.assign({"-Wunused-variable"});
  auto config = zephir::Config::factory(argv, "fake");

  EXPECT_FALSE(config->get("unused-variable", "warnings", true));
  EXPECT_TRUE(argv.empty());
}

TEST_F(ConfigBaseTest, EnableOWarningFromCli) {
  argv.assign({"-wunused-variable-external"});
  auto config = zephir::Config::factory(argv, "fake");

  EXPECT_TRUE(config->get("unused-variable-external", "warnings", false));
  EXPECT_TRUE(argv.empty());
}

TEST_F(ConfigBaseTest, EnableExtraFromCli) {
  argv.assign({"--export-classes"});
  auto config = zephir::Config::factory(argv, "fake");

  EXPECT_TRUE(config->get("export-classes", "extra", false));
  EXPECT_TRUE(argv.empty());
}

TEST_F(ConfigBaseTest, SettingUnknownParameterHasNoEffect) {
  argv.assign({"-undefined"});
  auto config = zephir::Config::factory(argv, "fake");

  auto actual = config->get<std::string>("undefined", "");
  EXPECT_EQ("", actual);
  EXPECT_FALSE(argv.empty());
}
