#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/commands/cmd.hpp"
#include "argv.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);

    CPPUNIT_TEST(Compiler_can_be_invoked_without_arguments);
    CPPUNIT_TEST(command_is_API);
    CPPUNIT_TEST_SUITE_END();

public:
    void Compiler_can_be_invoked_without_arguments();
    void command_is_API();

};

CPPUNIT_TEST_SUITE_REGISTRATION( CommandsTest );


void CommandsTest::Compiler_can_be_invoked_without_arguments()
{
    Argv argv({
            "zephir",
            ""
        });

    char **args = argv.argv();

    commands::Cmd cmd;
    std::memset(&cmd, 0, sizeof(cmd));

    auto result = commands::parseopt(args, cmd);

    CPPUNIT_ASSERT(cmd.kind == commands::NONE);
    CPPUNIT_ASSERT(cmd.quiet == false);
    CPPUNIT_ASSERT(cmd.common_help == false);
    CPPUNIT_ASSERT(cmd.version == false);
    CPPUNIT_ASSERT(cmd.vernum == false);
    CPPUNIT_ASSERT(cmd.dumpversion == false);
}

void CommandsTest::command_is_API()
{
    Argv argv({
            "zephir",
            "api",
            ""
        });

    char **args = argv.argv();

    commands::Cmd cmd;
    std::memset(&cmd, 0, sizeof(cmd));

    auto result = commands::parseopt(args, cmd);

    CPPUNIT_ASSERT(cmd.kind == commands::API);
    CPPUNIT_ASSERT(cmd.quiet == false);
    CPPUNIT_ASSERT(cmd.common_help == false);
    CPPUNIT_ASSERT(cmd.version == false);
    CPPUNIT_ASSERT(cmd.vernum == false);
    CPPUNIT_ASSERT(cmd.dumpversion == false);
}
