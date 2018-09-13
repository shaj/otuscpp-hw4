/**
 * \file
 * Реализация функции печати условного ip адреса
 */


/**
 * \brief решение поставленной задачи
 *
 * \todo
 *  - реализовать печать tuple чисел
 */


#pragma once

#include "reminder.h"

// #pragma message(TODO "реализовать печать tuple чисел")

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <list>


namespace my
{

/**
 * Поиск соответствия типу из списка типов
 * \param T тип который ищем
 * \param Args список типов среди которых ищем
 */
template<typename T, typename ... Args>
struct is_one_of;

template<typename T>
struct is_one_of<T> : std::false_type {};

template<typename T, typename ... Args>
struct is_one_of<T, T, Args...> : std::true_type {};

template<typename T, typename U, typename ... Args>
struct is_one_of<T, U, Args...> : is_one_of<T, Args...> {};



/**
 * Печать условного ip адреса из целочисленного типа
 *
 * \param val число, которое нужно напечатать как условный ip адрес
 * \return строка std::string, содержащая представление числа val, как ip адреса
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type print_ip(const T &val)
{
	std::ostringstream s;
	if(sizeof(val) == 1)
	{
		auto pLow = reinterpret_cast<const unsigned char*>(&val);
		s << static_cast<unsigned int>(*pLow);
	}
	else
	{
#ifdef BIG_ENDIAN
		auto pLow = reinterpret_cast<const unsigned char*>(&val);
		auto pHigh = reinterpret_cast<const unsigned char*>(&val) + sizeof(val);

		std::reverse_copy(pLow+1, pHigh, std::ostream_iterator<unsigned int>(s, "."));
		s << static_cast<unsigned int>(*pLow);
#elif LITTLE_ENDIAN
		auto pLow = reinterpret_cast<const unsigned char*>(&val);
		auto pHigh = reinterpret_cast<const unsigned char*>(&val) + sizeof(val);

		std::copy(pLow, pHigh-1, std::ostream_iterator<unsigned int>(s, "."));
		s << static_cast<unsigned int>(*(pHigh-1));
#else
#error "No endianness macro defined"
#endif
	}

	return s.str();
}

/**
 * Печать условного ip адреса из строки
 *
 * \param val строка, содержащая представление условного ip адреса
 * \return строка, содержащая представление условного ip адреса
 */
template<typename T>
typename std::enable_if<is_one_of<T, std::string, const char*>::value, std::string>::type print_ip(const T &val)
{
	return static_cast<std::string>(val);
}

/**
 * Печать списка условных ip адресов
 * из std::vector и std::list
 *
 * \param val std::vector или std::list чисел, которые нужно напечатать как условный ip адрес
 * \return строка std::string, содержащая представление всех чисел из контейнера, как ip адреса
 *
 * \todo
 *  - убрать лишний std::endl в конце списка
 */
template<class T>
typename std::enable_if<is_one_of<T, std::vector<typename T::value_type>, std::list<typename T::value_type>>::value,
		std::string>::type print_ip(const T &val)
{
	std::ostringstream s;
	bool f = true;
	for(const auto &it: val)
	{
		if(f)
		{
			s << print_ip(it);
			f = false;
		}
		else
		{
			s << "." << print_ip(it);
		}
	}
	return s.str();
}	


/**
 * Variadic для печати списка условных ip адресов
 * из разных типов данных
 *
 * \param 
 * \return строка std::string, содержащая представление числа val, как ip адреса
 *
 * \todo
 *  - Добавить печать неизвестного типа
 */
template<class T, class... Targs>
std::string print_ip(const T &val, Targs... Fargs)
{
	std::ostringstream s;
	s << print_ip(val);
	s << std::endl;
	s << print_ip(Fargs...);
	return s.str();
}


}
