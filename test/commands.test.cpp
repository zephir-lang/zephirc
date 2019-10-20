#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/commands/cmd.hpp"

class CommandsTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(CommandsTest);
        CPPUNIT_TEST(testExample);

    CPPUNIT_TEST_SUITE_END();

    public:
        void testExample();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CommandsTest );


void CommandsTest::testExample()
{
  CPPUNIT_ASSERT( 1 == 1 );
}
