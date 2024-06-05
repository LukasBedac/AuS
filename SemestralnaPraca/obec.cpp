#include "obec.h"


Obec::Obec(std::string nazov_, std::string kod_,
	std::string typ, std::string hektare, std::string pocetObyvatelov,
	std::string pocetObyvatelovMlady, std::string pocetObyvatelovStary, std::string kanalizacia,
	std::string vodovod, std::string plyn) : UzemnaJednotka(nazov_, kod_, typ)
{
	this->hektare_ = hektare;
	this->pocetObyvatelov_ = pocetObyvatelov;
	this->pocetObyvatelovMlady_ = pocetObyvatelovMlady;
	this->pocetObyvatelovStary_ = pocetObyvatelovStary;
	this->kanalizacia_ = kanalizacia;
	this->vodovod_ = vodovod;
	this->plyn_ = plyn;
}

std::string Obec::Vypis()
{
	return UzemnaJednotka::Vypis() + 
		+ ", " + this->hektare_ + "ha" + " | " + this->pocetObyvatelov_ + " " + this->pocetObyvatelovMlady_ + " " + this->pocetObyvatelovStary_
		+ " | " + this->kanalizacia_ + " " + this->vodovod_ + " " + this->plyn_ + " |";
}


 
