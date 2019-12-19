// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_THEME_PTR_OPTIONS_HPP_
#define ZEPHIR_CONFIG_API_THEME_PTR_OPTIONS_HPP_

#include <memory>

namespace zephir::config::api::theme {
class Options;
using OptionsPtr = std::shared_ptr<Options>;
}  // namespace zephir::config::api::theme

#endif  // ZEPHIR_CONFIG_API_THEME_PTR_OPTIONS_HPP_
