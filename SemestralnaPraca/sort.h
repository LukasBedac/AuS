#pragma once
#include "libds/adt/sorts.h"
#include "libds/adt/list.h"
#include "uzemna_jednotka.h"
#include <locale>
class Sort
{
public:
	Sort() : slovak("Slovak_Slovakia.1250") {};

	template<typename T>
	void utried(ds::amt::ImplicitSequence<T>& is, int index);

private:
	std::locale slovak;
	
	std::function<bool(UzemnaJednotka* const&, UzemnaJednotka* const&)> porovnajAbecedne = [&](UzemnaJednotka* const& a, UzemnaJednotka* const& b)
		{
			return slovak(a->getNazov(), b->getNazov());
		};
	std::function<bool(UzemnaJednotka* const&, UzemnaJednotka* const&)> porovnajPocetSpoluhlasok = [&](UzemnaJednotka* const& a, UzemnaJednotka* const& b)
		{
			return a->pocetSpoluhlasok() < b->pocetSpoluhlasok();
		};

};

template<typename T>
void Sort::utried(ds::amt::ImplicitSequence<T>& is, int komparatorIndex) 
{
	ds::adt::QuickSort<T> quickSort;
	std::function<bool(T const&, T const&)> komparator;
	if (komparatorIndex == 2)
	{
		komparator = porovnajPocetSpoluhlasok;
	}
	else
	{
		komparator = porovnajAbecedne;
	}

	quickSort.sort(is, komparator);
}