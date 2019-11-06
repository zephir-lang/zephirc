// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_OPTIONS_HPP_
#define ZEPHIR_COMMANDS_OPTIONS_HPP_

#include <string>
#include <vector>

#include "parse_result.hpp"

namespace commands {
class Options {
 public:
  Options() noexcept;
  ParseResult parse(const std::vector<const char *> &args);

 private:
  inline void set_help_flag(ParseResult &pr);
  inline void set_backend(ParseResult &pr, const char *backend);
  std::string program;
};

}  // namespace commands

#endif  // ZEPHIR_COMMANDS_OPTIONS_HPP_
