#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/commands/cmd.hpp"
#include "argv.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);

    CPPUNIT_TEST(Compiler_can_be_invoked_without_arguments);
    CPPUNIT_TEST(Invoke_api_command);
    CPPUNIT_TEST(Invoked_with_help_argument);
    CPPUNIT_TEST_SUITE_END();

public:
    void Compiler_can_be_invoked_without_arguments();
    void Invoke_api_command();
    void Invoked_with_help_argument();

private:
    commands::Cmd runTest(commands::Cmd &cmd, Argv &argv);
};

CPPUNIT_TEST_SUITE_REGISTRATION( CommandsTest );


// ***************************************************************
void CommandsTest::Compiler_can_be_invoked_without_arguments()
{
    Argv argv({
            "zephir",
            ""
        });

    commands::Cmd cmd;
    auto testCmd = this->runTest(cmd, argv);

    CPPUNIT_ASSERT_MESSAGE("command is NONE", testCmd.kind == commands::NONE);
    CPPUNIT_ASSERT_MESSAGE("global option [quiet] in default state", testCmd.quiet == false);
    CPPUNIT_ASSERT_MESSAGE("global option [common_help] in default state", testCmd.common_help == false);
    CPPUNIT_ASSERT_MESSAGE("global option [version] in default state", testCmd.version == false);
    CPPUNIT_ASSERT_MESSAGE("global option [vernum] in default state", testCmd.vernum == false);
    CPPUNIT_ASSERT_MESSAGE("global option [dumpversion] in default state", testCmd.dumpversion == false);
}

void CommandsTest::Invoke_api_command()
{
    Argv argv({
            "zephir",
            "api",
            ""
        });

    commands::Cmd cmd;
    auto testCmd = this->runTest(cmd, argv);

    CPPUNIT_ASSERT_MESSAGE("command is API", testCmd.kind == commands::API);

    CPPUNIT_ASSERT_MESSAGE("API option [backend] in default state", !testCmd.api.backend);
    CPPUNIT_ASSERT_MESSAGE("API option [path] in default state", !testCmd.api.path);
    CPPUNIT_ASSERT_MESSAGE("API option [output] in default state", !testCmd.api.output);
    CPPUNIT_ASSERT_MESSAGE("API option [options] in default state", !testCmd.api.options);
    CPPUNIT_ASSERT_MESSAGE("API option [options] in default state", !testCmd.api.options);
    CPPUNIT_ASSERT_MESSAGE("API option [url] in default state", !testCmd.api.url);
    CPPUNIT_ASSERT_MESSAGE("API option [help] in default state", !testCmd.api.help);

    CPPUNIT_ASSERT_MESSAGE("Global option [quiet] in default state", testCmd.quiet == false);
    CPPUNIT_ASSERT_MESSAGE("Global option [common_help] in default state", testCmd.common_help == false);
    CPPUNIT_ASSERT_MESSAGE("Global option [version] in default state", testCmd.version == false);
    CPPUNIT_ASSERT_MESSAGE("Global option [vernum] in default state", testCmd.vernum == false);
    CPPUNIT_ASSERT_MESSAGE("Global option [dumpversion] in default state", testCmd.dumpversion == false);
}

void CommandsTest::Invoked_with_help_argument()
{
    Argv argv({
            "zephir",
            "api",
            "--help",
            ""
        });

    commands::Cmd cmd;
    auto testCmd = this->runTest(cmd, argv);

    CPPUNIT_ASSERT_MESSAGE("command is API", testCmd.kind == commands::API);

    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [backend]", !testCmd.api.backend);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [path]", !testCmd.api.path);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [output]", !testCmd.api.output);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [options]", !testCmd.api.options);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [options]", !testCmd.api.options);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [url]", !testCmd.api.url);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [help]", testCmd.api.help);

    CPPUNIT_ASSERT_MESSAGE("Global option [quiet] in default state", !testCmd.quiet);
    CPPUNIT_ASSERT_MESSAGE("Global option [common_help] in default state", !testCmd.common_help);
    CPPUNIT_ASSERT_MESSAGE("Global option [version] in default state", !testCmd.version);
    CPPUNIT_ASSERT_MESSAGE("Global option [vernum] in default state", !testCmd.vernum);
    CPPUNIT_ASSERT_MESSAGE("Global option [dumpversion] in default state", !testCmd.dumpversion);
}

commands::Cmd CommandsTest::runTest(commands::Cmd &cmd, Argv &argv)
{
    char **args = argv.argv();

    std::memset(&cmd, 0, sizeof(cmd));

    auto result = commands::parseopt(args, cmd);

    return cmd;
}
