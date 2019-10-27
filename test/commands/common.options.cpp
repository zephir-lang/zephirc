#include <gtest/gtest.h>
#include <cstring>

// TODO: Make it better
#include "../../src/commands/cmd.hpp"
#include "../../src/commands/optionexception.hpp"
#include "../argv.hpp"

TEST(common_cmd, without_params) {
  Argv argv({"zephir", ""});
  char **args = argv.argv();

  commands::Cmd cmd;
  std::memset(&cmd, 0, sizeof(cmd));

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
