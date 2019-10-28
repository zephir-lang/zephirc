#include <gtest/gtest.h>

#include <cstring>

// TODO: Make it better
#include "../../src/commands/cmd.hpp"
#include "../../src/commands/optionexception.hpp"
#include "../../src/commands/options.hpp"
#include "../argv.hpp"

class NoneCmdTest : public ::testing::Test {
 protected:
  NoneCmdTest() : options(), cmd() {}

  commands::Cmd cmd;
  commands::Options options;
};

TEST_F(NoneCmdTest, InitWithoutParams) {
  Argv argv({"zephir", ""});
  char **args = argv.argv();

  // command is NONE
  options.parseopt(args, cmd);
  EXPECT_EQ(cmd.kind, commands::CmdKind::NONE);

  // all global options in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}
