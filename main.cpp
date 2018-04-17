
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
	std::cout << my::print_ip((long long)(8875824491850138409)) << std::endl;
	std::cout << my::print_ip((long long)(0xf0f1f2f3)) << std::endl;
	std::cout << my::print_ip(std::string("ip: 1.2.3.4")) << std::endl;
	std::cout << my::print_ip(std::vector<char>{-10, 20, -30, 40, -10, 20}) << std::endl;
	std::cout << my::print_ip(std::list<int>{2130706433, 85, 2130706433, 65, 2130706433, 45, 255}) << std::endl;
	// std::cout << my::print_ip(std::make_tuple(1024, 2048, 4096, 10)) << std::endl;

	return 0;
}

