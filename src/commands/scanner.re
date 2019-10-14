#include <iostream>

#include "commands.hpp"

/*!types:re2c*/
namespace commands {
    bool parseopt(char **argv, Cmd &cmd)
    {
        char *YYCURSOR, *YYMARKER;
        int cond = 0;

        loop:
        if (!(YYCURSOR = *++argv)) return true;

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
            std::cerr << "Command \"" << *argv << "\" is not defined" << std::endl;
            return false;
         }

         <init> "api" end => api {
            cmd.kind = API;
            goto loop;
         }

         <*> * {
            std::cerr << "The \"" << *argv << "\" option does not exist. ";
            std::cerr << "Did you missed \"=\" sign or forget escape option's value?" << std::endl;
            return false;
         }

         <api> "--backend" (eq | end) {
            if (YYCURSOR[-1] == 0) {
                if (!(YYCURSOR = *++argv)) {
                    std::cerr << "The \"--backend\" option requires a value" << std::endl;
                    return false;
                }
            }

            cmd.api.backend = YYCURSOR;
            goto yyc_backend;
         }

         <api> ("-p" end) | ("--path" (eq | end)) {
            if (YYCURSOR[-1] == 0) {
                if (!(YYCURSOR = *++argv)) {
                    std::cerr << "The \"--path\" option requires a value" << std::endl;
                    return false;
                }
            }

            cmd.api.path = YYCURSOR;
            goto yyc_path;
         }

         <api> ("-o" end) | ("--output" (eq | end)) {
            if (YYCURSOR[-1] == 0) {
                if (!(YYCURSOR = *++argv)) {
                    std::cerr << "The \"--output\" option requires a value" << std::endl;
                    return false;
                }
            }

            cmd.api.output = YYCURSOR;
            goto yyc_output;
         }

         <api> "--options" (eq | end) {
            if (YYCURSOR[-1] == 0) {
                if (!(YYCURSOR = *++argv)) {
                    std::cerr << "The \"--options\" option requires a value" << std::endl;
                    return false;
                }
            }

            cmd.api.options = YYCURSOR;
            goto yyc_options;
         }

         <api> "--url" (eq | end) {
            if (YYCURSOR[-1] == 0) {
                if (!(YYCURSOR = *++argv)) {
                    std::cerr << "The \"--url\" option requires a value" << std::endl;
                    return false;
                }
            }

            cmd.api.url = YYCURSOR;
            goto yyc_url;
         }

         <backend> * {
            std::cerr << "Backend \"" << *argv << "\" does not supported" << std::endl;
            return false;
         }

         <backend> "ZendEngine3" end {
            goto loop;
         }

         <path> * {
            std::cerr << "Invalid path specification" << std::endl;
            return false;
         }

         <path> [^\x00]+ end {
            goto loop;
         }

         <output> * {
            std::cerr << "Invalid output specification" << std::endl;
            return false;
         }

         <output> [^\x00]+ end {
            goto loop;
         }

         <options> * {
            std::cerr << "Invalid options specification" << std::endl;
            return false;
         }

         <options> [^\x00]+ end {
            goto loop;
         }

         <url> * {
            std::cerr << "Invalid url specification" << std::endl;
            return false;
         }

         <url> [^\x00]+ end {
            goto loop;
         }
        */

        return true;
    }
}
