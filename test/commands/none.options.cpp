#include <gtest/gtest.h>

#include <cstring>

// TODO: Make it better
#include "../../src/commands/cmd.hpp"
#include "../../src/commands/optionexception.hpp"
#include "../argv.hpp"

class NoneCmdTest : public ::testing::Test {
 protected:
  void SetUp() override { std::memset(&cmd, 0, sizeof(cmd)); }

  commands::Cmd cmd;
};

TEST_F(NoneCmdTest, InitWithoutParams) {
  Argv argv({"zephir", ""});
  char **args = argv.argv();

  // command is NONE
  EXPECT_TRUE(commands::parseopt(args, cmd));
  EXPECT_EQ(cmd.kind, commands::CmdKind::NONE);

  // all global options in default state
  EXPECT_FALSE(cmd.common.quiet);
  EXPECT_FALSE(cmd.common.help);
  EXPECT_FALSE(cmd.common.version);
  EXPECT_FALSE(cmd.common.vernum);
  EXPECT_FALSE(cmd.common.dumpversion);
}
