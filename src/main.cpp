// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config/config.hpp"
#include "filesystem/filesystem.hpp"

int main(int argc, char** argv) {
  auto cwd = zephir::filesystem::current_path();
  auto config = zephir::Config::CreateFromArgv(argc, argv, cwd + "/config.yml");

  // TODO(klay): Catch exceptions

  return EXIT_SUCCESS;
}
