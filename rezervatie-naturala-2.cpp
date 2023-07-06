#include <iostream>
#include <vector>
#include <algorithm>
// #include <bits/stdc++.h>
using namespace std;

class IOInterface {
public:
    // metode pur virtuale => clasa abstracta
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const = 0;
};


class Animal: public IOInterface {
protected:
    string nume, specie, mancare;
    vector <string> habitate;
    int varsta, masa;
    string gen;
    bool vertebrat, protejat;

public:
    //constructori
    Animal();
    Animal(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, bool protejat);
    Animal(const Animal& obj);

    //operatori
    Animal& operator =(const Animal& obj);
    friend istream& operator >>(istream& in, Animal& obj);
    friend ostream& operator <<(ostream& out, const Animal& obj);

    // metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    // setters
    void setNume(string nume) {this->nume = nume;}
    void setSpecie(string specie) {this->specie = specie;}
    void setMancare(string mancare) {this->mancare = mancare;}
    void setHabitate();
    void setVarsta(int varsta) {this->varsta = varsta;}
    void setMasa(int masa) {this->masa = masa;}
    void setGen(string gen) {this->gen = gen;}
    void setVertebrat(bool vertebrat) {this->vertebrat = vertebrat;}
    void setProtejat(bool protejat) {this->protejat = protejat;} 

    // getters
    string getSpecie() const {return this->specie;}

    virtual string tipAnimal() const = 0;

    // destructor
    virtual ~Animal() {};
};

// constructorul fara parametrii
Animal::Animal() {
    this->nume = "";
    this->specie = "";
    this->mancare = "";
    this->habitate = {};
    this->varsta = 0;
    this->masa = 0;
    this->vertebrat = 0;
    this->protejat = 0;
}

// constructorul cu parametrii
Animal::Animal(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, bool protejat) {
    this->nume = nume;
    this->specie = specie;
    this->mancare = mancare;
    this->habitate = habitate;
    this->varsta = varsta;
    this->masa = masa;
    this->gen = gen;
    this->vertebrat = vertebrat;
    this->protejat = protejat;
}

// constructorul de copiere
Animal::Animal(const Animal& obj) {
    this->nume = obj.nume;
    this->specie = obj.specie;
    this->mancare = obj.mancare;
    this->habitate = obj.habitate;
    this->varsta = obj.varsta;
    this->masa = obj.masa;
    this->gen = obj.gen;
    this->vertebrat = obj.vertebrat;
    this->protejat = obj.protejat;
}

// operatorul =
Animal& Animal::operator =(const Animal& obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->specie = obj.specie;
        this->mancare = obj.mancare;
        this->habitate = obj.habitate;
        this->varsta = obj.varsta;
        this->masa = obj.masa;
        this->gen = obj.gen;
        this->vertebrat = obj.vertebrat;
        this->protejat = obj.protejat;
    }
    return *this;
}

// metoda de citire
istream& Animal::citire(istream& in) {
    cout << "Nume: ";
    in >> this->nume;
    cout << "Specie: ";
    in >> this->specie;
    cout << "Mancare: ";
    in >> this->mancare;

    if(!this->habitate.empty())
        this->habitate.clear();
    cout << "Adauga un habitat: apasa 0\n";
    cout << "Stop: apasa 1\n";
    bool ok;

    while(cin >> ok && ok != 1) {
        this->habitate.push_back(*(new string));
        cout << "Habitat: ";
        in >> this->habitate.back();
        cout << "Adauga un habitat: apasa 0\n";
        cout << "Stop: apasa 1\n";
    }

    cout << "Varsta: ";
    in >> this->varsta;
    cout << "Masa: ";
    in >> this->masa;
    cout << "Gen: ";
    in >> this->gen;
    cout << "Vertebrat (1 pt da, 0 pt nu): ";
    in >> this->vertebrat;
    cout << "Protejat (1 pt da, 0 pt nu): ";
    in >> this->protejat;
    return in;
}

// metoda de afisare
ostream& Animal::afisare(ostream& out) const {
    out << "Nume: " << this->nume << "\n";
    out << "Specie: " << this->specie << "\n";
    out << "Mancare: " << this->mancare << "\n";
    out << "Habitate: ";
    for(int i = 0; i < this->habitate.size(); i++)
        out << this->habitate[i] << " ";
    out << "\n";
    out << "Varsta: " << this->varsta << "\n";
    out << "Masa: " << this->masa << "\n";
    out << "Gen: " << this->gen << "\n";
    out << "Vertebrat: " << this->vertebrat << "\n";
    out << "Protejat: " << this->protejat << "\n";
    return out;
}

// operatorul >>
istream& operator >>(istream& in, Animal& obj) {
    return obj.citire(in);
}

// operatorul <<
ostream& operator <<(ostream& out, const Animal& obj) {
    return obj.afisare(out);
}

void Animal::setHabitate() {
    bool ok = 1;

    while(ok) {
        cout << "Adauga un habitat: apasa 0\n";
        cout << "Sterge un habitat: apasa 1\n";
        cout << "Stop: apasa 2\n";

        int comanda;
        cin >> comanda;

        switch(comanda) {
            case 0: {
                string habitat;
                cout << "Habitat: ";
                cin >> habitat;
                this->habitate.push_back(habitat);
                break;
            }

            case 1: {
                int i;
                cout << "Indicele habitatului pe care vreti sa il stergeti: ";
                cin >> i;
                if (i < this->habitate.size())
                    this->habitate.erase(habitate.begin() + i);
                else
                    cout << "Indice invalid\n";
                break;
            }

            case 2: {
                ok = 0;
                break;
            }

            default: {
                cout << "Comanda invalida\n";
                break;
            }
        }
    }
}



class AnimalTerestru: virtual public Animal {
protected:
    float vitezaMaximaAlergare;
    vector <string> clima;

public:
    //constructori
    AnimalTerestru();
    AnimalTerestru(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, 
        string gen, bool vertebrat, bool protejat, float vitezaMaximaAlergare, vector <string> clima);
    AnimalTerestru(const AnimalTerestru& obj);

    //operatori
    AnimalTerestru& operator =(const AnimalTerestru& obj);

    // metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    // setters
    void setVitezaMaximaAlergare(float vitezaMaximaAlergare) {this->vitezaMaximaAlergare = vitezaMaximaAlergare;}
    void setClima();

    string tipAnimal() const {return "terestru";}

    // destructor
    ~AnimalTerestru() {};
};


AnimalTerestru::AnimalTerestru(): Animal() {
    this->vitezaMaximaAlergare = 0;
    this->clima = {};
}

AnimalTerestru::AnimalTerestru(string nume, string specie, string mancare, vector <string> habitate, int varsta, 
    int masa, string gen, bool vertebrat, bool protejat, float vitezaMaximaAlergare, vector <string> clima):
    Animal(nume, specie, mancare, habitate, varsta, masa, gen, vertebrat, protejat) {
    this->vitezaMaximaAlergare = vitezaMaximaAlergare;
    this->clima = clima;
}

AnimalTerestru::AnimalTerestru(const AnimalTerestru& obj): Animal(obj) {
    this->vitezaMaximaAlergare = obj.vitezaMaximaAlergare;
    this->clima = obj.clima;
}

AnimalTerestru& AnimalTerestru::operator =(const AnimalTerestru& obj) {
    if(this != &obj) {
        Animal::operator =(obj);
        this->vitezaMaximaAlergare = obj.vitezaMaximaAlergare;
        this->clima = obj.clima;
    }
    return *this;
}

istream& AnimalTerestru::citire(istream& in) {
    Animal::citire(in);
    cout << "Viteza maxima alergare: ";
    in >> this->vitezaMaximaAlergare;
    
    if(!this->clima.empty())
        this->clima.clear();
    cout << "Adauga o clima: apasa 0\n";
    cout << "Stop: apasa 1\n";
    bool ok;

    while(cin >> ok && ok != 1) {
        this->clima.push_back(*(new string));
        cout << "Clima: ";
        in >> this->clima.back();
        cout << "Adauga o clima: apasa 0\n";
        cout << "Stop: apasa 1\n";
    }

    return in;
}

ostream& AnimalTerestru::afisare(ostream& out) const {
    Animal::afisare(out);
    out << "Viteza maxima alergare: " << this->vitezaMaximaAlergare << "\n";
    out << "Clima: ";
    for(int i = 0; i < this->clima.size(); i++)
        out << this->clima[i] << " ";
    out << "\n";
    return out;
}

void AnimalTerestru::setClima() {
    bool ok = 1;

    while(ok) {
        cout << "Adauga o clima: apasa 0\n";
        cout << "Sterge o clima: apasa 1\n";
        cout << "Stop: apasa 2\n";

        int comanda;
        cin >> comanda;

        switch(comanda) {
            case 0: {
                string climaNoua;
                cout << "Clima: ";
                cin >> climaNoua;
                this->clima.push_back(climaNoua);
                break;
            }

            case 1: {
                int i;
                cout << "Indicele climei pe care vreti sa o stergeti: ";
                cin >> i;
                if (i < this->clima.size())
                    this->clima.erase(clima.begin() + i);
                else
                    cout << "Indice invalid\n";
                break;
            }

            case 2: {
                ok = 0;
                break;
            }

            default: {
                cout << "Comanda invalida\n";
                break;
            }
        }
    }
}


class AnimalAcvatic: virtual public Animal {
protected:
    float vitezaMaximaInot;
    string tipApa;

public:
    //constructori
    AnimalAcvatic();
    AnimalAcvatic(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, bool protejat, float vitezaMaximaInot, string tipApa);
    AnimalAcvatic(const AnimalAcvatic& obj);

    //operatori
    AnimalAcvatic& operator =(const AnimalAcvatic& obj);

    // metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    // setters
    void setVitezaMaximaInot(float vitezaMaximaInot) {this->vitezaMaximaInot = vitezaMaximaInot;}
    void setTipApa(string tipApa) {this->tipApa = tipApa;}

    string tipAnimal() const {return "acvatic";}

    // destructor
    ~AnimalAcvatic() {};
};

AnimalAcvatic::AnimalAcvatic(): Animal() {
    this->vitezaMaximaInot = 0;
    this->tipApa = "";
}

AnimalAcvatic::AnimalAcvatic(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, bool protejat, float vitezaMaximaInot, string tipApa):
    Animal(nume, specie, mancare, habitate, varsta, masa, gen, vertebrat, protejat) {
    this->vitezaMaximaInot = vitezaMaximaInot;
    this->tipApa = tipApa;
}

AnimalAcvatic::AnimalAcvatic(const AnimalAcvatic& obj): Animal(obj) {
    this->vitezaMaximaInot = obj.vitezaMaximaInot;
    this->tipApa = obj.tipApa;
}

AnimalAcvatic& AnimalAcvatic::operator =(const AnimalAcvatic& obj) {
    if(this != &obj) {
        Animal::operator =(obj);
        this->vitezaMaximaInot = obj.vitezaMaximaInot;
        this->tipApa = obj.tipApa;
    }
    return *this;
}

istream& AnimalAcvatic::citire(istream& in) {
    Animal::citire(in);
    cout << "Viteza maxima inot: ";
    in >> this->vitezaMaximaInot;
    cout << "Tip apa: ";
    in >> this->tipApa;
    return in;
}

ostream& AnimalAcvatic::afisare(ostream& out) const {
    Animal::afisare(out);
    out << "Viteza maxima inot: " << vitezaMaximaInot << "\n";
    out << "Tip apa: " << tipApa << "\n";
    return out;
}


class AnimalMixt: public AnimalTerestru, public AnimalAcvatic {
    string respiratie;
public:
    //constructori
    AnimalMixt();
    AnimalMixt(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, 
        bool protejat, float vitezaMaximaAlergare, vector <string> clima, float vitezaMaximaInot, string tipApa, string respiratie);
    AnimalMixt(const AnimalMixt& obj);

    //operatori
    AnimalMixt& operator =(const AnimalMixt& obj);

    // metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    // setters
    void setRespiratie(string respiratie) {this->respiratie = respiratie;}

    string tipAnimal() const {return "mixt";}

    // destructor
    ~AnimalMixt() {};
};


AnimalMixt::AnimalMixt() {
    this->respiratie = "";
}

AnimalMixt::AnimalMixt(string nume, string specie, string mancare, vector <string> habitate, int varsta, int masa, string gen, bool vertebrat, 
    bool protejat, float vitezaMaximaAlergare, vector <string> clima, float vitezaMaximaInot, string tipApa, string respiratie):
    Animal(nume, specie, mancare, habitate, varsta, masa, gen, vertebrat, protejat), 
    AnimalTerestru(nume, specie, mancare, habitate, varsta, masa, gen, vertebrat, protejat, vitezaMaximaAlergare, clima),
    AnimalAcvatic(nume, specie, mancare, habitate, varsta, masa, gen, vertebrat, protejat, vitezaMaximaInot, tipApa) {
    this->respiratie = respiratie;
}

AnimalMixt::AnimalMixt(const AnimalMixt& obj): Animal(obj), AnimalTerestru(obj), AnimalAcvatic(obj) {
    this->respiratie = obj.respiratie;
}

AnimalMixt& AnimalMixt::operator =(const AnimalMixt& obj) {
    if(this != &obj) {
        AnimalTerestru::operator=(obj);
        AnimalAcvatic::operator=(obj);
        this->respiratie = obj.respiratie;
    }
    return *this;
}

istream& AnimalMixt::citire(istream& in) {
    Animal::citire(in);
    cout << "Viteza maxima alergare: ";

    in >> this->vitezaMaximaAlergare;
    if(!this->clima.empty())
        this->clima.clear();
    cout << "Adauga o clima: apasa 0\n";
    cout << "Stop: apasa 1\n";
    bool ok;

    while(cin >> ok && ok != 1) {
        this->clima.push_back(*(new string));
        cout << "Clima: ";
        in >> this->clima.back();
        cout << "Adauga o clima: apasa 0\n";
        cout << "Stop: apasa 1\n";
    }

    cout << "Viteza maxima inot: ";
    in >> this->vitezaMaximaInot;
    cout << "Tip apa: ";
    in >> this->tipApa;
    cout << "Respiratie: ";
    in >> this->respiratie;
    return in;
}

ostream& AnimalMixt::afisare(ostream& out) const {
    Animal::afisare(out);
    out << "Viteza maxima alergare: " << this->vitezaMaximaAlergare << "\n";
    out << "Clima: ";
    for(int i = 0; i < this->clima.size(); i++)
        out << this->clima[i] << " ";
    out << "\n";
    out << "Viteza maxima inot: " << this->vitezaMaximaInot << "\n";
    out << "Tip apa: " << this->tipApa << "\n";
    out << "Respiratie: " << this->respiratie << "\n";
    return out;
}


class RezervatieNaturala {
    vector <Animal*> animale;

public:
    void addAnimal();
    void showAnimale() const;
    void showSpecii() const;
    Animal* getAnimal(int i);
    void deleteAnimal(int i);
    ~RezervatieNaturala();
};

void RezervatieNaturala::addAnimal() {
    Animal* animal;
    cout << "Animal terestru: apasa 0\n";
    cout << "Animal acvatic: apasa 1\n";
    cout << "Animal mixt: apasa 2\n";
    int ok;
    cin >> ok;

    switch(ok) {
        case 0: {
            animal = new AnimalTerestru();
            break;
        }

        case 1: {
            animal = new AnimalAcvatic();
            break;
        }

        case 2: {
            animal = new AnimalMixt();
            break;
        }
        
        default: {
            cout << "Comanda invalida\n";
            break;
        }
    }

    cin >> *animal;
    animale.push_back(animal);
}

void RezervatieNaturala::showAnimale() const {
    for(int i = 0; i < animale.size(); i++)
        cout << *animale[i] << "\n";
}

bool sortSpecii(const pair <string, int> s1, const pair <string, int> s2) {
    return s1.second > s2.second;
}

void RezervatieNaturala::showSpecii() const {
    vector <pair <string, int>> specii;
    bool ok = 0;
    for (int i = 0; i < this->animale.size() && ok == 0; i++) {
        for (int j = 0; j < specii.size(); j++) {
            if (this->animale[i]->getSpecie() == specii[j].first) {
                ok = 1;
                specii[j].second ++;
            }
        }
        if (!ok) {
            specii.push_back(make_pair(this->animale[i]->getSpecie(), 1));
        }
    }

    sort(specii.begin(), specii.end(), sortSpecii);
    cout << "Specii: \n";
    for (int i = 0; i < specii.size(); i++) {
        cout << specii[i].first << ": " << specii[i].second << " animale\n";
    }
}

Animal* RezervatieNaturala::getAnimal(int i) {
    if (i < this->animale.size()) 
        return this->animale[i];
    else
        return NULL;
}

void RezervatieNaturala::deleteAnimal(int i) {
    if (i < this->animale.size()) 
        this->animale.erase(animale.begin() + i);
    else
        cout << "Indice invalid\n";
}

RezervatieNaturala::~RezervatieNaturala() {
    for (int i = 0; i < this->animale.size(); i++) {
        if (this->animale[i] != NULL) {
            delete this->animale[i];
            this->animale[i] = NULL;
        }
    }
}


int main() {
    RezervatieNaturala rezervatie;
    Animal* animal;
    bool ok = 1;

    while(ok) {
        cout << "Adauga un animal: apasa 0\n";
        cout << "Afiseaza animalele: apasa 1\n";
        cout << "Afiseaza speciile: apasa 2\n";
        cout << "Modifica un animal: apasa 3\n";
        cout << "Sterge un animal: apasa 4\n";
        cout << "Stop: apasa 5\n";

        int comanda;
        cin >> comanda;

        switch(comanda) {
            case 0: {
                rezervatie.addAnimal();
                break;
            }

            case 1: {
                rezervatie.showAnimale();
                break;
            }

            case 2: {
                rezervatie.showSpecii();
                break;
            }

            case 3: {
                cout << "Indicele animalului pe care doriti sa il modificati: ";
                int i;
                cin >> i;
                if (rezervatie.getAnimal(i) == NULL)
                    cout << "Indice invalid\n";
                else {
                    cout << "Tipul animalului ales este: " << rezervatie.getAnimal(i)->tipAnimal() << "\n";
                    cout << "Modifica numele: apasa 0\n";
                    cout << "Modifica specia: apasa 1\n";
                    cout << "Modifica mancarea: apasa 2\n";
                    cout << "Modifica habitatele: apasa 3\n";
                    cout << "Modifica varsta: apasa 4\n";
                    cout << "Modifica masa: apasa 5\n";
                    cout << "Modifica genul: apasa 6\n";
                    cout << "Modifica vertebrat: apasa 7\n";
                    cout << "Modifica protejat: apasa 8\n";

                    if (rezervatie.getAnimal(i)->tipAnimal() == "terestru") {
                        cout << "Modifica viteza maxima de alergare: apasa 9\n";
                        cout << "Modifica clima: apasa 10\n";
                    }

                    if (rezervatie.getAnimal(i)->tipAnimal() == "acvatic") {
                        cout << "Modifica viteza maxima de inot: apasa 9\n";
                        cout << "Modifica tipul de apa: apasa 10\n";
                    }

                    if(rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                        cout << "Modifica viteza maxima de alergare: apasa 9\n";
                        cout << "Modifica clima: apasa 10\n";
                        cout << "Modifica viteza maxima de inot: apasa 11\n";
                        cout << "Modifica tipul de apa: apasa 12\n";
                        cout << "Modifica respiratia: apasa 13\n";
                    }

                    int comanda2;
                    cin >> comanda2;

                    switch(comanda2) {
                        case 0: {
                            string nume;
                            cout << "Noul nume: ";
                            cin >> nume;
                            rezervatie.getAnimal(i)->setNume(nume);
                            break;
                        }

                        case 1: {
                            string specie;
                            cout << "Noua specie: ";
                            cin >> specie;
                            rezervatie.getAnimal(i)->setSpecie(specie);
                            break;
                        }

                        case 2: {
                            string mancare;
                            cout << "Noua mancare: ";
                            cin >> mancare;
                            rezervatie.getAnimal(i)->setMancare(mancare);
                            break;
                        }

                        case 3: {
                            rezervatie.getAnimal(i)->setHabitate();
                            break;
                        }

                        case 4: {
                            int varsta;
                            cout << "Noua durata de viata: ";
                            cin >> varsta;
                            rezervatie.getAnimal(i)->setVarsta(varsta);
                            break;
                        }

                        case 5: {
                            int masa;
                            cout << "Noua masa: ";
                            cin >> masa;
                            rezervatie.getAnimal(i)->setMasa(masa);
                            break;
                        }

                        case 6: {
                            string gen;
                            cout << "Noul gen: ";
                            cin >> gen;
                            rezervatie.getAnimal(i)->setGen(gen);
                            break;
                        }

                        case 7: {
                            bool vertebrat;
                            cout << "Noul vertebrat (1 pt da, 0 pt nu): ";
                            cin >> vertebrat;
                            rezervatie.getAnimal(i)->setVertebrat(vertebrat);
                            break;
                        }

                        case 8: {
                            bool protejat;
                            cout << "Noul protejat (1 pt da, 0 pt nu): ";
                            cin >> protejat;
                            rezervatie.getAnimal(i)->setProtejat(protejat);
                            break;
                        }

                        case 9: {
                            if (rezervatie.getAnimal(i)->tipAnimal() == "terestru" || rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                                float vitezaMaximaAlergare;
                                cout << "Noua viteza maxima de alergare: ";
                                cin >> vitezaMaximaAlergare;
                                dynamic_cast<AnimalTerestru*>(rezervatie.getAnimal(i))->setVitezaMaximaAlergare(vitezaMaximaAlergare);
                            }
                            else {
                                if (rezervatie.getAnimal(i)->tipAnimal() == "acvatic") {
                                    float vitezaMaximaInot;
                                    cout << "Noua viteza maxima de inot: ";
                                    cin >> vitezaMaximaInot;
                                    dynamic_cast<AnimalAcvatic*>(rezervatie.getAnimal(i))->setVitezaMaximaInot(vitezaMaximaInot);
                                }
                            }
                            break;
                        }

                        case 10: {
                            if (rezervatie.getAnimal(i)->tipAnimal() == "terestru" || rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                               dynamic_cast<AnimalTerestru*>(rezervatie.getAnimal(i))->setClima();
                            }
                            else {
                                if (rezervatie.getAnimal(i)->tipAnimal() == "acvatic") {
                                    string tipApa;
                                    cout << "Noul tip de apa: ";
                                    cin >> tipApa;
                                    dynamic_cast<AnimalAcvatic*>(rezervatie.getAnimal(i))->setTipApa(tipApa);
                                }
                            }
                            break;
                        }

                        case 11: {
                            if (rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                                float vitezaMaximaInot;
                                cout << "Noua viteza maxima de inot: ";
                                cin >> vitezaMaximaInot;
                                dynamic_cast<AnimalMixt*>(rezervatie.getAnimal(i))->setVitezaMaximaInot(vitezaMaximaInot);
                            }
                            break;
                        }

                        case 12: {
                            if (rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                                string tipApa;
                                cout << "Noul tip de apa: ";
                                cin >> tipApa;
                                dynamic_cast<AnimalMixt*>(rezervatie.getAnimal(i))->setTipApa(tipApa);
                            }
                            break;
                        }

                        case 13: {
                            if (rezervatie.getAnimal(i)->tipAnimal() == "mixt") {
                                string respiratie;
                                cout << "Noul tip de respiratie: ";
                                cin >> respiratie;
                                dynamic_cast<AnimalMixt*>(rezervatie.getAnimal(i))->setRespiratie(respiratie);
                            }
                            break;
                        }

                        default: {
                            cout << "Comanda invalida\n";
                            break;
                        }
                    }
                }
                break;
            }

            case 4: {
                int i;
                cout << "Indicele animalului pe care vreti sa il stergeti: ";
                cin >> i;
                rezervatie.deleteAnimal(i);
                break;
            }

            case 5: {
                ok = 0;
                break;
            }

            default: {
                cout << "Comanda invalida\n";
                break;
            }
        }
    }

    return 0;
}