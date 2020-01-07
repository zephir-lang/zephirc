// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_LOGGER_FACADE_HPP_
#define ZEPHIR_LOGGER_FACADE_HPP_

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <string>

namespace zephir {

// TODO (alexndr.mac): change tuple to struct
typedef std::vector<std::tuple<std::string, std::string>> Context;

/// \brief A type definition for a unique pointer to a spdlog::logger instance.
using LoggerPtr = std::unique_ptr<spdlog::logger>;

/// \brief Wrap third party log library
/// and provide minimalistic interface for Zephir log writer
class Logger {
 private:
  /// spdlog's global registry name
  const std::string _logger_name = "console_logger";

  LoggerPtr _logger;

 public:
  /// \brief Construct a new logger
  Logger();

  ~Logger();

  /**
   * @brief Add a log record with INFO level
   *
   * @param message - The log message
   */
  void info(const std::string& message);

  /**
   * @brief Add a log record with WARNING level
   *
   * @param message - The log message
   */
  void warning(const std::string& message);

  /**
   * @brief Add a log record with ERROR level
   *
   * @param message - The log message
   */
  void error(const std::string& message);

  /**
   * @brief Add a log record with DEBUG level
   *
   * @param message - The log message
   */
  void debug(const std::string& message);

  /**
   * @brief Add a log record from Exception
   *
   * @param message - The log message
   * @param ctx - The process context detail
   */
  void exception(const std::exception& error, const Context& ctx);

  /**
   * @brief Add a log record with specified level, category and context
   *
   * @param message - The log message
   * @param level - The logging level
   * @param category - The log category
   * @param ctx - The log context
   */
  void log(const std::string& message, int level, const std::string& category,
           const Context& ctx);
};

}  // namespace zephir

#endif  // ZEPHIR_LOGGER_FACADE_HPP_
