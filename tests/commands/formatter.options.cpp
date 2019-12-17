// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <CLI/CLI.hpp>
#include <zephir/cli/formatter.hpp>

class FormatterTest : public ::testing::Test {
 protected:
  FormatterTest() = default;
};

TEST_F(FormatterTest, MakeUsage) {
  CLI::App app{"Zephir"};
  zephir::cli::Formatter formatter;

  auto usage = formatter.make_usage(&app, "not used");
  EXPECT_EQ(usage, "Usage:\n  COMMAND [OPTIONS] [--] [ARGUMENTS]\n");
}
