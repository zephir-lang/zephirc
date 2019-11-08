// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>
#include <CLI/CLI11.hpp>

// TODO(klay): Make it better.
#include "../../src/commands/formatter.hpp"

class FormatterTest : public ::testing::Test {
 protected:
  FormatterTest() {}
};

TEST_F(FormatterTest, MakeUsage) {
    CLI::App app{"Zephir"};
    commands::Formatter formatter;

    std::string usage = formatter.make_usage(&app, "not used");
    EXPECT_EQ(usage, "Usage:\n  command [options] [arguments]\n");
}
