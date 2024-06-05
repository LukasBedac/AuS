#include "menu.h"
#define RESET "\033[0m"
#define BLUE "\033[36m"
#define RED "\033[31m"
Menu::~Menu()
{
	delete nacitac;
	aktualnyVrchol = nullptr;
	nacitac = nullptr;
	delete sort;
	tabulka = nullptr;
}

void Menu::startMenu()
{
	bool run = true;
	nacitac->nacitajSubor("conv_CR.csv");
	while (run)
	{
		this->typFiltracie_ = 0;
		this->vyberMenu_ = 0;
		this->vyberJednotky_ = 0;
		this->filtracnyPrvok_ = "";
	//Vyber menu
		std::cout << RESET << "---------------------------------------------------------" << "\n";
		std::cout << "Zoznam menu" << "\n";
		std::cout << "---------------------------------------------------------" << "\n";
		std::cout << "1. èas semestrálnej práce" << "\n";
		std::cout << "2. 2. a 4. èas semestrálnej práce" << "\n";
		std::cout << "3. èas semestrálnej práce" << "\n";
		std::cout << "4. Ukonèi aplikáciu" << "\n" << "Váš výber: ";

		std::cin >> this->vyberMenu_;
		if (vyberMenu_ == 4)
		{
			run = false;
			break;
		}
		if (vyberMenu_ == 1)
		{
			//Start
			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "Zoznam možností na vyfiltrovanie územných jednotiek" << "\n";
			std::cout << "---------------------------------------------------------" << "\n";

			//Menu 
			std::cout << "1. Kraje Èeskej republiky" << "\n";
			std::cout << "2. SOORP (Správny obvod obce s rožširenou pôsobnosou) Èeskej republiky" << "\n";
			std::cout << "3. Obce Èeskej republiky" << "\n";
			std::cout << "4. Koniec programu" << "\n" << "Váš výber: ";
			std::cin >> this->vyberJednotky_;
			std::cout << "\n";
			if (!this->rozsahMenuHandling())
			{
				break;
			}			
			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "Zadajte znaky, ktoré chcete v danej jednotke vyhlada" << "\n";
			std::cout << "---------------------------------------------------------" << "\n" << "Vaše znaky: ";
			std::cin >> this->filtracnyPrvok_;
			std::cout << "\n";

			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "Vyberte si možnos filtrovania: " << "\n";
			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "1. Jednotka zaèína na: " << this->filtracnyPrvok_ << "\n";
			std::cout << "2. Jednotka obsahuje znaky: " << this->filtracnyPrvok_ << "\n" << "Váš výber: ";
			std::cin >> this->typFiltracie_;
			if (this->typFiltracie_ < 1 || this->typFiltracie_ > 2)
			{
				this->spravneInfo_ = false;
				while (!this->spravneInfo_)
				{
					std::cout << RED << "Chyba pri vyberaní filtraènej metódy, zadajte èíslo znova" << "\n" << RESET <<"Váš výber: ";
					std::cin >> this->typFiltracie_;
					std::cout << "---------------------------------------------------------" << "\n";
					std::cout << "\n";
					if (this->typFiltracie_ < 1 || this->typFiltracie_ > 2)
					{
						continue;
					}
					else {
						this->spravneInfo_ = true;
					}
				}
			}
			std::vector<UzemnaJednotka*> vybraneData;
			switch (this->vyberJednotky_)
			{
			case 1:
				vybraneData = nacitac->getKraje();
				break;
			case 2:
				vybraneData = nacitac->getSoorp();
				break;
			case 3:
				vybraneData = nacitac->getObce();
				break;
			default:
				break;
			}
			std::vector<UzemnaJednotka*> konecneData;
			konecneData = algoritmus.filtrujData(vybraneData.begin(), vybraneData.end(), [&](UzemnaJednotka* jednotka) {

				if (typFiltracie_ == 1)
				{
					return jednotka->getNazov().find(filtracnyPrvok_) == 0 ? true : false;
				}
				else {
					return jednotka->getNazov().find(filtracnyPrvok_) != std::string::npos ? true : false;
				}
				});
			for (UzemnaJednotka* jednotka : konecneData)
			{
				std::cout << BLUE << jednotka->Vypis() << RESET << "\n";
			}

			std::cout << "\n" << "Poèet vypísaných jednotiek: " << konecneData.size() << "\n";
			konecneData.clear();
			vybraneData.clear();

		}
		if (vyberMenu_ == 2) 
		{
			//auto hierarchia = nacitac.getHierarchia();
			aktualnyVrchol = nacitac->getHierarchia()->accessRoot();
			
			int vyberMožnosti = 0;
			bool cast2 = true;
			//Start
			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "Možnosti použitia hierarchie" << "\n";
			std::cout << "---------------------------------------------------------" << "\n";

			//Menu
			while (cast2)
			{
				std::cout << "Aktuálne ste vo vrchole: " << BLUE << aktualnyVrchol->data_->getNazov() << RESET << "\n";
				std::cout << "1. Pokraèova hlbšie do hierarchie" << "\n";
				std::cout << "2. Vráti sa na otca" << "\n";
				std::cout << "3. Spusti preh¾adávanie pod¾a zadaného typu" << "\n";
				std::cout << "4. Koniec programu" << "\n" << "Váš výber: ";
				std::cin >> vyberMožnosti;
				std::cout << "---------------------------------------------------------" << "\n";	
				if (vyberMožnosti == 4) {
					cast2 = false;
					run = false;
					continue;
				}
				if (vyberMožnosti == 1)
				{
					if (aktualnyVrchol->sons_->size() != 0)
					{
						for (size_t i = 0; i < aktualnyVrchol->sons_->size(); ++i)
						{
							std::cout << BLUE << (i + 1) << " " << aktualnyVrchol->sons_->access(i)->data_->data_->getNazov() << RESET << "\n";
						}
						std::cout << "---------------------------------------------------------" << "\n";
						std::cout << "Vyberte èíslo, do ktorého syna sa chcete dosta" << "\n" << "Váš výber ";
						int vybranySyn = 0;
						std::cin >> vybranySyn;
						std::cout << "---------------------------------------------------------" << "\n";
						aktualnyVrchol = aktualnyVrchol->sons_->access(vybranySyn - 1)->data_; // - 1 na korektne vybratie
						continue;
					}
					else
					{
						std::cout << RED << "Nedá sa dosta hlbšie do hierarchie" << RESET << "\n";
						continue;
					}
					
				}
				if (vyberMožnosti == 2)
				{
					if (aktualnyVrchol->parent_ == nullptr)
					{
						std::cout << RED << "Nemôžte ís vyššie, pretože ste v koreni!" << RESET << "\n";
						continue;
					}
					else
					{
						aktualnyVrchol = nacitac->getHierarchia()->accessParent(*aktualnyVrchol);
						continue;
					}
				}
				if (vyberMožnosti == 3)
				{
					std::cout << "---------------------------------------------------------" << "\n";
					std::cout << "Vyberte si možnos filtrovania: " << "\n";
					std::cout << "---------------------------------------------------------" << "\n";
					std::cout << "1. Jednotka zaèína na: " << this->filtracnyPrvok_ << "\n";
					std::cout << "2. Jednotka obsahuje znaky: " << this->filtracnyPrvok_ << "\n";
					std::cout << "3. Jednotka má typ: " << this->filtracnyPrvok_ << "\n" << "Váš výber: ";
					std::cin >> this->typFiltracie_;
					std::cout << "---------------------------------------------------------" << "\n";
					if (this->typFiltracie_ < 1 || this->typFiltracie_ > 3)
					{
						this->spravneInfo_ = false;
						while (!this->spravneInfo_)
						{
							std::cout << RED << "Chyba pri vyberaní filtraènej metódy, zadajte èíslo znova" << "\n" << RESET << "Váš výber: ";
							std::cin >> this->typFiltracie_;
							std::cout << "\n";
							if (this->typFiltracie_ < 1 || this->typFiltracie_ > 3)
							{
								continue;
							}
							else {
								this->spravneInfo_ = true;
							}
						}
					}
					std::string filtracnyZnak = "";
					ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator zaciatok(nacitac->getHierarchia(), aktualnyVrchol);
					ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator koniec(nacitac->getHierarchia(), nullptr);
					std::vector<UzemnaJednotka*> vystupData;
					switch (this->typFiltracie_)
					{
					case 1:
						std::cout << "Zadajte znak, ktorý chcete vyh¾ada" << "\n" << "Váš výber: ";
						std::cin >> filtracnyZnak;
						std::cout << "---------------------------------------------------------" << "\n";
						vystupData = algoritmus.filtrujData(zaciatok, koniec, [&](UzemnaJednotka* jednotka) {
							return jednotka->getNazov().find(filtracnyZnak) == 0 ? true : false;
							});
						break;
					case 2:
						std::cout << "Zadajte znak, ktorý chcete vyh¾ada" << "\n" << "Váš výber: ";
						std::cin >> filtracnyZnak;
						std::cout << "---------------------------------------------------------" << "\n";
						vystupData = algoritmus.filtrujData(zaciatok, koniec, [&](UzemnaJednotka* jednotka) {
							return jednotka->getNazov().find(filtracnyZnak) != std::string::npos ? true : false;
							});
						break;
					case 3:
						std::cout << "Vyberte typ, ktorý chcete vyhladat: obec, soorp, kraj" << "\n" << "Váš výber: ";
						std::cin >> filtracnyZnak;
						std::cout << "---------------------------------------------------------" << "\n";
						vystupData = algoritmus.filtrujData(zaciatok, koniec, [&](UzemnaJednotka* jednotka) {
							return jednotka->getTyp() == filtracnyZnak ;						
							});
						break;
					default:
						break;
					}
					ds::amt::ImplicitSequence<UzemnaJednotka*>* data = new ds::amt::ImplicitSequence<UzemnaJednotka*>();
					for (auto item : vystupData)
					{
						data->insertLast().data_ = item;
					}
					int triedenie;
					std::cout << "---------------------------------------------------------" << "\n";
					std::cout << "Chcete vyfiltrované územné jednotky utriedi?" << "\n";
					std::cout << "---------------------------------------------------------" << "\n";
					std::cout << "1. Vypísa bez triedenia" << "\n";
					std::cout << "2. Utriedi a následne vypísa" << "\n";
					std::cin >> triedenie;
					std::cout << "---------------------------------------------------------" << "\n";
					if (triedenie < 1 || triedenie > 2)
					{
						while (triedenie == 1 || triedenie == 2) {
							std::cout << RED << "Chyba pri vyberaní možnosti, zadajte èíslo znova prosím" << RESET << "\n";
							std::cin >> triedenie;
						}
					}
					if (triedenie == 1)
					{
						this->vypisanie(data);
						break;
					}
					if (triedenie == 2)
					{
						int volbaTriediacejMetody;
						sort = new Sort();
						std::cout << "Zvo¾te si možnos utriedenia" << "\n";						
						std::cout << "1. Utriedi abecedne" << "\n";
						std::cout << "2. Utriedi pod¾a poètu spoluhlások" << "\n";
						std::cout << RED << "Pri zle vybranej vo¾be sa dáta utriedia abecedne!" << "\n";
						std::cin >> volbaTriediacejMetody;
						
						if (volbaTriediacejMetody == 2)
						{
							sort->utried(*data, volbaTriediacejMetody);
						}
						else
						{
							sort->utried(*data, 1);
						}
						this->vypisanie(data);
						data->clear();
						delete data;
						vystupData.clear();
						break;
					}
				}
			}	
		}
		if (vyberMenu_ == 3)
		{
			std::cout << "---------------------------------------------------------" << "\n";
			std::cout << "Vypísanie územných jednotiek pod¾a názvu z tabu¾ky" << "\n";
			std::cout << "---------------------------------------------------------" << "\n";

			std::cout << "1. Kraje Èeskej republiky" << "\n";
			std::cout << "2. SOORP (Správny obvod obce s rožširenou pôsobnosou) Èeskej republiky" << "\n";
			std::cout << "3. Obce Èeskej republiky" << "\n";
			std::cout << "4. Koniec programu" << "\n" << "Váš výber: ";
			std::cin >> this->vyberJednotky_;
			if (!this->rozsahMenuHandling())
			{
				break;
			}
			
			ds::adt::ImplicitList<UzemnaJednotka*>** vystupData;
			this->tabulka = nacitac->getTabulka(this->vyberJednotky_);
			std::cout << "Zadajte názov, ktorý chcete filtrova" << "\n" << "Názov " << "\n";
			std::cin.ignore();
			std::getline(std::cin, this->filtracnyPrvok_);	
			if (this->tabulka->tryFind(this->filtracnyPrvok_, vystupData)) 
			{
				std::cout << "---------------------------------------------------------" << "\n";
				for (auto jednotka : **vystupData)
				{
					std::cout << BLUE << jednotka->Vypis() << RESET << "\n";
				}
				std::cout << "---------------------------------------------------------" << "\n";
			}
			else
			{
				std::cout << "---------------------------------------------------------" << "\n";
				std::cout << RED << "Nenašli sa žiadne územné jendotky so zadaným názvom" << RESET << "\n";
				std::cout << "---------------------------------------------------------" << "\n";
			}
			//vystupData.clear();
			
		}
	}
}

bool Menu::rozsahMenuHandling()
{
	if (this->vyberJednotky_ < 1 || this->vyberJednotky_ > 3)
	{
		if (this->vyberJednotky_ == 4)
		{
			return  false;
		}
		this->spravneInfo_ = false;
		while (!this->spravneInfo_)
		{
			std::cout << RED << "Chyba pri vyberaní územnej jednotky, zadajte èíslo znova" << "\n" << RESET << "Váš výber: ";
			std::cin >> this->vyberJednotky_;
			if (this->vyberJednotky_ == 4)
			{
				return  false;
			}
			else if (this->vyberJednotky_ < 1 || this->vyberJednotky_ > 3)
			{
				continue;
			}
			else 
			{
				this->spravneInfo_ = true;
				return true;
			}
		}
	}
}

void Menu::vypisanie(ds::amt::ImplicitSequence<UzemnaJednotka*>* &vystupData)
{
	for (auto item : *vystupData)
	{
		std::cout << BLUE << item->Vypis() << RESET << "\n";
	}
	std::cout << "---------------------------------------------------------" << "\n";
	std::cout << "Poèet vypísaných jednotiek: " << vystupData->size() << "\n";
	std::cout << "---------------------------------------------------------" << "\n";
	vystupData->clear();
}

