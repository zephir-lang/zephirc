// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <string>
#include <cstring>

#include "parse_result.hpp"
#include "optionexception.hpp"
#include "options.hpp"

/*!types:re2c*/
namespace commands {

Options::Options() noexcept : program("Zephir") {}

inline void Options::set_help_flag(ParseResult &pr) {
  switch (pr.get_kind()) {
    case CmdKind::API:
      pr.api.help = true;
      break;
    case CmdKind::INIT:
      pr.init.help = true;
      break;
    case CmdKind::NONE:
    default:
      pr.common.help = true;
  }
}

inline void Options::set_backend(ParseResult &pr, const char *backend) {
  if (pr.get_kind() == CmdKind::API) {
    pr.api.backend = backend;
    return;
  } else if (pr.get_kind() == CmdKind::INIT) {
    pr.init.backend = backend;
    return;
  }
}

ParseResult Options::parse(char **argv) {
  char *YYCURSOR, *YYMARKER;
  int cond = 0;

  ParseResult pr;
  std::memset(&pr, 0, sizeof(ParseResult));

loop:
  YYCURSOR = *++argv;
  if (!YYCURSOR || *YYCURSOR == '\0') return pr;

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
   ns = [_a-zA-Z][_a-zA-Z0-9]*;

   <start> * {
      throw OptionException(
         "Command \"" + std::string(*argv) + "\" is not defined.");
   }

   <start> ("-h" | "--help") end {
      set_help_flag(pr);
      return pr;
   }

   <start> ("-v" | "--version") end {
      pr.common.version = true;
      return pr;
   }

   <start> "--vernum" end {
      pr.common.vernum = true;
      return pr;
   }

  <start> "-"{1,2} "dumpversion" end {
      pr.common.dumpversion = true;
      return pr;
   }

   <start> "--" value end {
      throw OptionException(
         "Option \"" + std::string(*argv) + "\" isn't allowed in this context.");
   }

   <start> "api" end => api { pr.set_kind(CmdKind::API); goto loop; }
   <start> "init" end => init { pr.set_kind(CmdKind::INIT); goto loop; }

   <*> * {
      if (pr.get_kind() == CmdKind::INIT) {
         throw OptionException(
            "Invalid namespace format: \"" + std::string(*argv) + "\"."
         );
      }
      throw OptionException(
         "The \"" + std::string(*argv) + "\" option does not exist."
      );
   }

   <init> "--" end => namespace {
      // all remaining argv part is non-option
      // so it must be namespace name
      // zephir expects exactly one namespace name
      goto loop;
   }

   <api, init> "--backend" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--backend\" option requires a value.");
         }
      }

      set_backend(pr, YYCURSOR);
      goto yyc_backend;
   }

   <api> ("-p" end) | ("--path" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--path\" option requires a value.");
         }
      }

      pr.api.path = YYCURSOR;
      goto yyc_path;
   }

   <api> ("-o" end) | ("--output" (eq | end)) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--output\" option requires a value.");
          }
      }

      pr.api.output = YYCURSOR;
      goto yyc_output;
   }

   <api> "--options" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--options\" option requires a value.");
         }
      }

      pr.api.options = YYCURSOR;
      goto yyc_options;
   }

   <api, init> ("-h" | "--help") end {
      set_help_flag(pr);
      goto loop;
   }

   <api> "--url" (eq | end) {
      if (YYCURSOR[-1] == 0) {
         if (!(YYCURSOR = *++argv)) {
            throw OptionException("The \"--url\" option requires a value.");
         }
      }

      pr.api.url = YYCURSOR;
      goto yyc_url;
   }

  <api> ("-q" | "--quiet") end {
      pr.common.quiet = true;
      goto loop;
   }

   <namespace> * {
      throw OptionException(
         "Invalid namespace format: \"" + std::string(*argv) + "\"."
      );
   }

   <init, namespace> ns end {
      if (pr.init.ns) {
         throw OptionException(
            "Invalid namespace format: \"" +
            std::string(pr.init.ns) +
            " " +
            std::string(*argv) +
            "\"."
         );
      }

      pr.init.ns = *argv;
      goto loop;
   }

   <backend> * {
      throw OptionException("Backend \"" + std::string(*argv) + "\" does not supported.");
   }

   <backend> value end {
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

  return pr;
}
}  // namespace commands
