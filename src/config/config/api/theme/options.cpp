// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config/api/theme/options.hpp"

namespace ztheme = zephir::config::api::theme;

// TODO: Rename keys from link_color form to link-color form
ztheme::Options::Options()
    : container_({
          {"github", ""},
          {"analytics", ""},
          {"main_color", ""},
          {"link_color", "#3E6496"},
          {"link_hover_color", "#5F9AE7"},
      }){};

ztheme::Options::Options(std::map<std::string, std::string> container)
    : container_(std::move(container)) {}

bool ztheme::Options::operator==(const ztheme::Options &rhs) const {
  auto lhs_key = std::tie(container_);
  auto rhs_key = std::tie(rhs.container_);

  return lhs_key == rhs_key;
}

ztheme::Options &
ztheme::Options::operator=(const ztheme::Options &rhs) = default;
