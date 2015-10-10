#include "telnetpp/options/suppress_ga/client.hpp"
#include "telnetpp/options/suppress_ga.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class suppress_ga_client_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(suppress_ga_client_test);
        CPPUNIT_TEST(option_is_suppress_ga);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void option_is_suppress_ga();
    void valid_subnegotiation_signals_window_size_change();
};

CPPUNIT_TEST_SUITE_REGISTRATION(suppress_ga_client_test);

void suppress_ga_client_test::option_is_suppress_ga()
{
    telnetpp::options::suppress_ga::client client;
    CPPUNIT_ASSERT_EQUAL(telnetpp::options::suppress_ga::option, client.option());
}
