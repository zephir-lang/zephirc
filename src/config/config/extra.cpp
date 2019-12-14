// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <string>
#include <tuple>
#include <utility>

#include <zephir/config/extra.hpp>

zephir::config::Extra::Extra() : indent_("spaces"), exportc_(false) {}

zephir::config::Extra::Extra(std::string indent, bool exportc)
    : indent_(std::move(indent)), exportc_(exportc) {}

bool zephir::config::Extra::operator==(const zephir::config::Extra &rhs) const {
  auto lhs_key = std::tie(indent_, exportc_);
  auto rhs_key = std::tie(rhs.indent_, rhs.exportc_);

  return lhs_key == rhs_key;
}

zephir::config::Extra &
zephir::config::Extra::operator=(const zephir::config::Extra &rhs) = default;
