
/**
	\file
	Модульные тесты
*/	

#define BOOST_LOG_DYN_LINK 1

#define BOOST_TEST_MODULE test_printer

#include <boost/test/included/unit_test.hpp>

#include "printer.h"


/**
 * Основной набор основных тестов 
 */
BOOST_AUTO_TEST_SUITE(test_print_ip_suite)

BOOST_AUTO_TEST_CASE(test_print_ip) 
{
	BOOST_CHECK(my::print_ip(char(-1)) == "255");
	BOOST_CHECK(my::print_ip(short(0)) == "0.0");
	BOOST_CHECK(my::print_ip(int(2130706433)) == "127.0.0.1");
	BOOST_CHECK(my::print_ip((long long)(8875824491850138409)) == "123.45.67.89.101.112.131.41");
	BOOST_CHECK(my::print_ip(std::string("ip: 1.2.3.4")) == "ip: 1.2.3.4");
	BOOST_CHECK(my::print_ip(std::vector<int>{10, 20, 30}) == "0.0.0.10.0.0.0.20.0.0.0.30");
	BOOST_CHECK(my::print_ip(std::list<int>{2130706433, 85, 2130706433}) == "127.0.0.1.0.0.0.85.127.0.0.1");
	// BOOST_CHECK(my::print_ip(std::make_tuple(1024, 2048, 4096, 10)) == "1024.2048.4096.10");

	std::list<std::vector<short>> v1 = 
	{{1, 2},
	 {-1, -2},
	 {1024, 2048}};
	BOOST_CHECK(my::print_ip(v1) == "0.1.0.2.255.255.255.254.4.0.8.0");

	std::vector<std::list<short>> v2 = 
	{{1, 2},
	 {-1, -2},
	 {1024, 2048}};
	BOOST_CHECK(my::print_ip(v2) == "0.1.0.2.255.255.255.254.4.0.8.0");

	std::vector<std::string> v3 = {"127", "0", "0", "1"};
	BOOST_CHECK(my::print_ip(v3) == "127.0.0.1");

	std::list<std::string> v4 = {"127", "0", "0", "1"};
	BOOST_CHECK(my::print_ip(v4) == "127.0.0.1");

}

BOOST_AUTO_TEST_SUITE_END()
