#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/commands/cmd.hpp"
#include "argv.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);

    CPPUNIT_TEST(Compiler_can_be_invoked_without_arguments);
    CPPUNIT_TEST(Invoke_api_command);
    CPPUNIT_TEST_SUITE_END();

public:
    void Compiler_can_be_invoked_without_arguments();
    void Invoke_api_command();

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
    CPPUNIT_ASSERT_MESSAGE("API option [quiet] in default state", testCmd.quiet == false);
    CPPUNIT_ASSERT_MESSAGE("API option [common_help] in default state", testCmd.common_help == false);
    CPPUNIT_ASSERT_MESSAGE("API option [version] in default state", testCmd.version == false);
    CPPUNIT_ASSERT_MESSAGE("API option [vernum] in default state", testCmd.vernum == false);
    CPPUNIT_ASSERT_MESSAGE("API option [dumpversion] in default state", testCmd.dumpversion == false);
}

commands::Cmd CommandsTest::runTest(commands::Cmd &cmd, Argv &argv)
{
    char **args = argv.argv();

    std::memset(&cmd, 0, sizeof(cmd));

    auto result = commands::parseopt(args, cmd);

    return cmd;
}
