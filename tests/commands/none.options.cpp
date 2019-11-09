// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <gtest/gtest.h>

#include <utility>

#include "argv.hpp"
#include "commands.hpp"

struct ArgsProvider {
  std::initializer_list<const char*> args;
  int expected;

  ArgsProvider(std::initializer_list<const char*> new_args, int new_expected)
      : args(new_args), expected(new_expected){};
};

class NoneCmdTest : public testing::TestWithParam<ArgsProvider> {
 protected:
  NoneCmdTest() : argv(){};
  Argv argv;
};

ArgsProvider argsProvider[] = {
    {{"zephir", "--help"}, ZEPHIR_COMMANDS_EXIT_HELP},
    {{"zephir", "--version"}, 0},
    {{"zephir", "--vernum"}, 0},
    {{"zephir", "--dumpversion"}, 0},
};

TEST_P(NoneCmdTest, RunUsingGlobalOptions) {
  argv.assign(GetParam().args);
  auto retval = commands::optparse(argv.argc(), argv.argv());
  EXPECT_EQ(retval, GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(BulkTest, NoneCmdTest,
                         testing::ValuesIn(argsProvider));
