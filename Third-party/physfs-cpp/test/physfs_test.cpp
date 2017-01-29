#include <physfs.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestRunner.h>

class PhysfsTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(PhysfsTest);
    CPPUNIT_TEST(testExceptionThrownWhenFileNotFound);
    CPPUNIT_TEST_SUITE_END();
public:
    void testExceptionThrownWhenFileNotFound() {
        try {
            PhysFS::ifstream file("the_princess_is_in_another_castle");
            CPPUNIT_ASSERT(false); // should not get here
        } catch (std::invalid_argument e) {
        }
    }
};


int main(int argc, char** argv) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(PhysfsTest::suite());
    return runner.run() ? 0 : 1;
}
