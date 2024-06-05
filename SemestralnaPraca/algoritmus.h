#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include "uzemna_jednotka.h"
template<typename T>
class Algoritmus
{
private:

public:
	template<typename It, typename P>
	std::vector<T> filtrujData(It begin, It end, P predicate) {
		std::vector<T> data_;
		while (begin != end)
		{
			if (predicate(*begin))
			{				
				data_.push_back(*begin);
			}
			++begin;
		}
		return data_;
	};

	/*template<typename It>
	std::vector<T> dataPodlaTypu(It begin, It end, std::function<bool(T)> predicate) {
		std::vector<T> data_;
		while (begin != end)
		{
			if (predicate(*begin))
			{
				data_.push_back(*begin);
			}
			++begin;
		}
		return data_;
	}*/
};



