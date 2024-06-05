#pragma once
#include "uzemna_jednotka.h"
#include <string>

class Obec : public UzemnaJednotka
{

private:
	std::string typ_;
	std::string hektare_;
	std::string pocetObyvatelov_;
	std::string pocetObyvatelovMlady_;
	std::string pocetObyvatelovStary_;
	std::string kanalizacia_;
	std::string vodovod_;
	std::string plyn_;
public:
	Obec(std::string nazov, std::string kod,
		std::string typ, std::string hektare,
		std::string pocetObyvatelov, std::string pocetObyvatelovMlady,
		std::string pocetObyvatelovStary, std::string kanalizacia,
		std::string vodovod, std::string plyn);
	~Obec() {};
	std::string Vypis() override;
	/*size_t getHektare();
	size_t getPocetObyvatelov();
	size_t getPocetObyvatelovMlady();
	size_t getPocetObyvatelovStary();
	unsigned int getKanalizacia();
	unsigned int getVodovod();
	unsigned int getPlyn();*/

	/*void setTyp();
	void setHektare();
	void setPocetObyvatelov();
	void setPocetObyvatelovMlady();
	void setPocetObyvatelovStary();
	void setKanalizacia();
	void setVodovod();
	void setPlyn();*/
};

