// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "abstract_command.hpp"

#include <utility>

zephir::console::commands::AbstractCommand::AbstractCommand(std::string name)
    : name_(std::move(name)) {}

std::string
zephir::console::commands::AbstractCommand::CommonCompilationFlagsHelp() {
  const auto FLAGS = R"FLAGS(
  Common flags are:
      -f([a-z0-9\-]+)    Enables compiler optimizations
      -fno-([a-z0-9\-]+) Disables compiler optimizations
      -w([a-z0-9\-]+)    Turns a warning on
      -W([a-z0-9\-]+)    Turns a warning off)FLAGS";

  return FLAGS;
}
