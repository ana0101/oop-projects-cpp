#include <iostream>
#include <cstring>
using namespace std;

class Rulare;

class Film  {

    static int contorId;
    const int id;
    char *nume,  *categorie;
    int varstaMinima;
    float durata;
    int nrZile;
    int *nrBileteVanduteZi;

public:
    //constructori
    Film(char *nume, char *categorie, int varstaMinima, float durata, int nrZile, int *nrBileteVanduteZi); //constructorul cu toti parametrii
    Film(char *nume, char *categorie); //constructor cu parametrii
    Film(char *nume, char *categorie, int varstaMinima, float durata); //constructor cu parametrii
    Film(); //constructorul fara parametrii
    Film(const Film& obj); //constructorul de copiere

    //operatori
    Film& operator =(const Film&);
    friend ostream& operator <<(ostream& out, const Film& obj);
    friend istream& operator >>(istream& in, Film& obj);
    int operator [](int i);
    Film& operator ++();
    Film operator ++(int);
    Film operator +(int nr);
    Film operator +(int nr);
    Film operator +(const Film& obj);
    operator int() const {return varstaMinima;}
    bool operator <(const Film& obj);
    bool operator ==(const Film& obj);
    friend Film operator +(const Film& film, const Rulare& rulare);

    //functionalitate
    int nrBileteVadute();

    //getters
    static int getContorId() {return Film::contorId;}
    const int getId() const {return id;}
    const char *getNume() const {return this->nume;}
    const char *getCategorie() const {return this->categorie;}
    int getVarstaMinima() const {return varstaMinima;}
    float getDurata() const {return durata;}
    int getNrZile() const {return nrZile;}
    const int *getNrBileteVanduteZi() const {return this->nrBileteVanduteZi;}

    //setters
    void setNume(char *nume);
    void setCategorie(char *categorie);
    void setVarstaMinima(int varstaMinima);
    void setDurata(float durata);
    void setNrZile(int nrZile);
    void setNrBileteVanduteZi(int nrBileteVanduteZi, int poz);

    //destructor
    ~Film();
};

int Film::contorId = 0;


class Sala {

    static int contorId;
    const int id;
    int capacitate;
    char *tip;

public:
    //constructori
    Sala(int capacitate, char *tip); //constructorul cu toti parametrii
    Sala(int capacitate); //constructor cu parametrii
    Sala(char *tip); //constructor cu parametrii
    Sala(); //constructorul fara parametrii
    Sala(const Sala& obj); //constructorul de copiere

    //operatori
    Sala& operator =(const Sala&);
    friend ostream& operator <<(ostream& out, const Sala& obj);
    friend istream& operator >>(istream& in, Sala& obj);
    Sala& operator ++();
    Sala operator ++(int);
    Sala operator +(int nr);
    friend Sala operator +(int nr, Sala obj);
    Sala operator +(const Sala& obj);
    operator int() const {return capacitate;}
    bool operator <(const Sala& obj);
    bool operator ==(const Sala& obj);

    //setters
    void setCapacitate(int capacitate);
    void setTip(char *tip);

    //getters
    int getCapacitate() {return capacitate;}
    const char *getTip() const {return tip;}

    //destructor
    ~Sala();
};

int Sala::contorId = 100;


class Rulare {

    static int contorId;
    const int id;
    int idFilm;
    char *numeFilm;
    int idSala;
    double oraInceput, oraSfarsit;
    bool locuriLibere;
    int nrLocuri;
    bool *locuri;

public:
    //constructori
    Rulare(int idFilm, char *numeFilm, int idSala, double oraInceput, double oraSfarsit, bool locuriLibere, int nrLocuri, bool *locuri); //constructorul cu toti parametrii
    Rulare(int idFilm, char *numeFilm); //constructor cu parametrii
    Rulare(int idFilm, char *numeFilm, int idSala, double oraInceput, double oraSfarsit); //constructor cu parametrii
    Rulare(); //constructorul fara parametrii
    Rulare(const Rulare& obj); //constructorul de copiere

    //operatori
    Rulare& operator = (const Rulare&);
    friend ostream& operator <<(ostream& out, const Rulare& obj);
    friend istream& operator >>(istream& in, Rulare& obj);
    bool operator [](int i);
    Rulare& operator ++();
    Rulare operator ++(int);
    Rulare operator +(int nr);
    friend Rulare operator +(int nr, Rulare obj);
    Rulare operator +(const Rulare& obj);
    operator bool() const {return locuriLibere;}
    bool operator <(const Rulare& obj);
    bool operator ==(const Rulare& obj);
    friend Film operator +(const Film& film, const Rulare& rulare);
    Film operator +(const Film& film);

    //functionalitate
    double procentOcupare();

    //getters
    static int getContorId() {return Rulare::contorId;}
    const int getId() {return id;}
    int getIdFilm() {return idFilm;}
    const char *getNumeFilm() const {return this->numeFilm;}
    int getIdSala() {return idSala;}
    double getOraInceput() {return oraInceput;}
    double getOraSfarsit() {return oraSfarsit;}
    bool getLocuriLibere() {return locuriLibere;}
    int getNrLocuri() {return nrLocuri;}
    const bool *getLocuri() const {return this->locuri;}

    //setters
    void setIdFilm(int idFilm);
    void setNumeFilm(char *numeFilm);
    void setIdSala(int idSala);
    void setOraInceput(double oraInceput);
    void setOraSfarsit(double oraSfarsit);
    void setLocuriLibere(bool locuriLibere);
    void setNrLocuri(int nrLocuri);
    void setLocuri(bool ocupat, int poz);

    //destructor
    ~Rulare();
};

int Rulare::contorId = 200;


class Client {

    static int contorId;
    const int id;
    char *nume, *prenume;
    char gen;
    int varsta;

public:
    //constructori
    Client(char *nume, char *prenume, char gen, int varsta); //constructorul cu toti parametrii
    Client(char *nume, char *prenume); //constructor cu parametrii
    Client(char *nume, char *prenume, int varsta); //constructor cu parametrii
    Client(); //constructorul fara parametrii
    Client(const Client& obj); //constructorul de copiere

    //operatori
    Client& operator =(const Client&);
    friend ostream& operator <<(ostream& out, const Client& obj);
    friend istream& operator >>(istream& in, Client& obj);
    Client& operator ++();
    Client operator ++(int);
    Client operator +(int nr);
    friend Client operator +(int nr, Client obj);
    Client operator +(const Client& obj);
    operator char() const {return gen;}
    bool operator <(const Client& obj);
    bool operator ==(const Client& obj);

    //functionalitate
    bool major() {return varsta >= 18;};

    //getters
    char getGen() {return gen;}

    //setters
    void setNume(char *nume);
    void setPrenume(char *prenume);
    void setGen(char gen);
    void setVarsta(int varsta);

    //destructor
    ~Client();
};

int Client::contorId = 300;



Film::Film(char *nume, char *categorie, int varstaMinima, float durata, int nrZile, int *nrBileteVanduteZi): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->categorie = new char[strlen(categorie)+1];
    strcpy(this->categorie, categorie);
    this->varstaMinima = varstaMinima;
    this->durata = durata;
    this->nrZile = nrZile;
    this->nrBileteVanduteZi = new int[nrZile];
    for(int i=0; i<nrZile; i++)
        this->nrBileteVanduteZi[i] = nrBileteVanduteZi[i];
}

Film::Film(char *nume, char *categorie): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->categorie = new char[strlen(categorie)+1];
    strcpy(this->categorie, categorie);
    varstaMinima = 0;
    durata = 0.0;
    nrZile = 0;
    nrBileteVanduteZi = NULL;
}

Film::Film(char *nume, char *categorie, int varstaMinima, float durata): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->categorie = new char[strlen(categorie)+1];
    strcpy(this->categorie, categorie);
    this->varstaMinima = varstaMinima;
    this->durata = durata;
    nrZile = 0;
    nrBileteVanduteZi = NULL;
}

Film::Film(): id(contorId++) {
    nume = NULL;
    categorie = NULL;
    varstaMinima = 0;
    durata = 0.0;
    nrZile = 0;
    nrBileteVanduteZi = NULL;
}

Film::Film(const Film& obj): id(obj.id) {
    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);
    this->categorie = new char[strlen(obj.categorie)+1];
    strcpy(this->categorie, obj.categorie);
    this->varstaMinima = obj.varstaMinima;
    this->durata = obj.durata;
    this->nrZile = obj.nrZile;
    this->nrBileteVanduteZi = new int[this->nrZile];
    for(int i=0; i<nrZile; i++)
        this->nrBileteVanduteZi[i] = obj.nrBileteVanduteZi[i];
}

Film& Film::operator =(const Film& obj) {
    if(this != &obj) {
        if(this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }
        if(this->categorie != NULL) {
            delete[] this->categorie;
            this->categorie = NULL;
        }
        if(this->nrBileteVanduteZi != NULL) {
            delete[] this->nrBileteVanduteZi;
            this->nrBileteVanduteZi = NULL;
        }
        this->nume = new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);
        this->categorie = new char[strlen(obj.categorie)+1];
        strcpy(this->categorie, obj.categorie);
        this->varstaMinima = obj.varstaMinima;
        this->durata = obj.durata;
        this->nrZile = obj.nrZile;
        this->nrBileteVanduteZi = new int[this->nrZile];
        for(int i=0; i<nrZile; i++)
            this->nrBileteVanduteZi[i] = obj.nrBileteVanduteZi[i];
    }
    return *this;
}

ostream& operator <<(ostream& out, const Film& obj) {
    out << "Id: " << obj.id << "\n";
    out << "Nume: " << obj.nume << "\n";
    out << "Categorie: " << obj.categorie << "\n";
    out << "Varsta minima: " << obj.varstaMinima << "\n";
    out << "Durata: " << obj.durata << "\n";
    out << "Numar zile: " << obj.nrZile << "\n";
    out << "Numar bilete vandute pe zi: ";
    for(int i=0; i<obj.nrZile; i++)
        out << obj.nrBileteVanduteZi[i] << " ";
    out << "\n";
    return out;
}

istream& operator >>(istream& in, Film& obj) {
    cout << "Nume: ";
    char nume[51];
    in.ignore();
    in.getline(nume, 51);
    if(obj.nume != NULL) {
        delete[] obj.nume;
        obj.nume = NULL;
    }
    obj.nume = new char[strlen(nume)+1];
    strcpy(obj.nume, nume);

    cout << "Categorie: ";
    char categorie[51];
    in.getline(categorie, 51);
    if(obj.categorie != NULL) {
        delete[] obj.categorie;
        obj.categorie = NULL;
    }
    obj.categorie = new char[strlen(categorie)+1];
    strcpy(obj.categorie, categorie);

    cout << "Varsta minima: ";
    in >> obj.varstaMinima;

    cout << "Durata: ";
    in >> obj.durata;

    cout << "Numar zile: ";
    in >> obj.nrZile;

    cout << "Numar bilete vandute pe zi: ";
    if(obj.nrBileteVanduteZi != NULL) {
        delete[] obj.nrBileteVanduteZi;
        obj.nrBileteVanduteZi = NULL;
    }
    obj.nrBileteVanduteZi = new int[obj.nrZile+1];
    for(int i=0; i<obj.nrZile; i++)
        in >> obj.nrBileteVanduteZi[i];

    return in;
}

int Film::operator [](int i) {
    if(nrBileteVanduteZi == NULL) 
        throw runtime_error("Nu exista elemente in vector");
    if(i<0 || i>=nrZile)
        throw runtime_error("Index invalid");
    else
        return nrBileteVanduteZi[i];
}

Film& Film::operator ++() {
    if(nrBileteVanduteZi != NULL) {
        int aux[nrZile];
        for(int i=0; i<nrZile; i++)
            aux[i] = nrBileteVanduteZi[i];
        delete[] nrBileteVanduteZi;
        nrBileteVanduteZi = NULL;

        nrZile ++;
        nrBileteVanduteZi = new int[nrZile];
        for(int i=0; i<nrZile-1; i++)
            nrBileteVanduteZi[i] = aux[i];
        nrBileteVanduteZi[nrZile-1] = 0;
    }
    else {
        nrZile ++;
        nrBileteVanduteZi = new int[nrZile];
        nrBileteVanduteZi[nrZile-1] = 0;
    }
    return *this;
}

Film Film::operator ++(int) {
    Film aux(*this);
    if(this->nrBileteVanduteZi != NULL) {
        int aux2[this->nrZile];
        for(int i=0; i<this->nrZile; i++)
            aux2[i] = this->nrBileteVanduteZi[i];
        delete[] this->nrBileteVanduteZi;
        this->nrBileteVanduteZi = NULL;

        this->nrZile ++;
        this->nrBileteVanduteZi = new int[this->nrZile];
        for(int i=0; i<this->nrZile-1; i++)
            this->nrBileteVanduteZi[i] = aux2[i];
        this->nrBileteVanduteZi[this->nrZile-1] = 0;
    }
    else {
        this->nrZile ++;
        this->nrBileteVanduteZi = new int[this->nrZile];
        this->nrBileteVanduteZi[this->nrZile-1] = 0;
    }
    return aux;
}

Film Film::operator +(int nr) {
    Film aux(*this);
    if(aux.nrBileteVanduteZi != NULL) {
        int nrBilete2[aux.nrZile];
        for(int i=0; i<aux.nrZile; i++)
            nrBilete2[i] = aux.nrBileteVanduteZi[i];
        delete[] aux.nrBileteVanduteZi;
        aux.nrBileteVanduteZi = NULL;

        aux.nrZile += nr;
        aux.nrBileteVanduteZi = new int[aux.nrZile];
        for(int i=0; i<aux.nrZile-nr; i++)
            aux.nrBileteVanduteZi[i] = nrBilete2[i];
        for(int i=aux.nrZile-nr; i<aux.nrZile; i++)
            aux.nrBileteVanduteZi[i] = 0;
    }
    else {
        aux.nrZile += nr;
        aux.nrBileteVanduteZi = new int[aux.nrZile];
        for(int i=0; i<aux.nrZile; i++)
            aux.nrBileteVanduteZi[i] = 0;
    }
    return aux;
}

Film Film::operator +(int nr) {
    return *this + nr;
}


Film Film::operator +(const Film& obj) {
    Film aux;
    aux = *this;
    if(aux.nume != NULL && obj.nume != NULL) {
        char nume2[105];
        strcpy(nume2, aux.nume);
        strcat(nume2, " ");
        strcat(nume2, obj.nume);
        delete[] aux.nume;
        aux.nume = new char[strlen(nume2)+1];
        strcpy(aux.nume, nume2);
    }
    else {
        if(aux.nume == NULL && obj.nume != NULL) {
            aux.nume = new char[strlen(obj.nume)+1];
            strcpy(aux.nume, obj.nume);
        }
    }

    if(aux.categorie != NULL && obj.categorie != NULL) {
        char categorie2[105];
        strcpy(categorie2, aux.categorie);
        strcat(categorie2, " ");
        strcat(categorie2, obj.categorie);
        delete[] aux.categorie;
        aux.categorie = new char[strlen(categorie2)+1];
        strcpy(aux.categorie, categorie2);
    }
    else {
        if(aux.categorie == NULL && obj.categorie != NULL) {
            aux.categorie = new char[strlen(obj.categorie)+1];
            strcpy(aux.categorie, obj.categorie);
        }
    }
    
    if(obj.varstaMinima > aux.varstaMinima)
        aux.varstaMinima = obj.varstaMinima;
    aux.durata += obj.durata;

    if(aux.nrZile <= obj.nrZile) {
        if(aux.nrBileteVanduteZi != NULL) {
            delete[] aux.nrBileteVanduteZi;
            aux.nrBileteVanduteZi = NULL;
        }
        aux.nrBileteVanduteZi = new int[obj.nrZile];
        aux.nrZile = obj.nrZile;
        for(int i=0; i<this->nrZile; i++)
            aux.nrBileteVanduteZi[i] = this->nrBileteVanduteZi[i] + obj.nrBileteVanduteZi[i];
        for(int i=this->nrZile; i<aux.nrZile; i++)
            aux.nrBileteVanduteZi[i] = obj.nrBileteVanduteZi[i];
    }
    else {
        for(int i=0; i<obj.nrZile; i++)
            aux.nrBileteVanduteZi[i] += obj.nrBileteVanduteZi[i];
    }
    return aux;
}


bool Film::operator <(const Film& obj) {
    if(this->durata < obj.durata)
        return true;
    return false;
}

bool Film::operator ==(const Film& obj) {
    if(strcmp(this->nume, obj.nume) != 0)
        return false;
    if(strcmp(this->categorie, obj.categorie) != 0)
        return false;
    if(this->varstaMinima != obj.varstaMinima)
        return false;
    if(this->durata != obj.durata)
        return false;
    if(this->nrZile != obj.nrZile)
        return false;
    for(int i=0; i<this->nrZile; i++)
        if(this->nrBileteVanduteZi[i] != obj.nrBileteVanduteZi[i])
            return false;
    return true;
}

Film operator +(const Film& film, const Rulare& rulare) {
    Film aux;
    aux = film;
    int nrBilete = 0;
    for(int i=0; i<rulare.nrLocuri; i++)
        nrBilete += rulare.locuri[i];
    aux.nrBileteVanduteZi[aux.nrZile-1] += nrBilete;
    return aux;
}

Film Rulare::operator +(const Film& film) {
    return film + *this;
}

int Film::nrBileteVadute() {
    int nr = 0;
    for(int i=0; i<this->nrZile; i++)
        nr += this->nrBileteVanduteZi[i];
    return nr;
}

void Film::setNume(char *nume) {
    if(this->nume != NULL) {
        delete[] this->nume;
        this->nume = NULL;
    }
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
}

void Film::setCategorie(char *categorie) {
    if(this->categorie != NULL) {
        delete[] this->categorie;
        this->categorie = NULL;
    }
    this->categorie = new char[strlen(categorie)+1];
    strcpy(this->categorie, categorie);
}

void Film::setVarstaMinima(int varstaMinima) {
    this->varstaMinima = varstaMinima;
}

void Film::setDurata(float durata) {
    this->durata = durata;
}

void Film::setNrZile(int nrZile) {
    int nrBilete2[this->nrZile];
    if(this->nrBileteVanduteZi != NULL) {
        for(int i=0; i<this->nrZile; i++)
            nrBilete2[i] = this->nrBileteVanduteZi[i];
        delete[] this->nrBileteVanduteZi;
        this->nrBileteVanduteZi = NULL;
    }
    this->nrBileteVanduteZi = new int[nrZile];
    if(this->nrZile <= nrZile) {
        for(int i=0; i<this->nrZile; i++)
            this->nrBileteVanduteZi[i] = nrBilete2[i];
        for(int i=this->nrZile; i<nrZile; i++)
            this->nrBileteVanduteZi[i] = 0;
        this->nrZile = nrZile;
    }
    else {
        this->nrZile = nrZile;
        for(int i=0; i<this->nrZile; i++)
            this->nrBileteVanduteZi[i] = nrBilete2[i];
    }
}

void Film::setNrBileteVanduteZi(int nrBileteVanduteZi, int poz) {
    if(this->nrBileteVanduteZi == NULL) 
        throw runtime_error("Nu exista elemente in vector");
    if(poz<0 || poz>=this->nrZile)
        throw runtime_error("Index invalid");
    else
        this->nrBileteVanduteZi[poz] = nrBileteVanduteZi;
}

Film::~Film() {
    if(nume != NULL) {
        delete[] nume;
        nume = NULL;
    }
    if(categorie != NULL) {
        delete[] categorie;
        categorie = NULL;
    }
    if(nrBileteVanduteZi != NULL) {
        delete[] nrBileteVanduteZi;
        nrBileteVanduteZi = NULL;
    }
}



Sala::Sala(int capacitate, char *tip): id(contorId++) {
    this->capacitate = capacitate;
    this->tip = new char[strlen(tip)+1];
    strcpy(this->tip, tip);
}

Sala::Sala(int capacitate): id(contorId++) {
    this->capacitate = capacitate;
    tip = new char[strlen("-")+1];
    strcpy(tip, "-");
}

Sala::Sala(char *tip): id(contorId++) {
    this->tip = new char[strlen(tip)+1];
    strcpy(this->tip, tip);
    capacitate = 0;
}

Sala::Sala(): id(contorId++) {
    capacitate = 0;
    tip = new char[strlen("-")+1];
    strcpy(tip, "-");
}

Sala::Sala(const Sala& obj): id(obj.id) {
    this->capacitate = obj.capacitate;
    this->tip = new char[strlen(obj.tip)+1];
    strcpy(this->tip, obj.tip);
}

Sala& Sala::operator = (const Sala& obj) {
    if(this != &obj){
        if(this->tip != NULL) {
            delete[] this->tip;
            this->tip = NULL;
        }
        this->capacitate = obj.capacitate;
        this->tip = new char[strlen(obj.tip)+1];
        strcpy(this->tip, obj.tip);
    }
    return *this;
}

ostream& operator <<(ostream& out, const Sala& obj) {
    out << "Id: " << obj.id << "\n";
    out << "Capacitate: " << obj.capacitate << "\n";
    out << "Tip: " << obj.tip << "\n";
    return out;
}

istream& operator >>(istream& in, Sala& obj) {
    cout << "Capacitate: ";
    in >> obj.capacitate;

    char tip[51];
    cout << "Tip: ";
    in.ignore();
    in.getline(tip, 51);
    if(obj.tip != NULL) {
        delete[] obj.tip;
        obj.tip = NULL;
    }
    obj.tip = new char[strlen(tip)+1];
    strcpy(obj.tip, tip);

    return in;
}

Sala& Sala::operator ++() {
    capacitate ++;
    return *this;
}

Sala Sala::operator ++(int) {
    Sala aux(*this);
    this->capacitate ++;
    return aux;
}

Sala Sala::operator +(int nr) {
    Sala aux(*this);
    aux.capacitate += nr;
    return aux;
}

Sala operator +(int nr, Sala obj) {
    return obj+nr;
}

Sala Sala::operator +(const Sala& obj) {
    Sala aux;
    aux = *this;
    aux.capacitate += obj.capacitate;

    if(aux.tip != NULL && obj.tip != NULL) {
        char tip2[105];
        strcpy(tip2, aux.tip);
        strcat(tip2, " ");
        strcat(tip2, obj.tip);
        delete[] aux.tip;
        aux.tip = new char[strlen(tip2)+1];
        strcpy(aux.tip, tip2);
    }
    else {
        if(aux.tip == NULL && obj.tip != NULL) {
            aux.tip = new char[strlen(obj.tip)+1];
            strcpy(aux.tip, obj.tip);
        }
    }
    return aux;
}

bool Sala::operator <(const Sala& obj) {
    if(this->capacitate < obj.capacitate)
        return true;
    return false;
}

bool Sala::operator ==(const Sala& obj) {
    if(this->capacitate == obj.capacitate)
        return false;
    if(strcmp(this->tip, obj.tip) != 0)
        return false;
    return true;
}

void Sala::setCapacitate(int capacitate) {
    this->capacitate = capacitate;
}

void Sala::setTip(char *tip) {
    if(this->tip != NULL) {
        delete[] this->tip;
        this->tip = NULL;
    }
    this->tip = new char[strlen(tip)+1];
    strcpy(this->tip, tip);
}

Sala::~Sala() {
    if(tip != NULL){
        delete[] tip;
        tip = NULL;
    }
}



Rulare::Rulare(int idFilm, char *numeFilm, int idSala, double oraInceput, double oraSfarsit, bool locuriLibere, int nrLocuri, bool *locuri): id(contorId++) {
    this->idFilm = idFilm;
    this->numeFilm = new char[strlen(numeFilm)+1];
    strcpy(this->numeFilm, numeFilm);
    this->idSala = idSala;
    this->oraInceput = oraInceput;
    this->oraSfarsit = oraSfarsit;
    this->locuriLibere = locuriLibere;
    this->nrLocuri = nrLocuri;
    this->locuri = new bool[nrLocuri];
    for(int i=0; i<nrLocuri; i++)
        this->locuri[i] = locuri[i];
}

Rulare::Rulare(int idFilm, char *numeFilm): id(contorId++) {
    this->idFilm = idFilm;
    this->numeFilm = new char[strlen(numeFilm)+1];
    strcpy(this->numeFilm, numeFilm);
    idSala = 0;
    oraInceput = 0;
    oraSfarsit = 0;
    locuriLibere = 0;
    nrLocuri = 0;
    locuri = NULL;
}

Rulare::Rulare(int idFilm, char *numeFilm, int idSala, double oraInceput, double oraSfarsit): id(contorId++) {
    this->idFilm = idFilm;
    this->numeFilm = new char[strlen(numeFilm)+1];
    strcpy(this->numeFilm, numeFilm);
    this->idSala = idSala;
    this->oraInceput = oraInceput;
    this->oraSfarsit = oraSfarsit;
    locuriLibere = 0;
    nrLocuri = 0;
    locuri = NULL;
}

Rulare::Rulare(): id(contorId++) {
    idFilm = 0;
    numeFilm = new char[strlen("-")+1];
    strcpy(numeFilm, "-");
    idSala = 0;
    oraInceput = 0;
    oraSfarsit = 0;
    locuriLibere = 0;
    nrLocuri = 0;
    locuri = NULL;
}

Rulare::Rulare(const Rulare& obj): id(obj.id) {
    this->idFilm = obj.idFilm;
    this->numeFilm = new char[strlen(obj.numeFilm)+1];
    strcpy(this->numeFilm, obj.numeFilm);
    this->idSala = obj.idSala;
    this->oraInceput = obj.oraInceput;
    this->oraSfarsit = obj.oraSfarsit;
    this->locuriLibere = obj.locuriLibere;
    this->nrLocuri = obj.nrLocuri;
    this->locuri = new bool[obj.nrLocuri];
    for(int i=0; i<obj.nrLocuri; i++)
        this->locuri[i] = obj.locuri[i];
}

Rulare& Rulare::operator =(const Rulare& obj) {
    if(this != &obj) {
        if(this->locuri != NULL) {
            delete[] this->locuri;
            this->locuri = NULL;
        }
        if(this->numeFilm != NULL) {
            delete[] this->numeFilm;
            this->numeFilm = NULL;
        }

        this->idFilm = obj.idFilm;
        this->numeFilm = new char[strlen(obj.numeFilm)+1];
        strcpy(this->numeFilm, obj.numeFilm);
        this->idSala = obj.idSala;
        this->oraInceput = obj.oraInceput;
        this->oraSfarsit = obj.oraSfarsit;
        this->locuriLibere = obj.locuriLibere;
        this->nrLocuri = obj.nrLocuri;
        this->locuri = new bool[obj.nrLocuri];
        for(int i=0; i<obj.nrLocuri; i++)
            this->locuri[i] = obj.locuri[i];
    }
    return *this;
}

ostream& operator <<(ostream& out, const Rulare& obj) {
    out << "Id: " << obj.id << "\n";
    out << "Id film: " << obj.idFilm << "\n";
    out << "Nume film: " << obj.numeFilm << "\n";
    out << "Id sala: " << obj.idSala << "\n";
    out << "Ora inceput: " << obj.oraInceput << "\n";
    out << "Ora sfarsit: " << obj.oraSfarsit << "\n";
    out << "Locuri libere: " << obj.locuriLibere << "\n";
    out << "Numar locuri: " << obj.nrLocuri << "\n";
    out << "Locuri: ";
    for(int i=0; i<obj.nrLocuri; i++)
        out << obj.locuri[i] << " ";
    out << "\n";
    return out;
}

istream& operator >>(istream& in, Rulare& obj) {
    cout << "Id film: \n";
    in >> obj.idFilm;

    cout << "Nume film: \n";
    char numeFilm[51];
    in.ignore();
    in.getline(numeFilm, 51);
    if(obj.numeFilm != NULL) {
        delete[] obj.numeFilm;
        obj.numeFilm = NULL;
    }
    obj.numeFilm = new char[strlen(numeFilm)+1];
    strcpy(obj.numeFilm, numeFilm);

    cout << "Id sala: \n";
    in >> obj.idSala;

    cout << "Ora inceput: \n";
    in >> obj.oraInceput;

    cout << "Ora sfarsit: \n";
    in >> obj.oraSfarsit;

    cout << "Locuri libere: \n";
    in >> obj.locuriLibere;

    cout << "Numar locuri: \n";
    in >> obj.nrLocuri;

    cout << "Locuri: \n";
    if(obj.locuri != NULL) {
        delete[] obj.locuri;
        obj.locuri = NULL;
    }
    obj.locuri = new bool[obj.nrLocuri];
    for(int i=0; i<obj.nrLocuri; i++)
        in >> obj.locuri[i];

    return in;
}

bool Rulare::operator [](int i) {
    if(locuri == NULL) 
        throw runtime_error("Nu exista elemente in vector");
    if(i<0 || i>=nrLocuri)
        throw runtime_error("Index invalid");
    else
        return locuri[i];
}

Rulare& Rulare::operator ++() {
    if(locuri != NULL) {
        bool aux[nrLocuri];
        for(int i=0; i<nrLocuri; i++)
            aux[i] = locuri[i];

        delete[] locuri;
        locuri = NULL;

        nrLocuri ++;
        locuri = new bool[nrLocuri];
        for(int i=0; i<nrLocuri-1; i++)
            locuri[i] = aux[i];
        locuri[nrLocuri-1] = 0;
    }
    else {
        nrLocuri ++;
        locuri = new bool[nrLocuri];
        locuri[nrLocuri-1] = 0;
    }
    return *this;
}

Rulare Rulare::operator ++(int) {
    Rulare aux(*this);
    if(locuri != NULL) {
        bool aux2[nrLocuri];
        for(int i=0; i<nrLocuri; i++)
            aux2[i] = locuri[i];

        delete[] locuri;
        locuri = NULL;

        nrLocuri ++;
        locuri = new bool[nrLocuri];
        for(int i=0; i<nrLocuri-1; i++)
            locuri[i] = aux2[i];
        locuri[nrLocuri-1] = 0;
    }
    else {
        nrLocuri ++;
        locuri = new bool[nrLocuri];
        locuri[nrLocuri-1] = 0;
    }
    return aux;
}

Rulare Rulare::operator +(int nr) {
    Rulare aux(*this);
    if(aux.locuri != NULL) {
        bool locuri2[aux.nrLocuri];
        for(int i=0; i<aux.nrLocuri; i++)
            locuri2[i] = aux.locuri[i];

        delete[] aux.locuri;
        aux.locuri = NULL;

        aux.nrLocuri += nr;
        aux.locuri = new bool[aux.nrLocuri];
        for(int i=0; i<aux.nrLocuri-nr; i++)
            aux.locuri[i] = locuri2[i];
        for(int i=aux.nrLocuri-nr; i<aux.nrLocuri; i++)
            aux.locuri[i] = 0;
    }
    else {
        aux.nrLocuri += nr;
        aux.locuri = new bool[aux.nrLocuri];
        for(int i=0; i<aux.nrLocuri; i++)
            aux.locuri[i] = 0;
    }
    return aux;
}

Rulare operator +(int nr, Rulare obj) {
    return obj+nr;
}


Rulare Rulare::operator +(const Rulare& obj) {
    Rulare aux;
    aux = *this;
    aux.idFilm += obj.idFilm;
    if(aux.numeFilm != NULL && obj.numeFilm != NULL) {
        char numeFilm2[105];
        strcpy(numeFilm2, aux.numeFilm);
        strcat(numeFilm2, " ");
        strcat(numeFilm2, obj.numeFilm);
        delete[] aux.numeFilm;
        aux.numeFilm = new char[strlen(numeFilm2)+1];
        strcpy(aux.numeFilm, numeFilm2);
    }
    else {
        if(aux.numeFilm == NULL && obj.numeFilm != NULL) {
            aux.numeFilm = new char[strlen(obj.numeFilm)+1];
            strcpy(aux.numeFilm, obj.numeFilm);
        }
    }

    aux.idSala += obj.idSala;
    aux.oraInceput = std::min(aux.oraInceput, obj.oraInceput);
    aux.oraSfarsit = std::max(aux.oraSfarsit, obj.oraSfarsit);
    aux.locuriLibere = std::max(aux.locuriLibere, obj.locuriLibere);
    aux.nrLocuri += obj.nrLocuri;

    if(aux.locuri != NULL) {
        delete[] aux.locuri;
        aux.locuri = NULL;
    }
    if(aux.nrLocuri > 0) {
        aux.locuri = new bool[aux.nrLocuri];
        if(this->locuri != NULL) {
            for(int i=0; i<this->nrLocuri; i++)
                aux.locuri[i] = this->locuri[i];
        }
        if(obj.locuri != NULL) {
            for(int i=0; i<obj.nrLocuri; i++)
                aux.locuri[i+this->nrLocuri] = obj.locuri[i];
        }
    }

    return aux;
}


bool Rulare::operator <(const Rulare& obj) {
    if(this->oraInceput < obj.oraInceput)
        return true;
    return false;
}

bool Rulare::operator ==(const Rulare& obj) {
    if(this->idFilm != obj.idFilm)
        return false;
    if(strcmp(this->numeFilm, obj.numeFilm) != 0)
        return false;
    if(this->idSala != obj.idSala)
        return false;
    if(this->oraInceput != obj.oraInceput)
        return false;
    if(this->oraSfarsit != obj.oraSfarsit)
        return false;
    if(this->locuriLibere != obj.locuriLibere)
        return false;
    if(this->nrLocuri != obj.nrLocuri)
        return false;
    for(int i=0; i<this->nrLocuri; i++)
        if(this->locuri[i] != obj.locuri[i])
            return false;
    return true;
}

double Rulare::procentOcupare() {
    double procent = 0;
    int nrLocuriOcupate = 0;
    for(int i=0; i<this->nrLocuri; i++)
        nrLocuriOcupate += this->locuri[i];
    procent = nrLocuriOcupate * 100 / this->nrLocuri;
    return procent;
}

void Rulare::setIdFilm(int idFilm) {
    this->idFilm = idFilm;
}

void Rulare::setNumeFilm(char *numeFilm) {
    if(this->numeFilm != NULL) {
        delete[] this->numeFilm;
        this->numeFilm = NULL;
    }
    this->numeFilm = new char[strlen(numeFilm)+1];
    strcpy(this->numeFilm, numeFilm);
}

void Rulare::setIdSala(int idSala) {
    this->idSala = idSala;
}

void Rulare::setOraInceput(double oraInceput) {
    this->oraInceput = oraInceput;
}

void Rulare::setOraSfarsit(double oraSfarsit) {
    this->oraSfarsit = oraSfarsit;
}

void Rulare::setLocuriLibere(bool locuriLibere) {
    this->locuriLibere = locuriLibere;
}

void Rulare::setNrLocuri(int nrLocuri) {
    bool locuri2[this->nrLocuri];
    if(this->locuri != NULL) {
        for(int i=0; i<this->nrLocuri; i++)
            locuri2[i] = this->locuri[i];
        delete[] this->locuri;
        this->locuri = NULL;
    }
    this->locuri = new bool[nrLocuri];
    if(this->nrLocuri <= nrLocuri) {
        for(int i=0; i<this->nrLocuri; i++)
            this->locuri[i] = locuri2[i];
        for(int i=this->nrLocuri; i<nrLocuri; i++)
            this->locuri[i] = 0;
        this->nrLocuri = nrLocuri;
    }
    else {
        this->nrLocuri = nrLocuri;
        for(int i=0; i<this->nrLocuri; i++)
            this->locuri[i] = locuri2[i];
    }

    this->locuriLibere = 0;
    for(int i=0; i<this->nrLocuri; i++)
        if(this->locuri[i] == 0)
            this->locuriLibere = 1;
}

void Rulare::setLocuri(bool ocupat, int poz) {
    if(this->locuri == NULL) 
        throw runtime_error("Nu exista elemente in vector");
    if(poz<0 || poz>=this->nrLocuri)
        throw runtime_error("Index invalid");
    else
        this->locuri[poz] = ocupat;

    this->locuriLibere = 0;
    for(int i=0; i<this->nrLocuri; i++)
        if(this->locuri[i] == 0)
            this->locuriLibere = 1;
}

Rulare::~Rulare() {
    if(numeFilm != NULL) {
        delete[] numeFilm;
        numeFilm = NULL;
    }

    if(locuri != NULL) {
        delete[] locuri;
        locuri = NULL;
    }
}



Client::Client(char *nume, char *prenume, char gen, int varsta): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
    this->gen = gen;
    this->varsta = varsta;
}

Client::Client(char *nume, char *prenume): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
    this->gen = '-';
    this->varsta = 0;
}

Client::Client(char *nume, char *prenume, int varsta): id(contorId++) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
    this->varsta = varsta;
    this->gen = '-';
}

Client::Client(): id(contorId++) {
    nume = NULL;
    prenume = NULL;
    gen = '-';
    varsta = 0;
}

Client::Client(const Client& obj): id(obj.id) {
    this->nume = new char[strlen(obj.nume)+1];
    strcpy(this->nume, obj.nume);
    this->prenume = new char[strlen(obj.prenume)+1];
    strcpy(this->prenume, obj.prenume);
    this->gen = obj.gen;
    this->varsta = obj.varsta;
}

Client& Client::operator =(const Client& obj) {
    if(this != &obj) {
        if(this->nume != NULL) {
            delete[] this->nume;
            this->nume = NULL;
        }
        if(this->prenume != NULL) {
            delete[] this->prenume;
            this->prenume = NULL;
        }
        this->nume = new char[strlen(obj.nume)+1];
        strcpy(this->nume, obj.nume);
        this->prenume = new char[strlen(obj.prenume)+1];
        strcpy(this->prenume, obj.prenume);
        this->gen = obj.gen;
        this->varsta = obj.varsta;
    }
    return *this;
}

ostream& operator <<(ostream& out, const Client& obj) {
    out << "Id: " << obj.id << "\n";
    out << "Nume: " << obj.nume << "\n";
    out << "Prenume: " << obj.prenume << "\n";
    out << "Gen: " << obj.gen << "\n";
    out << "An nastere: " << obj.varsta << "\n";
    return out;
}

istream& operator >>(istream& in, Client& obj) {
    cout << "Nume: ";
    char nume[51];
    in.ignore();
    in.getline(nume, 51);
    if(obj.nume != NULL) {
        delete[] obj.nume;
        obj.nume = NULL;
    }
    obj.nume = new char[strlen(nume)+1];
    strcpy(obj.nume, nume);

    cout << "Prenume: ";
    char prenume[51];
    in.getline(prenume, 51);
    if(obj.prenume != NULL) {
        delete[] obj.prenume;
        obj.prenume = NULL;
    }
    obj.prenume = new char[strlen(prenume)+1];
    strcpy(obj.prenume, prenume);

    cout << "Gen: ";
    in >> obj.gen;

    cout << "An nastere: ";
    in >> obj.varsta;

    return in;
}

Client& Client::operator ++() {
    varsta ++;
    return *this;
}

Client Client::operator ++(int) {
    Client aux(*this);
    this->varsta ++;
    return aux;
}

Client Client::operator +(int nr) {
    Client aux(*this);
    aux.varsta += nr;
    return aux;
}

Client operator +(int nr, Client obj) {
    return obj+nr;
}

Client Client::operator +(const Client& obj) {
    Client aux;
    aux = *this;
    if(aux.nume != NULL && obj.nume != NULL) {
        char nume2[105];
        strcpy(nume2, aux.nume);
        strcat(nume2, " ");
        strcat(nume2, obj.nume);
        delete[] aux.nume;
        aux.nume = new char[strlen(nume2)+1];
        strcpy(aux.nume, nume2);
    }
    else {
        if(aux.nume == NULL && obj.nume != NULL) {
            aux.nume = new char[strlen(obj.nume)+1];
            strcpy(aux.nume, obj.nume);
        }
    }

    if(aux.prenume != NULL && obj.prenume != NULL) {
        char prenume2[105];
        strcpy(prenume2, aux.prenume);
        strcat(prenume2, " ");
        strcat(prenume2, obj.prenume);
        delete[] aux.prenume;
        aux.prenume = new char[strlen(prenume2)+1];
        strcpy(aux.prenume, prenume2);
    }
    else {
        if(aux.prenume == NULL && obj.prenume != NULL) {
            aux.prenume = new char[strlen(obj.prenume)+1];
            strcpy(aux.prenume, obj.prenume);
        }
    }

    if(aux.gen != obj.gen)
        aux.gen = 'B';
    aux.varsta += obj.varsta;
    return aux;
}


bool Client::operator <(const Client& obj) {
    if(this->varsta < obj.varsta)
        return true;
    return false;
}

bool Client::operator ==(const Client& obj) {
    if(strcmp(this->nume, obj.nume) != 0)
        return false;
    if(strcmp(this->prenume, obj.prenume) != 0)
        return false;
    if(this->gen != obj.gen)
        return false;
    if(this->varsta != obj.varsta)
        return false;
    return true;
}

void Client::setNume(char *nume) {
    if(this->nume != NULL) {
        delete[] this->nume;
        this->nume = NULL;
    }
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
}

void Client::setPrenume(char *prenume) {
    if(this->prenume != NULL) {
        delete[] this->prenume;
        this->prenume = NULL;
    }
    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
}

void Client::setGen(char gen) {
    this->gen = gen;
}

void Client::setVarsta(int varsta) {
    this->varsta = varsta;
}

Client::~Client() {
    if(nume != NULL) {
        delete[] nume;
        nume = NULL;
    }
    if(prenume != NULL) {
        delete[] prenume;
        prenume = NULL;
    }
}



int main()
{
    /*char numeFilm[] = {"Un film"};
    char categorieFilm[] = {"O categorie"};
    int nrBilete[] = {1, 2, 3, 4, 5};
    Film film(numeFilm, categorieFilm, 12, 90.5, 3, nrBilete);

    char numeFilm2[] = {"Un film2"};
    bool locuri[] = {1, 0, 1};
    Rulare rulare(123, numeFilm2, 239, 12.4, 34.2, 1, 3, locuri);

    cout << film << "\n" << rulare << "\n" << film + rulare + film;*/


    Film listaFilme[100];
    Sala listaSali[100];
    Rulare listaRulari[100];
    Client listaClienti[100];
    int contorFilme = 0, contorSali = 0, contorRulari = 0, contorClienti = 0;
    bool ok = true;

    while(ok) {
        int comanda0;
        cout << "\nPentru filme: apasa 0\n";
        cout << "Pentru sali: apasa 1\n";
        cout << "Pentru rulari: apasa 2\n";
        cout << "Pentru clienti: apasa 3\n";
        cout << "Stop: apasa 4\n";
        cin >> comanda0;

        switch(comanda0) {
            case 0: {
                int comanda1;
                cout << "Adauga un film: apasa 0\n";
                cout << "Afiseaza filmele: apasa 1\n";
                cout << "Afiseaza filmul cu cele mai multe bilete vandute: apasa 2\n";
                cout << "Modifica un film: apasa 3\n";
                cout << "Sterge un film: apasa 4\n";
                cin >> comanda1;

                switch(comanda1) {
                    case 0: {
                        Film film;
                        cin >> film;
                        listaFilme[contorFilme] = film;
                        contorFilme ++;
                        break;
                    }
                    case 1: {
                        if(contorFilme == 0)
                            cout << "Nu exista filme\n";
                        else
                            for(int i=0; i<contorFilme; i++)
                                cout << listaFilme[i] << "\n";
                        break;
                    }
                    case 2: {
                        if(contorFilme == 0)
                            cout << "Nu exista filme\n";
                        else {
                            int nrMaxBilete = -1, nrFilm[101], k = 0;
                            for(int i=0; i<contorFilme; i++)
                                if(listaFilme[i].nrBileteVadute() > nrMaxBilete) {
                                    nrMaxBilete = listaFilme[i].nrBileteVadute();
                                    nrFilm[k] = i;
                                    k ++;
                                }
                                else {
                                    if(listaFilme[i].nrBileteVadute() == nrMaxBilete) {
                                        nrFilm[k] = i;
                                        k ++;
                                    }
                                }
                            for(int i=0; i<k; i++) {
                                cout << listaFilme[nrFilm[i]];
                                cout << "Numar bilete vandute: " << nrMaxBilete << "\n\n";
                            }
                        }
                        break;
                    }
                    case 3: {
                        if(contorFilme == 0)
                            cout << "Nu exista filme\n";
                        else {
                            int nrFilm;
                            cout << "Numarul filmului pe care vreti sa il modificati: ";
                            cin >> nrFilm;
                            if(nrFilm<0 || nrFilm>=contorFilme)
                                cout << "Numar invalid\n";
                            else {
                                int comanda2;
                                cout << "Modifica numele: apasa 0\n";
                                cout << "Modifica categoria: apasa 1\n";
                                cout << "Modifica varsta minima: apasa 2\n";
                                cout << "Modifica durata: apasa 3\n";
                                cout << "Modifica numarul de zile: apasa 4\n";
                                cout << "Modifica numarul de bilete vandute intr-o zi: apasa 5\n";
                                cin >> comanda2;

                                switch(comanda2) {
                                    case 0: {
                                        char nume[51];
                                        cout << "Noul nume: ";
                                        cin.ignore();
                                        cin.getline(nume, 51);
                                        listaFilme[nrFilm].setNume(nume);
                                        break;
                                    }
                                    case 1: {
                                        char categorie[51];
                                        cout << "Noua categorie: ";
                                        cin.ignore();
                                        cin.getline(categorie, 51);
                                        listaFilme[nrFilm].setCategorie(categorie);
                                        break;
                                    }
                                    case 2: {
                                        int varstaMinima;
                                        cout << "Noua varsta minima: ";
                                        cin >> varstaMinima;
                                        listaFilme[nrFilm].setVarstaMinima(varstaMinima);
                                        break;
                                    }
                                    case 3: {
                                        float durata;
                                        cout << "Noua durata: ";
                                        cin >> durata;
                                        listaFilme[nrFilm].setDurata(durata);
                                        break;
                                    }
                                    case 4: {
                                        int nrZile;
                                        cout << "Noul numar de zile: ";
                                        cin >> nrZile;
                                        listaFilme[nrFilm].setNrZile(nrZile);
                                        break;
                                    }
                                    case 5: {
                                        int nrBilete, zi;
                                        cout << "Ziua pe care vreti sa o modificati: ";
                                        cin >> zi;
                                        cout << "Noul numar de bilete: ";
                                        cin >> nrBilete;
                                        listaFilme[nrFilm].setNrBileteVanduteZi(nrBilete, zi);
                                        break;
                                    }
                                    default: {
                                        cout << "Comanda invalida\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 4: {
                        if(contorFilme == 0)
                            cout << "Nu exista filme\n";
                        else {
                            int nrFilm;
                            cout << "Numarul filmului pe care vreti sa il stergeti: ";
                            cin >> nrFilm;
                            if(nrFilm<0 || nrFilm>=contorFilme)
                                cout << "Numar invalid\n";
                            else {
                                for(int i=nrFilm; i<contorFilme-1; i++)
                                    listaFilme[i] = listaFilme[i+1];
                                contorFilme --;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Comanda invalida";
                        break;
                    }
                }
                break;
            }
            case 1: {
                int comanda1;
                cout << "Adauga o sala: apasa 0\n";
                cout << "Afiseaza salile: apasa 1\n";
                cout << "Afiseaza toate salile de un anumit tip: apasa 2\n";
                cout << "Modifica o sala: apasa 3\n";
                cout << "Sterge o sala: apasa 4\n";
                cin >> comanda1;

                switch(comanda1) {
                    case 0: {
                        Sala sala;
                        cin >> sala;
                        listaSali[contorSali] = sala;
                        contorSali ++;
                        break;
                    }
                    case 1: {
                        if(contorSali == 0)
                            cout << "Nu exista sali\n";
                        else
                            for(int i=0; i<contorSali; i++)
                                cout << listaSali[i] << "\n";
                        break;
                    }
                    case 2: {
                        if(contorSali == 0)
                            cout << "Nu exista sali\n";
                        else {
                            char tipSala[51];
                            cout << "Tipul de sala pe care il vreti: ";
                            cin.ignore();
                            cin.getline(tipSala, 51);
                            for(int i=0; i<contorSali; i++)
                                if(strcmp(listaSali[i].getTip(), tipSala) == 0)
                                    cout << listaSali[i] << "\n";
                        }
                        break;
                    }
                    case 3: {
                        if(contorSali == 0)
                            cout << "Nu exista sali\n";
                        else {
                            int nrSala;
                            cout << "Numarul salii pe care vreti sa o modificati: ";
                            cin >> nrSala;
                            if(nrSala<0 || nrSala>=contorSali)
                                cout << "Numar invalid\n";
                            else {
                                int comanda2;
                                cout << "Modifica capacitatea: apasa 0\n";
                                cout << "Modifica tipul: apasa 1\n";
                                cin >> comanda2;

                                switch(comanda2) {
                                    case 0: {
                                        int capacitate;
                                        cout << "Noua capacitate: ";
                                        cin >> capacitate;
                                        listaSali[nrSala].setCapacitate(capacitate);
                                        break;
                                    }
                                    case 1: {
                                        char tip[51];
                                        cout << "Noul tip: ";
                                        cin.ignore();
                                        cin.getline(tip, 51);
                                        listaSali[nrSala].setTip(tip);
                                        break;
                                    }
                                    default: {
                                        cout << "Comanda invalida\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 4: {
                        if(contorSali == 0)
                            cout << "Nu exista sali\n";
                        else {
                            int nrSala;
                            cout << "Numarul salii pe care vreti sa o stergeti: \n";
                            cin >> nrSala;
                            if(nrSala<0 || nrSala>=contorSali)
                                cout << "Numar invalid\n";
                            else {
                                for(int i=nrSala; i<contorSali-1; i++)
                                    listaSali[i] = listaSali[i+1];
                                contorSali --;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Comanda invalida\n";
                        break;
                    }
                }
                break;
            }
            case 2: {
                int comanda1;
                cout << "Adauga o rulare: apasa 0\n";
                cout << "Afiseaza rularile: apasa 1\n";
                cout << "Afiseaza rularea cea mai ocupata: apasa 2\n";
                cout << "Modifica o rulare: apasa 3\n";
                cout << "Sterge o rulare: apasa 4\n";
                cin >> comanda1;

                switch(comanda1) {
                    case 0: {
                        Rulare rulare;
                        cin >> rulare;
                        listaRulari[contorRulari] = rulare;
                        contorRulari ++;
                        break;
                    }
                    case 1: {
                        if(contorRulari == 0)
                            cout << "Nu exista rulari\n";
                        else
                            for(int i=0; i<contorRulari; i++)
                                cout << listaRulari[i] << "\n";
                        break;
                    }
                    case 2: {
                        if(contorRulari == 0)
                            cout << "Nu exista rulari\n";
                        else {
                            double procentMax = -1;
                            int nrRulare[101], k = 0;
                            for(int i=0; i<contorRulari; i++)
                                if(listaRulari[i].procentOcupare() > procentMax) {
                                    procentMax = listaRulari[i].procentOcupare();
                                    nrRulare[k] = i;
                                    k ++;
                                }
                                else {
                                    if(listaRulari[i].procentOcupare() == procentMax) {
                                        nrRulare[k] = i;
                                        k ++;
                                    }
                                }
                            for(int i=0; i<k; i++) {
                                cout << listaRulari[nrRulare[i]];
                                cout << "Procent ocupare: " << procentMax << "%\n\n";
                            }
                        }
                        break;
                    }
                    case 3: {
                        if(contorRulari == 0)
                            cout << "Nu exista rulari\n";
                        else {
                            int nrRulare;
                            cout << "Numarul rularii pe care vreti sa o modificati: ";
                            cin >> nrRulare;
                            if(nrRulare<0 || nrRulare>= contorRulari)
                                cout << "Numar invalid\n";
                            else {
                                int comanda2;
                                cout << "Modifica id-ul filmului: apasa 0\n";
                                cout << "Modifica numele filmului: apasa 1\n";
                                cout << "Modifica id-ul salii: apasa 2\n";
                                cout << "Modifica ora de inceput: apasa 3\n";
                                cout << "Modifica ora de sfarsit: apasa 4\n";
                                cout << "Modifica daca mai sunt locuri libere: apasa 5\n";
                                cout << "Modifica numarul de locuri: apasa 6\n";
                                cout << "Modifica locurile: apasa 7\n";
                                cin >> comanda2;

                                switch(comanda2) {
                                    case 0: {
                                        int idFilm;
                                        cout << "Noul id al filmului: ";
                                        cin >> idFilm;
                                        listaRulari[nrRulare].setIdFilm(idFilm);
                                        break;
                                    }
                                    case 1: {
                                        char numeFilm[51];
                                        cout << "Noul nume al filmului: ";
                                        cin.ignore();
                                        cin.getline(numeFilm, 51);
                                        listaRulari[nrRulare].setNumeFilm(numeFilm);
                                        break;
                                    }
                                    case 2: {
                                        int idSala;
                                        cout << "Noul id al salii: ";
                                        cin >> idSala;
                                        listaRulari[nrRulare].setIdSala(idSala);
                                        break;
                                    }
                                    case 3: {
                                        double oraInceput;
                                        cout << "Noua ora de inceput: ";
                                        cin >> oraInceput;
                                        listaRulari[nrRulare].setOraInceput(oraInceput);
                                        break;
                                    }
                                    case 4: {
                                        double oraSfarsit;
                                        cout << "Noua ora de sfarsit: ";
                                        cin >> oraSfarsit;
                                        listaRulari[nrRulare].setOraSfarsit(oraSfarsit);
                                        break;
                                    }
                                    case 5: {
                                        bool locuriLibere;
                                        cout << "Mai exista locuri libere (1 pt da, 0 pt nu): ";
                                        cin >> locuriLibere;
                                        listaRulari[nrRulare].setLocuriLibere(locuriLibere);
                                        break;
                                    }
                                    case 6: {
                                        int nrLocuri;
                                        cout << "Noul numar de locuri: ";
                                        cin >> nrLocuri;
                                        listaRulari[nrRulare].setNrLocuri(nrLocuri);
                                        break;
                                    }
                                    case 7: {
                                        bool ocupat;
                                        int loc;
                                        cout << "Numarul locului pe care vreti sa il modificati: ";
                                        cin >> loc;
                                        cout << "Este ocupat (1) sau nu (0): ";
                                        cin >> ocupat;
                                        listaRulari[nrRulare].setLocuri(ocupat, loc);
                                        break;
                                    }
                                    default: {
                                        cout << "Comanda invalida\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 4: {
                        if(contorRulari == 0)
                            cout << "Nu exista rulari\n";
                        else {
                            int nrRulare;
                            cout << "Numarul rularii pe care vreti sa o stergeti: \n";
                            cin >> nrRulare;
                            if(nrRulare<0 || nrRulare>=contorRulari)
                                cout << "Numar invalid\n";
                            else {
                                for(int i=nrRulare; i<contorRulari-1; i++)
                                    listaRulari[i] = listaRulari[i+1];
                                contorRulari --;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Comanda invalida\n";
                        break;
                    }
                }
                break;
            }
            case 3: {
                int comanda1;
                cout << "Adauga un client: apasa 0\n";
                cout << "Afiseaza clientii: apasa 1\n";
                cout << "Afiseaza clientii majori: apasa 2\n";
                cout << "Afiseaza clientii minori: apasa 3\n";
                cout << "Modifica un client: apasa 4\n";
                cout << "Sterge un client: apasa 5\n";
                cin >> comanda1;

                switch(comanda1) {
                    case 0: {
                        Client client;
                        cin >> client;
                        listaClienti[contorClienti] = client;
                        contorClienti ++;
                        break;
                    }
                    case 1: {
                        if(contorClienti == 0)
                            cout << "Nu exista clienti\n";
                        else
                            for(int i=0; i<contorClienti; i++)
                                cout << listaClienti[i] << "\n";
                        break;
                    }
                    case 2: {
                        if(contorClienti == 0)
                            cout << "Nu exista clienti\n";
                        else 
                            for(int i=0; i<contorClienti; i++)
                                if(listaClienti[i].major())
                                    cout << listaClienti[i] << "\n";
                        break;
                    }
                    case 3: {
                        if(contorClienti == 0)
                            cout << "Nu exista clienti\n";
                        else
                            for(int i=0; i<contorClienti; i++)
                                if(!listaClienti[i].major())
                                    cout << listaClienti[i] << "\n";
                        break;
                    }
                    case 4: {
                        if(contorClienti == 0)
                            cout << "Nu exista clienti\n";
                        else {
                            int nrClient;
                            cout << "Numarul clientului pe care vreti sa il modificati: ";
                            cin >> nrClient;
                            if(nrClient<0 || nrClient>=contorClienti)
                                cout << "Numar invalid\n";
                            else {
                                int comanda2;
                                cout << "Modifica numele: apasa 0\n";
                                cout << "Modifica prenumele: apasa 1\n";
                                cout << "Modifica genul: apasa 2\n";
                                cout << "Modifica varsta: apasa 3\n";
                                cin >> comanda2;

                                switch(comanda2) {
                                    case 0: {
                                        char nume[51];
                                        cout << "Noul nume: ";
                                        cin.ignore();
                                        cin.getline(nume, 51);
                                        listaClienti[nrClient].setNume(nume);
                                        break;
                                    }
                                    case 1: {
                                        char prenume[51];
                                        cin.ignore();
                                        cout << "Noul prenume: ";
                                        cin.getline(prenume, 51);
                                        listaClienti[nrClient].setPrenume(prenume);
                                        break;
                                    }
                                    case 2: {
                                        char gen;
                                        cout << "Noul gen: ";
                                        cin >> gen;
                                        listaClienti[nrClient].setGen(gen);
                                        break;
                                    }
                                    case 3: {
                                        int varsta;
                                        cout << "Noua varsta: ";
                                        cin >> varsta;
                                        listaClienti[nrClient].setVarsta(varsta);
                                        break;
                                    }
                                    default: {
                                        cout << "Comanda invalida\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 5: {
                        if(contorClienti == 0)
                            cout << "Nu exista clienti\n";
                        else {
                            int nrClient;
                            cout << "Numarul clientului pe care vreti sa il stergeti: ";
                            cin >> nrClient;
                            if(nrClient<0 || nrClient>=contorClienti)
                                cout << "Numar invalid\n";
                            else {
                                for(int i=nrClient; i<contorClienti-1; i++)
                                    listaClienti[i] = listaClienti[i+1];
                                contorClienti --;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Comanda invalida\n";
                        break;
                    }
                }
                break;
            }
            case 4: {
                ok = false;
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