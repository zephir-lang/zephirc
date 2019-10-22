#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstring>
#include "../src/commands/cmd.hpp"
#include "argv.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);

    CPPUNIT_TEST(Compiler_can_be_invoked_without_arguments);
    CPPUNIT_TEST(Invoke_api_command);
    CPPUNIT_TEST(Invoked_with_help_argument);
    CPPUNIT_TEST(Invoked_with_general_arguments);
    CPPUNIT_TEST_SUITE_END();

public:
    void Compiler_can_be_invoked_without_arguments();
    void Invoke_api_command();
    void Invoked_with_help_argument();
    void Invoked_with_general_arguments();

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
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [url]", !testCmd.api.url);
    CPPUNIT_ASSERT_MESSAGE("Only help option was changed [help]", testCmd.api.help);

    CPPUNIT_ASSERT_MESSAGE("Global option [quiet] in default state", !testCmd.quiet);
    CPPUNIT_ASSERT_MESSAGE("Global option [common_help] in default state", !testCmd.common_help);
    CPPUNIT_ASSERT_MESSAGE("Global option [version] in default state", !testCmd.version);
    CPPUNIT_ASSERT_MESSAGE("Global option [vernum] in default state", !testCmd.vernum);
    CPPUNIT_ASSERT_MESSAGE("Global option [dumpversion] in default state", !testCmd.dumpversion);
}

void CommandsTest::Invoked_with_general_arguments()
{
    Argv argv({
            "zephir",
            "api",
            "--url=http://test.com",
            "--backend=ZendEngine3",
            "-p", "theme",
            "-o", "out",
            "--options=opts",
            ""
        });

    commands::Cmd cmd;
    auto testCmd = this->runTest(cmd, argv);

    CPPUNIT_ASSERT_MESSAGE("command is API", testCmd.kind == commands::API);

    CPPUNIT_ASSERT_MESSAGE("general options were changed [backend]", (std::string)testCmd.api.backend == "ZendEngine3");
    CPPUNIT_ASSERT_MESSAGE("general options were changed [path]", (std::string)testCmd.api.path == "theme");
    CPPUNIT_ASSERT_MESSAGE("general options were changed [output]", (std::string)testCmd.api.output == "out");
    CPPUNIT_ASSERT_MESSAGE("general options were changed [options]", (std::string)testCmd.api.options == "opts");
    CPPUNIT_ASSERT_MESSAGE("general options were changed [url]", (std::string)testCmd.api.url == "http://test.com");
    CPPUNIT_ASSERT_MESSAGE("general options were changed [help]", !testCmd.api.help);
}

commands::Cmd CommandsTest::runTest(commands::Cmd &cmd, Argv &argv)
{
    char **args = argv.argv();

    std::memset(&cmd, 0, sizeof(cmd));

    auto result = commands::parseopt(args, cmd);

    return cmd;
}
