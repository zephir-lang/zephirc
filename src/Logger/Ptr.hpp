// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file Ptr.hpp
/// \brief \brief Represents type definition for a unique/shared pointers
/// to a Logger instance.

#ifndef ZEPHIR_LOGGER_PTR_HPP
#define ZEPHIR_LOGGER_PTR_HPP

namespace zephir {
class Logger;

/// \brief A type definition for SpdLog levels enum.
using LogLevelEnum = spdlog::level::level_enum;

/// \brief A type definition for a unique pointer to a spdlog::logger instance.
using LoggerPtr = std::unique_ptr<spdlog::logger>;

/// \brief A type definition for a shared pointer to a zephir::Config instance.
using ConfigPtr = std::shared_ptr<zephir::Config>;

}  // namespace zephir

#endif  // ZEPHIR_LOGGER_PTR_HPP
