// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_FORMATTER_HPP_
#define ZEPHIR_COMMANDS_FORMATTER_HPP_

#include <CLI/CLI11.hpp>
#include <string>

namespace commands {
    class Formatter : public CLI::Formatter {
        public:
        Formatter();
        std::string make_usage(const CLI::App *app, std::string name) const override;
    };
}

#endif  // ZEPHIR_COMMANDS_FORMATTER_HPP_
