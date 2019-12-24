// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include "console/formatter.hpp"

class FormatterTest : public ::testing::Test {
 protected:
  FormatterTest() = default;
};

TEST_F(FormatterTest, MakeUsage) {
  auto app(std::make_shared<CLI::App>());
  auto formatter(std::make_shared<zephir::console::Formatter>());
  auto usage = formatter->make_usage(app.get(), "not used");

  EXPECT_EQ(usage, "Usage:\n  COMMAND [OPTIONS] [--] [ARGUMENTS]\n");
}
