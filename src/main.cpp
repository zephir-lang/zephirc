// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config/config.hpp"
#include "filesystem/filesystem.hpp"

int main(int argc, char** argv) {
  auto cwd = zephir::filesystem::GetCurrentWorkingPath();
  auto config = zephir::Config::CreateFromArgv(argc, argv, cwd + "/config.yml");

  // TODO(klay): Catch exceptions

  // TODO: Planned flow design
  // -----------------------------------------------------------------------
  // 1. auto cmd = zephir::command::CreateFromArgv(argc, argv);
  //    1a. auto cwd = zephir::filesystem::GetCurrentWorkingPath();
  //    1b. auto config = zephir::Config::CreateFromArgv(argc, argv, cwd);
  // 2. auto retval = cmd.Execute();
  //    2a. zephir::compiler::CommandName();
  // 3. return retval;
  // -----------------------------------------------------------------------
  // 1..9    Should be invoked from main.cpp
  // 1a..1z  Should be invoked from command::CreateFromArgv
  // 2a..2z  Should be invoked from cmd.Execute

  return EXIT_SUCCESS;
}
