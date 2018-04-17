/**
 * Реализация функции печати условного ip адреса
 */


#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>


namespace my
{

template<class T>
struct type_is
{
	using type = T;
};

template<typename T, T v>
struct integral_constant
{
	static constexpr T value = v;
	using type = integral_constant;
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;


template<bool B, class T>
struct enable_if : type_is<T> {};

template<class T>
struct enable_if<false, T> {};


template<typename T, typename ... Args>
struct is_one_of;

template<typename T>
struct is_one_of<T> : false_type {};

template<typename T, typename ... Args>
struct is_one_of<T, T, Args...> : true_type {};

template<typename T, typename U, typename ... Args>
struct is_one_of<T, U, Args...> : is_one_of<T, Args...> {};



template<typename T>
typename enable_if<std::is_integral<T>::value, std::string>::type print_ip(const T &val)
{
	std::ostringstream s;
	auto pLow = reinterpret_cast<const unsigned char*>(&val);
	auto pHigh = reinterpret_cast<const unsigned char*>(&val) + sizeof(val);

	if(sizeof(val) == 1)
	{
		s << static_cast<unsigned int>(*pLow);
	}
	else
	{
		std::reverse_copy(pLow+1, pHigh, std::ostream_iterator<unsigned int>(s, "."));
		s << static_cast<unsigned int>(*pLow);
	}
	return s.str();
}

template<typename T>
typename enable_if<is_one_of<T, std::string>::value, std::string>::type print_ip(const T &val)
{
	return static_cast<std::string>(val);
}

template<class T>
typename enable_if<is_one_of<T, std::vector<typename T::value_type>, std::list<typename T::value_type>>::value,
		std::string>::type print_ip(const T &val)
{
	std::ostringstream s;
	for(const auto &it: val)
	{
		s << print_ip(it) << std::endl;
	}
	return s.str();
}		

}
