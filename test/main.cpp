#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

/*
 * This entrypoint should be used to provide a custom
 * code that executes before and/ or after Catch
 *
 * See: https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top
 */
int main(int argc, char *argv[]) {
    // global setup...

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}
