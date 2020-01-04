// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code

/// \file main.hpp
/// \brief Provides common macros and helper functions.

#ifndef ZEPHIR_MAIN_HPP_
#define ZEPHIR_MAIN_HPP_

/// \brief This macro internally used in the \a TOSTRING macro.
#define STRINGIFY(s) #s

/// \brief This macro is used to represent \a s as a string.
#define TOSTRING(s) STRINGIFY(s)

#endif  // ZEPHIR_MAIN_HPP_
