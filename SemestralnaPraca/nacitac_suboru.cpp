#include "nacitac_suboru.h"
#include <thread>
#include <chrono>

Nacitac_suboru::Nacitac_suboru()
{
	hierarchia = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>();
	poslednyPridanyKraj = nullptr;
	poslednyPridanySOORP = nullptr;
	koreò = new UzemnaJednotka("Èeská republika", "0", "koreò");

	auto hashFunkcia = [](std::string const& nazov) 
	{
		size_t ascii = 0;
		for (const char ch : nazov) 
		{
			ascii += ch;
		}
		return ascii;
	};

	tabulkaKrajov = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>(hashFunkcia, 13);
	tabulkaSOORP = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>(hashFunkcia, 53);
	tabulkaObci = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>(hashFunkcia, 3041);
}

Nacitac_suboru::~Nacitac_suboru()
{	
	for (UzemnaJednotka* &item : obce_)
	{
		delete item;
		item = nullptr;
	}
	for (UzemnaJednotka* &item : SOORPs_)
	{
		delete item;
		item = nullptr;
	}
	for (UzemnaJednotka* &item : kraje_)
	{
		delete item;
		item = nullptr;
	}
	for (auto item : *(this->tabulkaKrajov))
	{
		delete item.data_;
	}
	for (auto item : *(this->tabulkaSOORP))
	{
		delete item.data_;
	}
	for (auto item : *(this->tabulkaObci))
	{
		delete item.data_;
	}
	delete tabulkaKrajov;
	delete tabulkaSOORP;
	delete tabulkaObci;
	delete hierarchia;
	hierarchia = nullptr;
	delete koreò;
	koreò = nullptr;
	
}

void Nacitac_suboru::nacitajSubor(std::string nazovSuboru)
{
	std::ifstream subor(nazovSuboru);	
	hierarchia->emplaceRoot().data_ = koreò;
	if (!subor.is_open())
	{
		std::cerr << "Chyba pri otváraní súboru" << std::endl;
	}
	std::string riadok;
	while (std::getline(subor, riadok))
	{
		//std::cout << riadok << std::endl;
		//std::this_thread::sleep_for(std::chrono::seconds(3)); //Test vypisu

		std::vector<std::string> rozdelenyRiadok;
		std::string udaj;
		while (!riadok.empty())
		{			
			udaj = riadok.substr(0, riadok.find(';'));
			if (udaj.empty())
			{
				riadok.erase(0, 1);
				continue;
				
			}
			riadok.erase(0, riadok.find_first_of(';'));
			rozdelenyRiadok.push_back(udaj);
			udaj = "";
		}
		this->rozdelData(rozdelenyRiadok);
		rozdelenyRiadok.clear();
	}
	subor.close();
	std::cout << "Poèet naèítaných krajov:" << this->kraje_.size() << "\n";
	std::cout << "Poèet naèítaných SOORP:" << this->SOORPs_.size() << "\n";
	std::cout << "Poèet naèítaných obcí:" << this->obce_.size() << "\n";
}

void Nacitac_suboru::rozdelData(std::vector<std::string> &data)
{	
	std::string kanalizacia;
	std::string vodovod;
	std::string plyn;

	//Ak je 1 prvok, je to kraj
	if (data.size() == 1)
	{
		this->kraj_ = data[0];
		UzemnaJednotka* tmpKraj = new UzemnaJednotka(this->kraj_,"", "kraj");
		this->kraje_.push_back(tmpKraj);
		poslednyPridanyKraj = &hierarchia->emplaceSon(*hierarchia->accessRoot(), poradieKrajov);
		poslednyPridanyKraj->data_ = tmpKraj;
		++poradieKrajov;
		poradieSOORP = 0;
		this->pridajDoTabulky(tmpKraj, this->tabulkaKrajov);
		tmpKraj = nullptr;
		return;
	}
	if (this->kraje_.back()->getKod() == "")
	{
		this->kraje_.back()->setKod(data[0]);
	}

	//Ak kraj nie je prazdny, predosly riadok bol kraj a potrebujem kod k nemu z dalsieho riadku
	/*if (!this->kraj_.empty()) {
		kodKraja = data[0];
		UzemnaJednotka tmpKraj(this->kraj_, kodKraja);
		this->kraj_.clear();
		this->kraje_.push_back(tmpKraj);
	}
	//Ak sa kod rovna aktualnemu prvku, sme v istom kraji
	if (this->kraje_.back().getKod() != data[0])
	{
		kodKraja = data[0];
		if ((this->kraje_.back().getNazov() != this->kraj_))
		{
			UzemnaJednotka tmpKraj(this->kraj_, kodKraja);
			this->kraje_.push_back(tmpKraj);
		}
	}*/
	//Ak nacitame kodSOORP, catchnem ci to nie je x
	
	if (data.at(3) == "1" || data.at(3) == "x")
	{
		UzemnaJednotka* tmpSoorp = new UzemnaJednotka(data[2], data[1], "soorp");
		this->SOORPs_.push_back(tmpSoorp);
		poslednyPridanySOORP = &hierarchia->emplaceSon(*poslednyPridanyKraj, poradieSOORP);
		poslednyPridanySOORP->data_ = tmpSoorp;
		++poradieSOORP;
		poradieObci = 0;
		this->pridajDoTabulky(tmpSoorp, this->tabulkaSOORP);
		tmpSoorp = nullptr;
	}
	if (data.size() < 15)
	{
		kanalizacia = ""; 
		vodovod = "";
		plyn = "";
	}
	else
	{
		if (data[13] == "-" || data[13] == "")
		{
			kanalizacia = "";
		}
		else {
			kanalizacia = data[13];
		}
		if (data[14] == "-" || data[14] == "")
		{
			vodovod = "";
		}
		else {
			vodovod = data[14];
		}
		if (data[15] == "-" || data[15] == "")
		{
			plyn = "";
		}
		else {
			plyn = data[15];
		}
	}			
	Obec* tmpObec = new Obec(data[4], data[5], "obec", data[9], data[10],
		data[11], data[12], kanalizacia, vodovod, plyn);			
	this->obce_.push_back(tmpObec);
	hierarchia->emplaceSon(*poslednyPridanySOORP, poradieObci).data_ = tmpObec;
	++poradieObci;
	this->pridajDoTabulky(tmpObec, this->tabulkaObci);
	tmpObec = nullptr;
	
	//std::cout << this->kraje_[0].getNazov() << this->kraje_[0].getKodKraju() << std::endl;
	//std::this_thread::sleep_for(std::chrono::seconds(3)); //Test vypisu
	
}

void Nacitac_suboru::pridajDoTabulky(UzemnaJednotka* jednotka, ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* tabulka)
{
	ds::adt::ImplicitList<UzemnaJednotka*>** tabulkaData = nullptr;
	auto jednotkaExistuje = tabulka->tryFind(jednotka->getNazov(), tabulkaData); //vrati true ak obsahuje uz jednotku
																				 // + vrati aj LIST!
	if (!jednotkaExistuje)
	{
		ds::adt::ImplicitList<UzemnaJednotka*>* tempList = new ds::adt::ImplicitList<UzemnaJednotka*>();
		tempList->insertLast(jednotka);
		tabulka->insert(jednotka->getNazov(), tempList);
	}
	else
	{
		(*tabulkaData)->insertLast(jednotka);
	}
}

std::vector<UzemnaJednotka*> &Nacitac_suboru::getSoorp()
{
	return this->SOORPs_;
}

std::vector<UzemnaJednotka*> &Nacitac_suboru::getObce()
{
	return this->obce_;
}

std::vector<UzemnaJednotka*> &Nacitac_suboru::getKraje()
{
	return this->kraje_;
}

ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* &Nacitac_suboru::getTabulka(int typ)
{
	if (typ == 1)
	{
		return this->tabulkaKrajov;
	}
	if (typ == 2)
	{
		return this->tabulkaSOORP;
	}
	if (typ == 3)
	{
		return this->tabulkaObci;
	}
}

ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* &Nacitac_suboru::getHierarchia()
{
	return this->hierarchia;
}


