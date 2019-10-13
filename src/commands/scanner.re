#include <iostream>

#include "commands.hpp"

/*!types:re2c*/
namespace commands {
    #define YYGETCONDITION()  cond
    #define YYSETCONDITION(c) cond = c

    bool parseopt(char **argv, Cmd &cmd)
    {
        char *YYCURSOR, *YYMARKER;
        const char **backend, **path, **output, **options, **url;
        int cond = 0;

        loop:
        if (!(YYCURSOR = *++argv)) return true;

        /*!re2c
         re2c:define:YYCTYPE = 'unsigned char';
         re2c:yyfill:enable = 0;
         re2c:yych:conversion = 1;

         eq  = "=";
         end = "\x00";

         <init> * {
            std::cerr << "Command \"" << *argv << "\" is not defined" << std::endl;
            return false;
         }

         <init> "api" end => api {
            cmd.kind = API;
            goto loop;
         }

         <*> * {
            std::cerr << "The \"" << *argv << "\" option does not exist" << std::endl;
            return false;
         }

         <api> "--backend" end {
            if (!(YYCURSOR = *++argv)) {
                std::cerr << "The \"--backend\" option requires a value" << std::endl;
                return false;
            }

            backend = &cmd.api.backend;
            goto yyc_backend;
         }

         <api> ("-p" | "--path") end {
            if (!(YYCURSOR = *++argv)) {
                std::cerr << "The \"--path\" option requires a value" << std::endl;
                return false;
            }

            path = &cmd.api.path;
            goto yyc_path;
         }

         <api> ("-o" | "--output") end {
            if (!(YYCURSOR = *++argv)) {
                std::cerr << "The \"" << *argv << "\" option requires a value" << std::endl;
                //std::cerr << "The \"--output\" option requires a value" << std::endl;
                return false;
            }

            output = &cmd.api.output;
            goto yyc_output;
         }

         <api> "--options" end {
            if (!(YYCURSOR = *++argv)) {
                std::cerr << "The \"--options\" option requires a value" << std::endl;
                return false;
            }

            options = &cmd.api.options;
            goto yyc_options;
         }

         <api> "--url" end {
            if (!(YYCURSOR = *++argv)) {
                std::cerr << "The \"--url\" option requires a value" << std::endl;
                return false;
            }

            url = &cmd.api.url;
            goto yyc_url;
         }

         <backend> * {
            std::cerr << "Backend \"" << *argv << "\" does not supported" << std::endl;
            return false;
         }

         <backend> "ZendEngine3" end {
            *backend = *argv;
            goto loop;
         }

         <path> * {
            std::cerr << "Invalid path specification" << std::endl;
            return false;
         }

         <path> [^\x00]+ end {
            *path = *argv;
            goto loop;
         }

         <output> * {
            std::cerr << "Invalid output specification" << std::endl;
            return false;
         }

         <output> [^\x00]+ end {
            *output = *argv;
            goto loop;
         }

         <options> * {
            std::cerr << "Invalid options specification" << std::endl;
            return false;
         }

         <options> [^\x00]+ end {
            *options = *argv;
            goto loop;
         }

         <url> * {
            std::cerr << "Invalid url specification" << std::endl;
            return false;
         }

         <url> [^\x00]+ end {
            *url = *argv;
            goto loop;
         }
        */

        return true;
    }
}
