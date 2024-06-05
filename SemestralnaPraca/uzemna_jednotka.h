#pragma once
#include <string>

class UzemnaJednotka
{
private:	
	
protected:
	std::string nazov_;
	std::string kod_;
	std::string typ_;
	size_t pocetSpoluhlasok_ = -1;
public:
	UzemnaJednotka(std::string nazov, std::string kod, std::string typ);
	virtual ~UzemnaJednotka() {};
	std::string getNazov();
	std::string getKod();
	std::string getTyp();
	void setKod(std::string kod);
	virtual std::string Vypis();
	size_t pocetSpoluhlasok();
};

