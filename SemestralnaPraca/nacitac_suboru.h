#pragma once
#include "uzemna_jednotka.h"
#include "obec.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "libds/adt/abstract_data_type.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/mm/compact_memory_manager.h"
#include "libds/adt/table.h"
#include "libds/heap_monitor.h"
#include "libds/adt/list.h"

class Nacitac_suboru
{
private:
	//cast 1
	std::vector<UzemnaJednotka*> SOORPs_;
	std::vector<UzemnaJednotka*> obce_;
	std::vector<UzemnaJednotka*> kraje_;
	std::string kraj_;
	//cast 2 a 4
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	int poradieKrajov = 0;
	int poradieSOORP = 0;
	int poradieObci = 0;
	UzemnaJednotka* koreò;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* poslednyPridanyKraj;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* poslednyPridanySOORP;
	//cast 3
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulkaKrajov;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulkaSOORP;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulkaObci;
public:
	Nacitac_suboru();
	~Nacitac_suboru();
	void nacitajSubor(std::string nazovSuboru);
	void rozdelData(std::vector<std::string> &data);
	std::vector<UzemnaJednotka*> &getSoorp();
	std::vector<UzemnaJednotka*> &getObce();
	std::vector<UzemnaJednotka*> &getKraje();
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* &getTabulka(int typ);
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* &getHierarchia();
	void pridajDoTabulky(UzemnaJednotka* jednotka, ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulka);
};

