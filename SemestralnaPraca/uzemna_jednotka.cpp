#include "uzemna_jednotka.h"

UzemnaJednotka::UzemnaJednotka(std::string nazov, std::string kod, std::string typ)
{
    this->nazov_ = nazov;
    this->kod_ = kod;
    this->typ_ = typ;
}


std::string UzemnaJednotka::getNazov()
{
    return this->nazov_;
}

std::string UzemnaJednotka::getKod()
{
    return this->kod_;
}

std::string UzemnaJednotka::getTyp()
{
    return this->typ_;
}

void UzemnaJednotka::setKod(std::string kod)
{
    this->kod_ = kod;
}

std::string UzemnaJednotka::Vypis()
{
    return this->getNazov() + ", kÛd: " + this->getKod() + ", typ: " + this->getTyp();
}

size_t UzemnaJednotka::pocetSpoluhlasok()
{
    if (this->pocetSpoluhlasok_ != -1)
    {
        return this->pocetSpoluhlasok_; // Ak sa raz vypocitaju, nech sa nemusia pocitat znova
    }
    this->pocetSpoluhlasok_ = 0;

    char spoluhlasky[] =
    {
        'd', 't', 'n', 'l', 'ch', 'h', 'g', 'k',
        'D', 'T', 'N', 'L', 'Ch', 'H', 'G', 'K',
        'Ô', 'ù', 'Ú', 'æ', 'c', 'Ë', 'û', 'ö', 'dz', 'dû', 'j',
        'œ', 'ç', '“', 'º', 'C', '»', 'é', 'ä', 'Dz', 'Dû', 'J',
        'b', 'm', 'p', 'r', 's', 'v', 'z', 'f',
        'B', 'M', 'P', 'R', 'S', 'V', 'Z', 'F', '¯', 'ÿ'
    };
    for (size_t i = 0; i < this->getNazov().length(); ++i)
    {
        char c = this->getNazov().at(i); 
        for (size_t j = 0; j < sizeof(spoluhlasky); ++j)
        {
            if (c == spoluhlasky[j])
            {
                ++pocetSpoluhlasok_; 
                break;
            }
        }
    }
    return this->pocetSpoluhlasok_;
}


