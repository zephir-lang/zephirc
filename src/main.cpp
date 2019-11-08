// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "commands/commands.hpp"

int main(int argc, char** argv) {
  auto retval = commands::optparse(argc, argv);

  return retval;
}
