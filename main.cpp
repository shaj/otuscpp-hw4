
/**
 * Программа печати условного ip - адреса
 * 


*/

#include <iostream>
#include <vector>
#include <list>
#include <tuple>

#include "printer.h"




int main (int argc, char *argv[])
{
	std::cout << my::print_ip(char(-1)) << std::endl;
	std::cout << my::print_ip(short(0)) << std::endl;
	std::cout << my::print_ip(int(2130706433)) << std::endl;
	std::cout << my::print_ip(long(8875824491850138409)) << std::endl;
	std::cout << my::print_ip(std::string("ip: 1.2.3.4")) << std::endl;
	std::cout << my::print_ip(std::vector<int>{10, 20, 30, 40, 50, 60}) << std::endl;
	std::cout << my::print_ip(std::list<int>{95, 85, 75, 65, 55, 45, 1024}) << std::endl;
	std::cout << my::print_ip(std::make_tuple(1024, 2048, 4096, 10)) << std::endl;

	return 0;
}

