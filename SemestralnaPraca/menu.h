#pragma once
#include "algoritmus.h"
#include "nacitac_suboru.h"
#include "sort.h"
#include <iostream>
class Menu
{
private:
	int vyberJednotky_;
	int vyberMenu_;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualnyVrchol;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulka;
	std::string filtracnyPrvok_;
	int typFiltracie_;
	bool spravneInfo_ = true;
	Algoritmus<UzemnaJednotka*> algoritmus;
	Nacitac_suboru* nacitac;
	Sort* sort;
public:
	Menu() { nacitac = new Nacitac_suboru(); };
	~Menu();
	void startMenu();
	bool rozsahMenuHandling();
	void vypisanie(ds::amt::ImplicitSequence<UzemnaJednotka*>* &vystupData);
};

