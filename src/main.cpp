// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <memory>

#include "zephir/config.hpp"
#include "zephir/filesystem.hpp"

int main(int argc, char** argv) {
  auto config = std::make_unique<compiler::Config>();
  auto cwd = compiler::filesystem::current_path();

  auto retval =
      compiler::load_config(config.get(), argc, argv, cwd + "/config.yml");
  if (retval != EXIT_SUCCESS) {
    return retval;
  }

  return EXIT_SUCCESS;
}
