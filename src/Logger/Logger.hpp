// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file Logger.hpp
/// \brief The main Logger class. Provides simple interface for log writer.

#ifndef ZEPHIR_LOGGER_HPP_
#define ZEPHIR_LOGGER_HPP_

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

namespace zephir {

/// \brief Collection of all context details.
struct Context {
  Context(const std::string& fl, int ln, int cur)
      : file(fl), line(ln), cursor(cur) {}
  /// Absolute file path to zephir file.
  std::string file{""};
  /// Line number in zephir source file.
  int line;
  /// Context character position in zephir source file.
  int cursor;
};

/// \brief Log levels enum.
enum class LogLevel {
  info = spdlog::level::info,
  warn = spdlog::level::warn,
  error = spdlog::level::err,
  off = spdlog::level::off,
};

/// \brief A type definition for SpdLog levels enum.
using LogLevelEnum = spdlog::level::level_enum;

/// \brief A type definition for a unique pointer to a spdlog::logger instance.
using LoggerPtr = std::unique_ptr<spdlog::logger>;

/// \brief Wrap third party log library
/// and provide minimalistic interface for Zephir log writer.
class Logger {
 private:
  /// spdlog's global registry name
  const std::string _channel = "console";

  /// default message format
  const std::string _format = "%l: %v";

  LoggerPtr _logger;

 public:
  /// \brief Construct a new Logger.
  Logger();

  ~Logger();

  /// \brief Disable copy and move ctor.
  /// \note Deleted copy ctor inhibit the compiler from declaring move members.
  Logger(const Logger& logger) = delete;
  Logger& operator=(const Logger& logger) = delete;

  /// \brief Add a log record with INFO level.
  ///
  /// \param message - The log message.
  void info(const std::string& message);

  /// \brief Add a log record with WARNING level.
  ///
  /// \param message - The log message.
  void warn(const std::string& message);

  /// \brief Add a log record with ERROR level.
  ///
  /// \param message - The log message.
  void error(const std::string& message);

  /// \brief Add a log record with specified level, category and context.
  ///
  /// \param message - The log message.
  /// \param level - The logging level.
  /// \param category - The log category.
  /// \param ctx - The log context.
  void log(const std::string& message, zephir::LogLevel level,
           const std::string& category, const Context& ctx);
};

}  // namespace zephir

#endif  // ZEPHIR_LOGGER_HPP_
