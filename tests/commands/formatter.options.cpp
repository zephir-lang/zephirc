// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <CLI/CLI11.hpp>

#include "formatter.hpp"
#include "zephir/commands.hpp"

class FormatterTest : public ::testing::Test {
 protected:
  FormatterTest() = default;
};

TEST_F(FormatterTest, MakeUsage) {
  CLI::App app{"Zephir"};
  zephir::commands::Formatter formatter;

  auto usage = formatter.make_usage(&app, "not used");
  EXPECT_EQ(usage, "Usage:\n  COMMAND [OPTIONS] [--] [ARGUMENTS]\n");
}
