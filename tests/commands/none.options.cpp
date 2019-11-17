// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <utility>

#include "argv.hpp"
#include "commands.hpp"
#include "zephir/main.hpp"

class NoneCmdTest
    : public testing::TestWithParam<std::tuple<std::string, int>> {
 protected:
  NoneCmdTest() : argv(){};
  Argv argv;
};

TEST_P(NoneCmdTest, RunUsingGlobalOptions) {
  int expected = std::get<1>(GetParam());
  const std::string& option = std::get<0>(GetParam());

  argv.assign({"zephir", option.c_str()});
  auto actual = zephir::commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    BulkTest, NoneCmdTest,
    testing::Values(std::make_tuple("--help", EXIT_HELP),
                    std::make_tuple("--version", EXIT_SUCCESS),
                    std::make_tuple("--vernum", EXIT_SUCCESS),
                    std::make_tuple("--dumpversion", EXIT_SUCCESS)));
