// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <string>

#include "cmd.hpp"
#include "optionexception.hpp"
#include "options.hpp"

/*!types:re2c*/
namespace commands {

Options::Options() noexcept : m_program("Zephir") {}

inline void Options::set_help_flag(Cmd &cmd) {
  switch (cmd.kind) {
    case CmdKind::API:
      cmd.api.help = true;
      break;
    case CmdKind::INIT:
      cmd.init.help = true;
      break;
    default:
      cmd.common.help = true;
  }
}

inline void Options::set_backend(Cmd &cmd, const char *backend) {
  switch (cmd.kind) {
    case CmdKind::API:
      cmd.api.backend = backend;
      break;
    case CmdKind::INIT:
      cmd.init.backend = backend;
      break;
    default:
      throw OptionException("Backend isn't allowed in this context.");
  }
}

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
   re2c:indent:top = 1;
   re2c:indent:string = "  ";
   re2c:define:YYGETCONDITION = "cond";
   re2c:define:YYGETCONDITION:naked = 1;
   re2c:define:YYSETCONDITION = "cond = @@;";
   re2c:define:YYSETCONDITION:naked = 1;

   end = "\x00";
   eq  = "=";
   value = [^\x00-][^\x00]*;

   <start> * {
      throw OptionException(
         "Command \"" + std::string(*argv) + "\" is not defined.");
   }

   <start> ("-h" | "--help") end {
      set_help_flag(cmd);
      return;
   }

   <start> ("-v" | "--version") end {
      cmd.common.version = true;
      return;
   }

   <start> "--vernum" end {
      cmd.common.vernum = true;
      return;
   }

  <start> "-"{1,2} "dumpversion" end {
      cmd.common.dumpversion = true;
      return;
   }

   <start> "--" value end {
      throw OptionException(
         "Option \"" + std::string(*argv) + "\" isn't allowed in this context.");
   }

   <start> "api" end => api { cmd.kind = CmdKind::API; goto loop; }
   <start> "init" end => init { cmd.kind = CmdKind::INIT; goto loop; }

   <*> * {
      throw OptionException(
         "The \"" + std::string(*argv) + "\" option does not exist."
      );
   }

   <api, init> "--backend" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--backend\" option requires a value.");
         }
      }

      set_backend(cmd, YYCURSOR);
      goto yyc_backend;
   }

   <api> ("-p" end) | ("--path" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--path\" option requires a value.");
         }
      }

      cmd.api.path = YYCURSOR;
      goto yyc_path;
   }

   <api> ("-o" end) | ("--output" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--output\" option requires a value.");
          }
      }

      cmd.api.output = YYCURSOR;
      goto yyc_output;
   }

   <api> "--options" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--options\" option requires a value.");
         }
      }

      cmd.api.options = YYCURSOR;
      goto yyc_options;
   }

   <api, init> ("-h" | "--help") end {
      set_help_flag(cmd);
      goto loop;
   }

   <api> "--url" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--url\" option requires a value.");
         }
      }

      cmd.api.url = YYCURSOR;
      goto yyc_url;
   }

  <api> ("-q" | "--quiet") end {
      cmd.common.quiet = true;
      goto loop;
   }

   <init> "--" end {
      // all remaining argv part is non-option
      // so it must be namespace name
      // zephir expects exactly one namespace name
      if (!(YYCURSOR = *++argv)) {
        throw OptionException("Not enough arguments (missing: \"namespace\").");
      }

      cmd.init.ns = YYCURSOR;
      goto yyc_namespace;
   }

   // TODO: Better namespace parsing
   <init> value end {
      cmd.init.ns = *argv;
      goto loop;
   }

   <namespace> * {
      throw OptionException("Namespace name \"" + std::string(*argv) + "\" does not supported.");
   }

   // TODO: Better namespace parsing
   <namespace> value end {
      goto loop;
   }

   <backend> * {
      throw OptionException("Backend \"" + std::string(*argv) + "\" does not supported.");
   }

   <backend> "ZendEngine3" end {
      goto loop;
   }

   <path> * {
      throw OptionException("Invalid path specification.");
   }

   <path> value end {
      goto loop;
   }

   <output> * {
      throw OptionException("Invalid output specification");
   }

   <output> value end {
      goto loop;
   }

   <options> * {
      throw OptionException("Invalid options specification.");
   }

   // TODO: Better options pattern
   <options> value end {
      goto loop;
   }

   <url> * {
      throw OptionException("Invalid url specification.");
   }

   // TODO: Better URL pattern
   <url> value end {
      goto loop;
   }
  */

  return;
}
}  // namespace commands
