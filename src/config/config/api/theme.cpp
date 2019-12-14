// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <zephir/config/api/theme.hpp>

namespace ztheme = zephir::config::api::theme;

zephir::config::api::Theme::Theme() : name_("zephir"), options_() {}

zephir::config::api::Theme::Theme(std::string name,
                                  const ztheme::Options &options)
    : name_(std::move(name)), options_(options) {}

bool zephir::config::api::Theme::operator==(
    const zephir::config::api::Theme &rhs) const {
  auto lhs_key = std::tie(name_, options_);
  auto rhs_key = std::tie(rhs.name_, rhs.options_);

  return lhs_key == rhs_key;
}
