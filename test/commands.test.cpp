#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/commands/cmd.hpp"
#include "argv.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);

    CPPUNIT_TEST(CommandParse);

    CPPUNIT_TEST_SUITE_END();

public:
    void testExample();
    void CommandParse();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CommandsTest );


void CommandsTest::CommandParse()
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
}
