#ifndef ZEPHIR_COMMANDS_CMD_HPP
#define ZEPHIR_COMMANDS_CMD_HPP

namespace commands {

    enum CmdKind {
        NONE = 0,
        API,
        BUILD,
        CLEAN,
        FULLCLEAN,
        GENERATE,
        HELP,
        INIT,
        INSTALL,
        STUBS
    };

    class Cmd {
    public:
        // what kind of command
        CmdKind kind;

        // command-specific options
        union {
            // api-specific options
            struct {
                const char *backend;
                const char *path;
                const char *output;
                const char *options;
                const char *url;
                bool help;
            } api;

            // build-specific options
            struct {
                // ...
            } build;

            // clean-specific options
            struct {
                // ...
            } clean;

            // fullclean-specific options
            struct {
                // ...
            } fullclean;

            // generate-specific options
            struct {
                // ...
            } generate;

            // help-specific options
            struct {
                // ...
            } help;

            // init-specific options
            struct {
                // ...
            } init;

            // install-specific options
            struct {
                // ...
            } install;

            // stubs-specific options
            struct {
                // ...
            } stubs;
        };

        // common options
        struct {
            bool quiet;
            bool common_help;
            bool version;
            bool vernum;
            bool dumpversion;
        };
    };

    bool parseopt(char **argv, Cmd &cmd);
}

#endif // ZEPHIR_COMMANDS_CMD_HPP
