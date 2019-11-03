// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <iostream>
#include <string>

#include "cmd.hpp"
#include "optionexception.hpp"
#include "options.hpp"

/*!types:re2c*/
namespace commands {

Options::Options() noexcept : m_program("Zephir") {}

void Options::parseopt(char **argv, Cmd &cmd) {
  char *YYCURSOR, *YYMARKER;
  int cond = 0;

loop:
  YYCURSOR = *++argv;
  if (!YYCURSOR || *YYCURSOR == '\0') return;

  /*!re2c
   re2c:define:YYCTYPE = "unsigned char";
   re2c:yyfill:enable = 0;
   re2c:yych:conversion = 1;
   re2c:indent:top = 2;
   re2c:indent:string = "    ";
   re2c:define:YYGETCONDITION = "cond";
   re2c:define:YYGETCONDITION:naked = 1;
   re2c:define:YYSETCONDITION = "cond = @@;";
   re2c:define:YYSETCONDITION:naked = 1;

   end = "\x00";
   eq  = "=";

   <init> * {
      throw OptionException(
         "Command '" + std::string(*argv) + "' is not defined");
   }

   <init> ("-h" | "--help") end {
      cmd.common.help = true;
      return;
   }

   <init> ("-v" | "--version") end {
      cmd.common.version = true;
      return;
   }

   <init> "--vernum" end {
      cmd.common.vernum = true;
      return;
   }

  <init> "-"{1,2} "dumpversion" end {
      cmd.common.dumpversion = true;
      return;
   }

   <init> "api" end => api {
      cmd.kind = CmdKind::API;
      goto loop;
   }

   <*> * {
      throw OptionException(
         "The '" + std::string(*argv) + "' option does not exist"
      );
   }

   <api> "--backend" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The '--backend' option requires a value");
         }
      }

      cmd.api.backend = YYCURSOR;
      goto yyc_backend;
   }

   <api> ("-p" end) | ("--path" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The '--path' option requires a value");
         }
      }

      cmd.api.path = YYCURSOR;
      goto yyc_path;
   }

   <api> ("-o" end) | ("--output" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The '--output' option requires a value");
          }
      }

      cmd.api.output = YYCURSOR;
      goto yyc_output;
   }

   <api> "--options" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The '--options' option requires a value");
         }
      }

      cmd.api.options = YYCURSOR;
      goto yyc_options;
   }

   <api> ("-h" | "--help") end {
      cmd.api.help = true;
      goto loop;
   }

   <api> "--url" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The '--url' option requires a value");
         }
      }

      cmd.api.url = YYCURSOR;
      goto yyc_url;
   }

  <api> ("-q" | "--quiet") end {
      cmd.common.quiet = true;
      goto loop;
   }

   <backend> * {
      throw OptionException("Backend '" + std::string(*argv) + "' does not supported");
   }

   <backend> "ZendEngine3" end {
      goto loop;
   }

   <path> * {
      throw OptionException("Invalid path specification");
   }

   <path> [^\x00]+ end {
      goto loop;
   }

   <output> * {
      throw OptionException("Invalid output specification");
   }

   <output> [^\x00]+ end {
      goto loop;
   }

   <options> * {
      throw OptionException("Invalid options specification");
   }

   <options> [^\x00]+ end {
      goto loop;
   }

   <url> * {
      throw OptionException("Invalid url specification");
   }

   <url> [^\x00]+ end {
      goto loop;
   }
  */

  return;
}
}  // namespace commands
