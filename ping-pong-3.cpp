#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <limits>
#include <time.h>
#include <typeinfo>
#include <random>
#include <type_traits>
using namespace std;
std::knuth_b rand_engine;

const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();

template <class T> 
T getInput(const string& prompt, istream& in) {
    T input;
    bool ok = false;
    while (!ok) {
        try {
            cout << prompt;
            in >> input;
            if (in.fail())
                throw 0;
            else
                ok = true;
        }
        catch(int) {
            in.clear();
            in.ignore(MAX, '\n');
            cout << "\nInput invalid, incercati din nou\n";
        }
    }
    return input;
}

template <typename T>
typename enable_if<is_arithmetic<T>::value, bool>::type
verifyInput(T input, float minim, float maxim) {
    try {
        if (input < minim)
            throw 'a';
        if (input > maxim)
            throw 1.2;
    }
    catch(char) {
        cout << "Numarul este prea mic. Incercati din nou\n";
        return false;
    }
    catch(double) {
        cout << "Numarul este prea mare. Incercati din nou\n";
        return false;
    }
    return true;
}

template <typename T>
typename enable_if<!is_arithmetic<T>::value, bool>::type
verifyInput(T input, float minim, float maxim) {
    cout << "Input-ul nu este un numar\n";
    return false;
}


bool succes(double prob) {
    srand(time(0));
    bernoulli_distribution d(prob);
    return d(rand_engine);
}


class Efect {
protected:
    int intensitate;
public:
    // constructori
    Efect() {this->intensitate = 0;}
    Efect(int intensitate) {this->intensitate = intensitate;}
    Efect(const Efect& obj) {this->intensitate = obj.intensitate;};

    // operatori
    Efect& operator=(const Efect& obj) {
        if (this != &obj)
            this->intensitate = obj.intensitate; 
        return *this;
    }

    friend istream& operator>>(istream& in, Efect& obj) {
        bool ok = false;
        while (!ok) {
            obj.intensitate = getInput<float>("Intensitate: ", in);
            ok = verifyInput<float>(obj.intensitate, 0, 100);
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Efect& obj) {
        out << "Intensitate: " << obj.intensitate << "\n";
        return out;
    }

    // setters
    void setIntensitate(int intensitate) {this->intensitate = intensitate;}

    // getters
    int getIntensitate() const {return this->intensitate;}

    // metode
    virtual void metoda() {cout << 0;}

    // destructor
    virtual ~Efect() {};
};


class Backspin: public Efect {
public:
    // constructori
    Backspin(): Efect() {};
    Backspin(int intensitate): Efect(intensitate) {};
    Backspin(const Backspin& obj): Efect(obj) {};

    // operatori
    Backspin& operator=(const Backspin& obj) {
        if (this != &obj) {
            Efect::operator=(obj);
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Backspin& obj) {in >> dynamic_cast<Efect&>(obj); return in;}
    friend ostream& operator<<(ostream& out, const Backspin& obj) {out << "Efect: backspin\n" << dynamic_cast<const Efect&>(obj); return out;}

    // metode
    // bool suficient(Efect* efect);
    void metoda() {cout << 1;}

    // destructor
    ~Backspin() {};
};


class Topspin: public Efect {
public:
    // constructori
    Topspin(): Efect() {};
    Topspin(int intensitate): Efect(intensitate) {};
    Topspin(const Topspin& obj): Efect(obj) {};

    // operatori
    Topspin& operator=(const Topspin& obj) {
        if (this != &obj) {
            Efect::operator=(obj);
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Topspin& obj) {in >> dynamic_cast<Efect&>(obj); return in;}
    friend ostream& operator<<(ostream& out, const Topspin& obj) {out << "Efect: topspin\n" << dynamic_cast<const Efect&>(obj); return out;}

    // metode
    // bool suficient(Efect* efect);
    void metoda() {cout << 2;}

    // destructor
    ~Topspin() {};
};



class Serva {
    string nume;
    Efect* efect;
public:
    // constructori
    Serva();
    Serva(string nume, Efect* efect);
    Serva(const Serva& obj);

    // operatori
    Serva& operator=(const Serva& obj);
    friend istream& operator>>(istream& in, Serva& obj);
    friend ostream& operator<<(ostream& out, const Serva& obj);
    bool operator<(const Serva& obj) const {return this->nume < obj.nume;}

    // setters
    void setNume(string nume) {this->nume = nume;}
    void setEfect(Efect* efect) {*this->efect = *efect;}

    // getters
    string getNume() const {return this->nume;}
    Efect* getEfect() const {return this->efect;}

    // destructor
    ~Serva();
};

Serva::Serva() {
    this->nume = "";
    this->efect = new Efect();
}

Serva::Serva(string nume, Efect* efect) {
    this->nume = nume;
    this->efect = new Efect();
    if (dynamic_cast<Backspin*>(efect) != nullptr)
        this->efect = new Backspin();
    if (dynamic_cast<Topspin*>(efect) != nullptr)
        this->efect = new Topspin();
    *(this->efect) = *(efect);
}

Serva::Serva(const Serva& obj) {
    this->nume = obj.nume;
    this->efect = new Efect();
    if (dynamic_cast<Backspin*>(obj.efect) != nullptr)
        this->efect = new Backspin();
    if (dynamic_cast<Topspin*>(obj.efect) != nullptr)
        this->efect = new Topspin();
    *(this->efect) = *(obj.efect);
}

Serva& Serva::operator=(const Serva& obj) {
    if (this != &obj) {
        this->nume = obj.nume;
        if (dynamic_cast<Backspin*>(obj.efect) != nullptr)
            this->efect = new Backspin();
        if (dynamic_cast<Topspin*>(obj.efect) != nullptr)
            this->efect = new Topspin();
        *(this->efect) = *(obj.efect);
    }
    return *this;
}

istream& operator>>(istream& in, Serva& obj) {
    obj.nume = getInput<string>("Nume: ", in);
    bool tip;
    tip = getInput<bool>("Backspin: apasa 0\nTopspin: apasa 1\n", in);
    if (!tip) {
        obj.efect = new Backspin();
    }
    else {
        obj.efect = new Topspin();
    }
    in >> *(obj.efect);
    return in;
}

ostream& operator<<(ostream& out, const Serva& obj) {
    out << "Nume: " << obj.nume << "\n";
    try {
        Topspin* topspin = dynamic_cast<Topspin*>(obj.efect);
        if (topspin != nullptr)
            out << *topspin;
        else
            throw(2.3);
    }
    catch(double) {
        try {
            Backspin* backspin = dynamic_cast<Backspin*>(obj.efect);
            if (backspin != nullptr)
                out << *backspin;
            else
                throw(2.3);
        }
        catch(double) {
            out << "Eroare\n";
            // out << "Pointer afisare: " << obj.efect << "\n";
        }
    }
    return out;
}

Serva::~Serva() {
    if (this->efect != NULL) {
        delete this->efect;
        this->efect = NULL;
    }
}



class Lovitura {
protected:
    string nume;
    int viteza;
public:
    // constructori
    Lovitura();
    Lovitura(string nume, int viteza);
    Lovitura(const Lovitura& obj);

    // operatori
    Lovitura& operator=(const Lovitura& obj);
    friend istream& operator>>(istream& in, Lovitura& obj);
    friend ostream& operator<<(ostream& out, const Lovitura& obj);
    bool operator<(const Lovitura& obj) const {return this->nume < obj.nume;}
    bool potrivit(const Efect* efect) const;

    // getters
    int getViteza() const {return this->viteza;}

    // destructor
    virtual ~Lovitura() {}
};

Lovitura::Lovitura() {
    this->nume = ""; 
    this->viteza = 0;
}

Lovitura::Lovitura(string nume, int viteza) {
    this->nume = nume; 
    this->viteza = viteza;
}

Lovitura::Lovitura(const Lovitura& obj) {
    this->nume = obj.nume; 
    this->viteza = obj.viteza;
}

Lovitura& Lovitura::operator=(const Lovitura& obj) {
    if (this != &obj) {
        this->nume = obj.nume; 
        this->viteza = obj.viteza;
    }
    return *this;
}

istream& operator>>(istream& in, Lovitura& obj) {
    obj.nume = getInput<string>("Nume: ", in);
    bool ok = false;
    while (!ok) {
        obj.viteza = getInput<int>("Viteza: ", in);
        ok = verifyInput<int>(obj.viteza, 0, 100);
    }
    return in;
}

ostream& operator<<(ostream& out, const Lovitura& obj) {
    out << "Nume: " << obj.nume << "\n";
    out << "Viteza: " << obj.viteza << "\n";
    return out;
}

bool Lovitura::potrivit(const Efect* efect) const {
    if (efect->getIntensitate() > 0) {
        if (dynamic_cast<const Topspin*>(efect) != nullptr)
            cout << "\033[31m" << "Mingea a iesit in afara mesei! :(\n" << "\033[0m";
        if (dynamic_cast<const Backspin*>(efect) != nullptr)
            cout << "\033[31m" << "Mingea a intrat in fileu! :(\n" << "\033[0m";
        return false;
    }
    return true;
}


class LovituraAtac: public Lovitura {
public:
    // constructori
    LovituraAtac(): Lovitura() {};
    LovituraAtac(string nume, int viteza): Lovitura(nume, viteza) {};
    LovituraAtac(const LovituraAtac& obj): Lovitura(obj) {};

    // operatori
    LovituraAtac& operator=(const LovituraAtac& obj) {
        if (this != &obj) {
            Lovitura::operator=(obj);
        }
        return *this;
    }
    
    friend istream& operator>>(istream& in, LovituraAtac& obj) {in >> dynamic_cast<Lovitura&>(obj); return in;}
    friend ostream& operator<<(ostream& out, const LovituraAtac& obj) {out << dynamic_cast<const Lovitura&>(obj); return out;}

    // destructor
    virtual ~LovituraAtac() = 0;
};

LovituraAtac::~LovituraAtac() {}


class Loop: public LovituraAtac {
    Topspin topspin;
public:
    // constructori
    Loop();
    Loop(string nume, int viteza, Topspin topspin);
    Loop(const Loop& obj);

    // operatori
    Loop& operator=(const Loop& obj);
    friend istream& operator>>(istream& in, Loop& obj);
    friend ostream& operator<<(ostream& out, const Loop& obj);
    bool potrivit(const Efect* efect) const;

    // getters
    int getIntensitateEfect() const {return this->topspin.getIntensitate();}

    // destructor
    ~Loop();
};

Loop::Loop(): LovituraAtac() {
    this->topspin = *(new Topspin());
}

Loop::Loop(string nume, int viteza, Topspin topspin): LovituraAtac(nume, viteza) {
    this->topspin = topspin;
}

Loop::Loop(const Loop& obj): LovituraAtac(obj) {
    this->topspin = obj.topspin;
}

Loop& Loop::operator=(const Loop& obj) {
    if (this != &obj) {
        LovituraAtac::operator=(obj);
        this->topspin = obj.topspin;
    }
    return *this;
}

istream& operator>>(istream& in, Loop& obj) {
    in >> dynamic_cast<LovituraAtac&>(obj); 
    in >> obj.topspin;
    return in;
}

ostream& operator<<(ostream& out, const Loop& obj) {
    out << dynamic_cast<const LovituraAtac&>(obj); 
    out << obj.topspin;
    return out;
}

bool Loop::potrivit(const Efect* efect) const {
    if (dynamic_cast<const Backspin*>(efect) != nullptr) {
        int intensitate = dynamic_cast<const Backspin*>(efect)->getIntensitate();
        if (intensitate - this->topspin.getIntensitate() > 20) {
            cout << "\033[31m" << "Mingea a intrat in fileu! :(\n" << "\033[0m";
            return false;
        }
    }
    return true;
}

Loop::~Loop() {}


class Smash: public LovituraAtac {
    int putere;
public:
    // constructori
    Smash(): LovituraAtac() {};
    Smash(string nume, int viteza, int putere): LovituraAtac(nume, viteza) {this->putere = putere;}
    Smash(const Smash& obj): LovituraAtac(obj) {this->putere = obj.putere;}

    // operatori
    Smash& operator=(const Smash& obj);
    friend istream& operator>>(istream& in, Smash& obj);
    friend ostream& operator<<(ostream& out, const Smash& obj);
    bool potrivit(const Efect* efect) const;

    // getters
    int getViteza() const {return this->viteza + this->putere / 2;}

    // destructor
    ~Smash() {}
};

Smash& Smash::operator=(const Smash& obj) {
    if (this != &obj) {
        LovituraAtac::operator=(obj);
        this->putere = obj.putere;
    }
    return *this;
}

istream& operator>>(istream& in, Smash& obj) {
    in >> dynamic_cast<LovituraAtac&>(obj); 
    bool ok = false;
    while (!ok) {
        obj.putere = getInput<int>("Putere: ", in);
        ok = verifyInput<int>(obj.putere, 0, 100);
    }
    return in;
}

ostream& operator<<(ostream& out, const Smash& obj) {
    out << dynamic_cast<const LovituraAtac&>(obj); 
    out << "Putere: " << obj.putere << "\n";
    return out;
}

bool Smash::potrivit(const Efect* efect) const {
    int intensitate = 0;
    if (dynamic_cast<const Topspin*>(efect) != nullptr) {
        intensitate = dynamic_cast<const Topspin*>(efect)->getIntensitate();
        if (intensitate - this->putere > 20) {
            cout << "\033[31m" << "Mingea a iesit in afara mesei! :(\n" << "\033[0m";
            return false;
        }
    }
    if (dynamic_cast<const Backspin*>(efect) != nullptr) {
        intensitate = dynamic_cast<const Backspin*>(efect)->getIntensitate();
        if (intensitate - this->putere > 20) {
            cout << "\033[31m" << "Mingea a intrat in fileu! :(\n" << "\033[0m";
            return false;
        }
    }
    return true;
}


class LovituraAparare: public Lovitura {
public:
    // constructori
    LovituraAparare(): Lovitura() {};
    LovituraAparare(string nume, int viteza): Lovitura(nume, viteza) {};
    LovituraAparare(const LovituraAparare& obj): Lovitura(obj) {};

    // operatori
    LovituraAparare& operator=(const LovituraAparare& obj) {
        if (this != &obj) {
            Lovitura::operator=(obj);
        }
        return *this;
    }
    
    friend istream& operator>>(istream& in, LovituraAparare& obj) {in >> dynamic_cast<Lovitura&>(obj); return in;}
    friend ostream& operator<<(ostream& out, const LovituraAparare& obj) {out << dynamic_cast<const Lovitura&>(obj); return out;}

    // destructor
    virtual ~LovituraAparare() = 0;
};

LovituraAparare::~LovituraAparare() {}


class Slice: public LovituraAparare {
    Backspin backspin;
public:
    // constructori
    Slice();
    Slice(string nume, int viteza, Backspin backspin);
    Slice(const Slice& obj);

    // operatori
    Slice& operator=(const Slice& obj);
    friend istream& operator>>(istream& in, Slice& obj);
    friend ostream& operator<<(ostream& out, const Slice& obj);
    bool potrivit(const Efect* efect) const;

    // getters
    int getIntensitateEfect() const {return this->backspin.getIntensitate();}

    // destructor
    ~Slice();
};

Slice::Slice(): LovituraAparare() {
    this->backspin = *(new Backspin());
}

Slice::Slice(string nume, int viteza, Backspin backspin): LovituraAparare(nume, viteza) {
    this->backspin = backspin;
}

Slice::Slice(const Slice& obj): LovituraAparare(obj) {
    this->backspin = obj.backspin;
}

Slice& Slice::operator=(const Slice& obj) {
    if (this != &obj) {
        LovituraAparare::operator=(obj);
        this->backspin = obj.backspin;
    }
    return *this;
}

istream& operator>>(istream& in, Slice& obj) {
    in >> dynamic_cast<LovituraAparare&>(obj);
    in >> obj.backspin;
    return in;
}

ostream& operator<<(ostream& out, const Slice& obj) {
    out << dynamic_cast<const LovituraAparare&>(obj);
    out << obj.backspin;
    return out;
}

bool Slice::potrivit(const Efect* efect) const {
    if (dynamic_cast<const Topspin*>(efect) != nullptr) {
        int intensitate = dynamic_cast<const Topspin*>(efect)->getIntensitate();
        if (intensitate - this->backspin.getIntensitate() > 20) {
            cout << "\033[31m" << "Mingea a iesit in afara mesei! :(\n" << "\033[0m";
            return false;
        }
    }
    return true;
}

Slice::~Slice() {}


class Block: public LovituraAparare {
    double amplificare;
public:
    // constructori
    Block(): LovituraAparare() {};
    Block(string nume, int viteza, double amplificare): LovituraAparare(nume, viteza) {this->amplificare = amplificare;}
    Block(const Block& obj): LovituraAparare(obj) {this->amplificare = obj.amplificare;}

    // operatori
    Block& operator=(const Block& obj);
    friend istream& operator>>(istream& in, Block& obj);
    friend ostream& operator<<(ostream& out, const Block& obj);
    bool potrivit(const Efect* efect) const;

    // getters
    int getAmplificare() const {return this->amplificare;}

    // destructor
    ~Block() {}
};

Block& Block::operator=(const Block& obj) {
    if (this != &obj) {
        LovituraAparare::operator=(obj);
        this->amplificare = obj.amplificare;
    }
    return *this;
}

istream& operator>>(istream& in, Block& obj) {
    in >> dynamic_cast<LovituraAparare&>(obj);
    bool ok = false;
    while (!ok) {
        obj.amplificare = getInput<double>("Amplificare: ", in);
        ok = verifyInput<double>(obj.amplificare, 0.5, 1.5);
    }
    return in;
}

ostream& operator<<(ostream& out, const Block& obj) {
    out << dynamic_cast<const LovituraAparare&>(obj);
    out << "Amplificare: " << obj.amplificare << "\n";
    return out;
}

bool Block::potrivit(const Efect* efect) const {
    int intensitate = 0;
    if (dynamic_cast<const Topspin*>(efect) != nullptr) {
        intensitate = dynamic_cast<const Topspin*>(efect)->getIntensitate();
        if (intensitate - this->amplificare > 50) {
            cout << "\033[31m" << "Mingea a iesit in afara mesei! :(\n" << "\033[0m";
            return false;
        }
    }

    if (dynamic_cast<const Backspin*>(efect) != nullptr) {
        cout << "\033[31m" << "Mingea a intrat in fileu! :(\n" << "\033[0m";
        return false;
    }
    return true;
}


class Jucator {
protected:
    string nume;
    double puncte;
    int viteza;
    vector <Serva*> serve;
    vector <double> probServe;
    map <Lovitura, double> lovituri;
    set <string> strigateVictorie;
    list <string> tipFete;

public:
    // constructori
    Jucator();
    Jucator(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, list <string> tipFete);
    Jucator(const Jucator& obj);

    // operatori
    Jucator& operator=(const Jucator& obj);
    friend istream& operator>>(istream& in, Jucator& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Jucator& obj) {return obj.afisare(out);}

    // metode
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    void showServe(ostream& out) const;
    pair <const Serva*, double> serveste() const;
    void showLovituri(ostream& out) const;
    pair <const Lovitura*, double> lovesteMingea() const;
    bool rapid(int viteza);
    bool areStrigate() const;
    bool existaStrigat(string strigat) const;
    void striga() const;

    // getters
    string getNume() const {return this->nume;}
    int getPuncte() const {return this->puncte;}

    // setters
    void updatePuncte(int nr) {this->puncte += nr;}
    void setPuncte(int puncte) {this->puncte = puncte;}

    // destructor
    virtual ~Jucator() {}
};

Jucator::Jucator() {
    this->nume = "";
    this->puncte = 0;
    this->viteza = 0;
    this->serve = {};
    this->lovituri = {};
    this->strigateVictorie = {};
    this->tipFete = {};
}

Jucator::Jucator(string nume, double puncte, int viteza, vector<Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, list <string> tipFete) {
    this->nume = nume;
    this->puncte = puncte;
    this->viteza = viteza;
    for (int i = 0; i < serve.size(); i ++) {
        this->serve.push_back(new Serva());
        *this->serve.back() = *serve[i];
    }
    this->probServe = probServe;
    this->lovituri = lovituri;
    this->strigateVictorie = strigateVictorie;
    this->tipFete = tipFete;
}

Jucator::Jucator(const Jucator& obj) {
    this->nume = obj.nume;
    this->puncte = obj.puncte;
    this->viteza = obj.viteza;
    for (int i = 0; i < obj.serve.size(); i ++) {
        this->serve.push_back(new Serva());
        *this->serve.back() = *obj.serve[i];
    }
    this->probServe = obj.probServe;
    this->lovituri = obj.lovituri;
    this->strigateVictorie = obj.strigateVictorie;
    this->tipFete = obj.tipFete;
}

Jucator& Jucator::operator=(const Jucator& obj) {
    if (this != &obj) {
        this->nume = obj.nume;
        this->puncte = obj.puncte;
        this->viteza = obj.viteza;
        for (int i = 0; i < obj.serve.size(); i ++) {
            this->serve.push_back(new Serva());
            *this->serve.back() = *obj.serve[i];
        }
        this->probServe = obj.probServe;
        this->lovituri = obj.lovituri;
        this->strigateVictorie = obj.strigateVictorie;
        this->tipFete = obj.tipFete;
    }
    return *this;
}

istream& Jucator::citire(istream& in) {
    this->nume = getInput<string>("Nume: ", in);

    bool ok = false;
    while (!ok) {
        this->puncte = getInput<double>("Puncte: ", in);
        ok = verifyInput<double>(this->puncte, 0, 1000);
    }

    ok = false;
    while (!ok) {
        this->viteza = getInput<int>("Viteza: ", in);
        ok = verifyInput<int>(this->viteza, 0, 100);
    }

    bool op = 0;
    while (!op) {
        op = getInput<bool>("Adauga o serva: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            this->serve.push_back(new Serva());
            in >> *(this->serve.back());
            
            bool ok = false;
            this->probServe.push_back(*new double);
            while (!ok) {
                this->probServe.back() = getInput<double>("Probabilitate reusita: ", in);
                ok = verifyInput<double>(this->probServe.back(), 0, 1);
            }
        }
    }

    op = 0;
    while (!op) {
        op = getInput<bool>("Adauga o lovitura: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            Lovitura lovitura;
            in >> lovitura;

            bool ok = false;
            double prob;
            while (!ok) {
                prob = getInput<double>("Probabilitate reusita: ", in);
                ok = verifyInput<double>(prob, 0, 1);
            }
            this->lovituri.insert(pair<Lovitura, double>(lovitura, prob));
        }
    }

    op = 0;
    while (!op) {
        op = getInput<bool>("Adauga un strigat de victorie: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            string strigat = getInput<string>("Strigat: ", in);
            this->strigateVictorie.insert(strigat);
        }
    }

    op = 0;
    while (!op) {
        op = getInput<bool>("Adauga un tip de fata: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            string fata = getInput<string>("Tip de fata: ", in);
            this->tipFete.push_back(fata);
        }
    }

    return in;
}
    
ostream& Jucator::afisare(ostream& out) const {
    out << "Nume: " << this->nume << "\n";
    out << "Puncte: " << this->puncte << "\n";
    out << "Viteza: " << this->viteza << "\n";
    this->showServe(out);
    this->showLovituri(out);
    out << "Strigate victorie: \n";
    for (auto itr = this->strigateVictorie.begin(); itr != this->strigateVictorie.end(); itr ++)
        out << *itr << "\n";
    out << "Tipuri fete: ";
    for (auto i : this->tipFete) {
        cout << i << " ";
    }
    return out;
}

void Jucator::showServe(ostream& out) const {
    out << "\nServe: \n";
    for (int i = 0; i < this->serve.size(); i ++)
        out << *this->serve[i]  << "Probabilitate reusita: " << this->probServe[i] << "\n\n";
}

pair <const Serva*, double> Jucator::serveste() const {
    this->showServe(cout);
    bool ok = false;
    int index;
    while(!ok) {
        index = getInput<int>("Alege o serva (index-ul ei): ", cin);
        ok = verifyInput<int>(index, 0, this->serve.size()-1);
    }
    return {this->serve[index], this->probServe[index]};
}

void Jucator::showLovituri(ostream& out) const {
    out << "\nLovituri: \n";
    for (auto itr = this->lovituri.begin(); itr != this->lovituri.end(); itr ++)
        out << itr->first << "Probabilitate reusita: " << itr->second << "\n\n";
}

pair <const Lovitura*, double> Jucator::lovesteMingea() const {
    this->showLovituri(cout);

    if (this->lovituri.empty()) {
        cout << "Nu ai lovituri!\n";
        return {nullptr, 0};
    }

    bool ok = false;
    int index;
    while (!ok) {
        index = getInput<int>("Alege o lovitura (index-ul ei): ", cin);
        ok = verifyInput<int>(index, 0, this->lovituri.size() - 1);
    }

    auto it = this->lovituri.begin();
    advance(it, index);

    const Lovitura* selectedLovitura = &(it->first);
    double probabilitateReusita = it->second;

    return {selectedLovitura, probabilitateReusita};
}

bool Jucator::rapid(int viteza) {
    if (viteza - this->viteza <= 25)
        return true;
    return false;
}

bool Jucator::existaStrigat(string strigat) const {
    if (this->strigateVictorie.find(strigat) != this->strigateVictorie.end())
        return true;
    cout << "Nu ai acest strigat\n";
    return false;
}

void Jucator::striga() const {
    bool strigat = getInput<bool>("Doresti un strigat de victorie? (0 pt nu, 1 pt da) ", cin);
    if (strigat) {
        if (!this->strigateVictorie.empty()) {
            bool exista = 0;
            string s;
            while (!exista) {
                s = getInput<string>("Strigat: ", cin);
                exista = this->existaStrigat(s);
            }
            cout << this->nume << ": " << "\033[1m" << s << "\033[0m" << "\n";
        }
        else {
            cout << "Imi pare rau, dar nu ai strigate\n";
        }
    }
}


class Atacant: virtual public Jucator {
protected:
    vector <LovituraAtac*> lovituriAtac;
    vector <double> probAtac;
public:
    // constructori
    Atacant();
    Atacant(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
            list <string> tipFete, vector <LovituraAtac*> lovituriAtac, vector <double> probAtac);
    Atacant(const Atacant& obj);

    // operatori
    Atacant& operator=(const Atacant& obj);
    friend istream& operator>>(istream& in, Atacant& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Atacant& obj) {return obj.afisare(out);}
    
    // metode
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    void showLovituri(ostream& out) const;
    pair <const Lovitura*, double> lovesteMingea() const;

    // destructor
    ~Atacant();
};

Atacant::Atacant(): Jucator() {
    this->lovituriAtac = {};
    this->probAtac = {};
}

Atacant::Atacant(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
                list <string> tipFete, vector <LovituraAtac*> lovituriAtac, vector <double> probAtac): Jucator(nume, puncte, viteza, serve, probServe, lovituri, strigateVictorie, tipFete) {
    for (int i = 0; i < lovituriAtac.size(); i ++) {
        if (dynamic_cast<Loop*>(lovituriAtac[i]) != nullptr) {
            this->lovituriAtac.push_back(new Loop());
            *dynamic_cast<Loop*>(this->lovituriAtac.back()) = *dynamic_cast<Loop*>(lovituriAtac[i]);
        }

        if (dynamic_cast<Smash*>(lovituriAtac[i]) != nullptr) {
            this->lovituriAtac.push_back(new Smash());
            *dynamic_cast<Smash*>(this->lovituriAtac.back()) = *dynamic_cast<Smash*>(lovituriAtac[i]);
        }
    }
    this->probAtac = probAtac;
}

Atacant::Atacant(const Atacant& obj): Jucator(obj) {
    for (int i = 0; i < obj.lovituriAtac.size(); i ++) {
        if (dynamic_cast<Loop*>(obj.lovituriAtac[i]) != nullptr) {
            this->lovituriAtac.push_back(new Loop());
            *dynamic_cast<Loop*>(this->lovituriAtac.back()) = *dynamic_cast<Loop*>(obj.lovituriAtac[i]);
        }

        if (dynamic_cast<Smash*>(obj.lovituriAtac[i]) != nullptr) {
            this->lovituriAtac.push_back(new Smash());
            *dynamic_cast<Smash*>(this->lovituriAtac.back()) = *dynamic_cast<Smash*>(obj.lovituriAtac[i]);
        }
    }
    this->probAtac = obj.probAtac;
}

Atacant& Atacant::operator=(const Atacant& obj) {
    if (this != &obj) {
        Jucator::operator=(obj);
        for (int i = 0; i < obj.lovituriAtac.size(); i ++) {
            if (dynamic_cast<Loop*>(obj.lovituriAtac[i]) != nullptr) {
                this->lovituriAtac.push_back(new Loop());
                *dynamic_cast<Loop*>(this->lovituriAtac.back()) = *dynamic_cast<Loop*>(obj.lovituriAtac[i]);
            }

            if (dynamic_cast<Smash*>(obj.lovituriAtac[i]) != nullptr) {
                this->lovituriAtac.push_back(new Smash());
                *dynamic_cast<Smash*>(this->lovituriAtac.back()) = *dynamic_cast<Smash*>(obj.lovituriAtac[i]);
            }
        }
        this->probAtac = obj.probAtac;
    }
    return *this;
}

istream& Atacant::citire(istream& in) {
    Jucator::citire(in);
    bool op = 0;
    while (!op) {
        op = getInput<bool>("Adauga o lovitura de atac: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            bool tip;
            tip = getInput<bool>("Loop: apasa 0\nSmash: apasa 1\n", in);
            if (!tip) {
                this->lovituriAtac.push_back(new Loop());
                in >> *dynamic_cast<Loop*>(this->lovituriAtac.back());
            }
            else {
                this->lovituriAtac.push_back(new Smash());
                in >> *dynamic_cast<Smash*>(this->lovituriAtac.back());
            }

            bool ok = false;
            this->probAtac.push_back(*new double);
            while (!ok) {
                this->probAtac.back() = getInput<double>("Probabilitate reusita: ", in);
                ok = verifyInput<double>(this->probAtac.back(), 0, 1);
            }
        }
    }
    return in;
}

ostream& Atacant::afisare(ostream& out) const {
    Jucator::afisare(out);
    this->showLovituri(out);
    return out;
}

void Atacant::showLovituri(ostream& out) const {
    out << "Lovituri atac:\n";
    for (int i = 0; i < this->lovituriAtac.size(); i ++) {
        if (dynamic_cast<Loop*>(this->lovituriAtac[i]) != nullptr) {
            out << *dynamic_cast<Loop*>(this->lovituriAtac[i]);
        }
        else {
            if (dynamic_cast<Smash*>(this->lovituriAtac[i]) != nullptr) {
                out << *dynamic_cast<Smash*>(this->lovituriAtac[i]);
            }
            else {
                out << "Eroare";
            }
        }
        out << "Probabilitate reusita: " << this->probAtac[i] << "\n\n";
    }
}

pair <const Lovitura*, double> Atacant::lovesteMingea() const {
    bool tip;
    tip = getInput<bool>("Lovitura simpla: apasa 0\nLovitura atac: apasa 1\n", cin);
    if (!tip) {
        return dynamic_cast<const Jucator*>(this)->lovesteMingea();
    }
    else {
        this->showLovituri(cout);

        if (this->lovituriAtac.empty()) {
            cout << "Nu ai lovituri de atac!\n";
            return {nullptr, 0};
        }

        bool ok = false;
        int index;
        while(!ok) {
            index = getInput<int>("Alege o lovitura (index-ul ei): ", cin);
            ok = verifyInput<int>(index, 0, this->lovituriAtac.size()-1);
        }

        return {this->lovituriAtac[index], this->probAtac[index]};
    }
}

Atacant::~Atacant() {
    for (int i = 0; i < this->lovituriAtac.size(); i ++) {
        if (this->lovituriAtac[i] != NULL) {
            delete this->lovituriAtac[i];
            this->lovituriAtac[i] = NULL;
        }
    }
}


class Aparator: virtual public Jucator {
protected:
    vector <LovituraAparare*> lovituriAparare;
    vector <double> probAparare;
public:
    // constructori
    Aparator();
    Aparator(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
            list <string> tipFete, vector <LovituraAparare*> lovituriAparare, vector <double> probAparare);
    Aparator(const Aparator& obj);

    // operatori
    Aparator& operator=(const Aparator& obj);
    friend istream& operator>>(istream& in, Aparator& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Aparator& obj) {return obj.afisare(out);}

    // metode
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    void showLovituri(ostream& out) const;
    pair <const Lovitura*, double> lovesteMingea() const;

    // destructor
    ~Aparator();
};

Aparator::Aparator(): Jucator() {
    this->lovituriAparare = {};
    this->probAparare = {};
}

Aparator::Aparator(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
                list <string> tpFete, vector <LovituraAparare*> lovituriAparare, vector <double> probAparare): Jucator(nume, puncte, viteza, serve, probServe, lovituri, strigateVictorie, tipFete) {
    for (int i = 0; i < lovituriAparare.size(); i ++) {
        if (dynamic_cast<Slice*>(lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Slice());
            *dynamic_cast<Slice*>(this->lovituriAparare.back()) = *dynamic_cast<Slice*>(lovituriAparare[i]);
        }

        if (dynamic_cast<Block*>(lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Block());
            *dynamic_cast<Block*>(this->lovituriAparare.back()) = *dynamic_cast<Block*>(lovituriAparare[i]);
        }
    }
    this->probAparare = probAparare;
}

Aparator::Aparator(const Aparator& obj): Jucator(obj) {
    for (int i = 0; i < obj.lovituriAparare.size(); i ++) {
        if (dynamic_cast<Slice*>(obj.lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Slice());
            *dynamic_cast<Slice*>(this->lovituriAparare.back()) = *dynamic_cast<Slice*>(obj.lovituriAparare[i]);
        }

        if (dynamic_cast<Block*>(obj.lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Block());
            *dynamic_cast<Block*>(this->lovituriAparare.back()) = *dynamic_cast<Block*>(obj.lovituriAparare[i]);
        }
    }
    this->probAparare = obj.probAparare;
}

Aparator& Aparator::operator=(const Aparator& obj) {
    if (this != &obj) {
        Jucator::operator=(obj);
        for (int i = 0; i < obj.lovituriAparare.size(); i ++) {
        if (dynamic_cast<Slice*>(obj.lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Slice());
            *dynamic_cast<Slice*>(this->lovituriAparare.back()) = *dynamic_cast<Slice*>(obj.lovituriAparare[i]);
        }

        if (dynamic_cast<Block*>(obj.lovituriAparare[i]) != nullptr) {
            this->lovituriAparare.push_back(new Block());
            *dynamic_cast<Block*>(this->lovituriAparare.back()) = *dynamic_cast<Block*>(obj.lovituriAparare[i]);
        }
    }
        this->probAparare = obj.probAparare;
    }
    return *this;
}

istream& Aparator::citire(istream& in) {
    Jucator::citire(in);
    bool op = 0;
    while (!op) {
        op = getInput<bool>("Adauga o lovitura de aparare: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            bool tip;
            tip = getInput<bool>("Slice: apasa 0\nBlock: apasa 1\n", in);
            if (!tip) {
                this->lovituriAparare.push_back(new Slice());
                in >> *dynamic_cast<Slice*>(this->lovituriAparare.back());
            }
            else {
                this->lovituriAparare.push_back(new Block());
                in >> *dynamic_cast<Block*>(this->lovituriAparare.back());
            }

            bool ok = false;
            this->probAparare.push_back(*new double);
            while (!ok) {
                this->probAparare.back() = getInput<double>("Probabilitate reusita: ", in);
                ok = verifyInput<double>(this->probAparare.back(), 0, 1);
            }
        }
    }
    return in;
}

ostream& Aparator::afisare(ostream& out) const {
    Jucator::afisare(out);
    this->showLovituri(out);
    return out;
}

void Aparator::showLovituri(ostream& out) const {
    out << "Lovituri aparare:\n";
    for (int i = 0; i < this->lovituriAparare.size(); i ++) {
        if (dynamic_cast<Slice*>(this->lovituriAparare[i]) != nullptr) {
            out << *dynamic_cast<Slice*>(this->lovituriAparare[i]);
        }
        else {
            if (dynamic_cast<Block*>(this->lovituriAparare[i]) != nullptr) {
                out << *dynamic_cast<Block*>(this->lovituriAparare[i]);
            }
            else {
                out << "Eroare";
            }
        }
        out << "Probabilitate reusita: " << this->probAparare[i] << "\n\n";
    }
}

pair <const Lovitura*, double> Aparator::lovesteMingea() const {
    bool tip;
    tip = getInput<bool>("Lovitura simpla: apasa 0\nLovitura aparare: apasa 1\n", cin);
    if (!tip) {
        return dynamic_cast<const Jucator*>(this)->lovesteMingea();
    }
    else {
        this->showLovituri(cout);

        if (this->lovituriAparare.empty()) {
            cout << "Nu ai lovituriAtac!\n";
            return {nullptr, 0};
        }

        bool ok = false;
        int index;
        while(!ok) {
            index = getInput<int>("Alege o lovitura (index-ul ei): ", cin);
            ok = verifyInput<int>(index, 0, this->lovituriAparare.size()-1);
        }

        return {this->lovituriAparare[index], this->probAparare[index]};
    }
}

Aparator::~Aparator() {
    for (int i = 0; i < this->lovituriAparare.size(); i ++) {
        if (this->lovituriAparare[i] != NULL) {
            delete this->lovituriAparare[i];
            this->lovituriAparare[i] = NULL;
        }
    }
}


class AllRounder: public Atacant, public Aparator {
public:
    // constructori
    AllRounder();
    AllRounder(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
                list <string> tipFete, vector <LovituraAtac*> lovituriAtac, vector <double> probAtac, vector <LovituraAparare*> lovituriAparare, vector <double> probAparare);
    AllRounder(const AllRounder& obj);

    // operatori
    AllRounder& operator=(const AllRounder& obj);
    friend istream& operator>>(istream& in, AllRounder& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, AllRounder& obj) {return obj.afisare(out);}

    // metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    void showLovituri(ostream& out) const;
    pair <const Lovitura*, double> lovesteMingea() const;

    // destructor
    ~AllRounder() {};
};

AllRounder::AllRounder() {};

AllRounder::AllRounder(string nume, double puncte, int viteza, vector <Serva*> serve, vector <double> probServe, map <Lovitura, double> lovituri, set <string> strigateVictorie, 
                list <string> tipFete, vector <LovituraAtac*> lovituriAtac, vector <double> probAtac, vector <LovituraAparare*> lovituriAparare, vector <double> probAparare):
            Jucator(nume, puncte, viteza, serve, probServe, lovituri, strigateVictorie, tipFete),
            Atacant(nume, puncte, viteza, serve, probServe, lovituri, strigateVictorie, tipFete, lovituriAtac, probAtac),
            Aparator(nume, puncte, viteza, serve, probServe, lovituri, strigateVictorie, tipFete, lovituriAparare, probAparare) {}

AllRounder::AllRounder(const AllRounder& obj): Jucator(obj), Atacant(obj), Aparator(obj) {}

AllRounder& AllRounder::operator=(const AllRounder& obj) {
    if (this != &obj) {
        Atacant::operator=(obj);
        Aparator::operator=(obj);
    }
    return *this;
}

istream& AllRounder::citire(istream& in) {
    Atacant::citire(in);
    bool op = 0;
    while (!op) {
        op = getInput<bool>("Adauga o lovitura de aparare: apasa 0\nInceteaza sa adaugi: apasa 1\n", in);
        if (!op) {
            bool tip;
            tip = getInput<bool>("Slice: apasa 0\nBlock: apasa 1\n", in);
            if (!tip) {
                this->lovituriAparare.push_back(new Slice());
                in >> *dynamic_cast<Slice*>(this->lovituriAparare.back());
            }
            else {
                this->lovituriAparare.push_back(new Block());
                in >> *dynamic_cast<Block*>(this->lovituriAparare.back());
            }

            bool ok = false;
            this->probAparare.push_back(*new double);
            while (!ok) {
                this->probAparare.back() = getInput<double>("Probabilitate reusita: ", in);
                ok = verifyInput<double>(this->probAparare.back(), 0, 1);
            }
        }
    }
    return in;
}

ostream& AllRounder::afisare(ostream& out) const {
    Jucator::afisare(out);
    this->showLovituri(out);
    return out;
}

void AllRounder::showLovituri(ostream& out) const {
    // cout << "Adresa metoda: " << reinterpret_cast<const void*>(this) << "\n";
    try {
        dynamic_cast<const Jucator*>(this)->showLovituri(out);
        dynamic_cast<const Atacant*>(this)->showLovituri(out);
        dynamic_cast<const Aparator*>(this)->showLovituri(out);
    }
    catch(...) {
        cout << "Eroare\n";
    }
}

pair <const Lovitura*, double> AllRounder::lovesteMingea() const {
    // cout << "ok\n";
    bool ok = false;
    int tip;
    // cout << "Adresa loveste: " << this << "\n";
    this->showLovituri(cout);
    while (!ok) {
        tip = getInput<int>("Lovitura simpla: apasa 0\nLovitura atac: apasa 1\nLovitura aparare: apasa 2\n", cin);
        ok = verifyInput<int>(tip, 0, 2);
    }

    switch(tip) {
        case 0: {
            return dynamic_cast<const Jucator*>(this)->lovesteMingea();
            break;
        }

        case 1: {
            this->showLovituri(cout);

            if (this->lovituriAtac.empty()) {
                cout << "Nu ai lovituri de atac!\n";
                return {nullptr, 0};
            }

            bool ok = false;
            int index;
            while(!ok) {
                index = getInput<int>("Alege o lovitura (index-ul ei): ", cin);
                ok = verifyInput<int>(index, 0, this->lovituriAtac.size()-1);
            }

            return {this->lovituriAtac[index], this->probAtac[index]};
            break;
        }

        case 2: {
            this->showLovituri(cout);

            if (this->lovituriAparare.empty()) {
                cout << "Nu ai lovituri de aparare!\n";
                return {nullptr, 0};
            }

            bool ok = false;
            int index;
            while(!ok) {
                index = getInput<int>("Alege o lovitura (index-ul ei): ", cin);
                ok = verifyInput<int>(index, 0, this->lovituriAparare.size()-1);
            }

            return {this->lovituriAparare[index], this->probAparare[index]};
            break;
        }
    }
}



// clasa template
template <class T, class U> 
class Joc {
    T p1;
    U p2;
    int nrSeturi;
    int nrPuncte;
    pair <int, int> scorMeci;
    pair <int, int> scorSet;

public:
    // constructori
    Joc();
    Joc(T p1, U p2, int nrSeturi, int nrPuncte, pair <int, int> scorMeci, pair <int, int> scorSet);
    Joc(const Joc <T, U>& obj);

    // operatori
    Joc <T, U>& operator=(const Joc <T, U>& obj);
    friend istream& operator>>(istream& in, Joc <T, U>& obj);
    friend ostream& operator<<(ostream& out, const Joc <T, U>& obj);

    // metode
    void joaca();

    // destructor
    ~Joc();
};

template <class T, class U> 
Joc <T, U>::Joc() {
    this->p1 = nullptr;
    this->p2 = nullptr;
    this->nrSeturi = 0;
    this->nrPuncte = 0;
    this->scorMeci.first = 0;
    this->scorMeci.second = 0;
    this->scorSet.first = 0;
    this->scorSet.second = 0;
}

template <class T, class U>
Joc <T, U>::Joc(T p1, U p2, int nrSeturi, int nrPuncte, pair <int, int> scorMeci, pair <int, int> scorSet) {
    this->p1 = p1;
    this->p2 = p2;
    this->nrSeturi = nrSeturi;
    this->nrPuncte = nrPuncte;
    this->scorMeci = scorMeci;
    this->scorSet = scorSet;
}

template <class T, class U>
Joc <T, U>::Joc(const Joc <T, U>& obj) {
    this->p1 = obj.p1;
    this->p2 = obj.p2;
    this->nrSeturi = obj.nrSeturi;
    this->nrPuncte = obj.nrPuncte;
    this->scorMeci = obj.scorMeci;
    this->scorSet = obj.scorSet;
}

template <class T, class U>
Joc <T, U>& Joc <T, U>::operator=(const Joc <T, U>& obj) {
    if (this != &obj) {
        this->p1 = obj.p1;
        this->p2 = obj.p2;
        this->nrSeturi = obj.nrSeturi;
        this->nrPuncte = obj.nrPuncte;
        this->scorMeci = obj.scorMeci;
        this->scorSet = obj.scorSet;
    }
    return *this;
}

template <class T, class U>
istream& operator>>(istream& in, Joc <T, U>& obj) {
    in >> obj.p1;
    in >> obj.p2;

    bool ok = 0;
    while (!ok) {
        obj.nrSeturi = getInput<int>("Nr seturi: ", in);
        ok = verifyInput<int>(obj.nrSeturi, 1, MAX);
    }

    ok = 0;
    while (!ok) {
        obj.nrPuncte = getInput<int>("Nr puncte: ", in);
        ok = verifyInput<int>(obj.nrPuncte, 1, MAX);
    }

    ok = 0;
    while (!ok) {
        obj.scorMeci.first = getInput<int>("Scor meci jucator 1: ", in);
        ok = verifyInput<int>(obj.scorMeci.first, 0, obj.nrSeturi);
    }

    ok = 0;
    while (!ok) {
        obj.scorMeci.second = getInput<int>("Scor meci jucator 2: ", in);
        ok = verifyInput<int>(obj.scorMeci.second, 0, obj.nrSeturi);
    }

    ok = 0;
    while (!ok) {
        obj.scorSet.first = getInput<int>("Scor set jucator 1: ", in);
        ok = verifyInput<int>(obj.scorSet.first, 0, obj.nrPuncte);
    }

    ok = 0;
    while (!ok) {
        obj.scorSet.second = getInput<int>("Scor set jucator 2: ", in);
        ok = verifyInput<int>(obj.scorSet.second, 0, obj.nrPuncte);
    }

    return in;
}

template <class T, class U>
ostream& operator<<(ostream& out, const Joc <T, U>& obj) {
    out << "Jucator 1:\n" << obj.p1 << "\n";
    out << "Jucator 2:\n" << obj.p2 << "\n";
    out << "Nr seturi: " << obj.nrSeturi << "\n";
    out << "Nr puncte: " << obj.nrPuncte << "\n";
    out << "Scor meci: " << obj.scorMeci.first << " - " << obj.scorMeci.second << "\n";
    out << "Scor set: " << obj.scorSet.first << " - " << obj.scorSet.second << "\n";
    return out;
}


template <class T, class U>
void Joc <T, U>::joaca() {
    bool ok = 1;

    // inca mai trebuie jucate seturi
    while (max(this->scorMeci.first, this->scorMeci.second) < this->nrSeturi / 2 + 1) {
        // inca nu s-a terminat setul
        int nr = 0;
        while (max(this->scorSet.first, this->scorSet.second) < this->nrPuncte || abs(this->scorSet.first - this->scorSet.second) < 2) {

            bool ok = 1;
            int rand;
            int viteza = 1;
            Efect* efect = new Efect();

            // vedem al cui e randul
            if (nr % 4 < 2) {
                // 1 serveste
                cout << p1->getNume() << " serveste\n";
                pair <const Serva*, double> serva = p1->serveste();
                bool reuseste = succes(serva.second);
                if (!reuseste) {
                    cout << "\033[31m" << p1->getNume() << " a servit pe langa\nAia e, se mai intampla\n" << "\033[0m";
                    this->scorSet.second ++;
                    ok = 0;
                }
                else {
                    cout << "Serva aleasa:\n" << *serva.first << "\n";
                    if (typeid(*serva.first->getEfect()) == typeid(Topspin)) {
                        delete efect;
                        efect = new Topspin();
                        *efect = *serva.first->getEfect();
                    }

                    if (typeid(*serva.first->getEfect()) == typeid(Backspin)) {
                        delete efect;
                        efect = new Backspin();
                        *efect = *serva.first->getEfect();
                    }  

                    // cout << "Efect serva: " << typeid(*efect).name() << "\n";
                    rand = 2;
                }
            }
            else {
                // 2 serveste
                cout << p2->getNume() << " serveste\n";
                pair <const Serva*, double> serva = p2->serveste();
                bool reuseste = succes(serva.second);
                if (!reuseste) {
                    cout << "\033[31m" << p2->getNume() << " a servit pe langa\nAia e, se mai intampla\n" << "\033[0m";
                    this->scorSet.first ++;
                    ok = 0;
                }
                else {
                    cout << "Serva aleasa:\n" << *serva.first << "\n";
                    if (typeid(*serva.first->getEfect()) == typeid(Topspin)) {
                        delete efect;
                        efect = new Topspin();
                        *efect = *serva.first->getEfect();
                    }

                    if (typeid(*serva.first->getEfect()) == typeid(Backspin)) {
                        delete efect;
                        efect = new Backspin();
                        *efect = *serva.first->getEfect();
                    }  

                    // cout << "Efect serva: " << typeid(*efect).name() << "\n";
                    rand = 1;
                }
            }

            // continua jocul
            while (ok) {
                if (rand == 1) {
                    cout << "\nRandul lui " << p1->getNume() << "\n";
                    // verificam daca e suficient de rapid sa ajunga la minge
                    if (p1->rapid(viteza)) {
                        pair<const Lovitura *, double> l1 = p1->lovesteMingea();

                        bool ok2 = 0;
                        cout << "Lovitura aleasa: \n";
                        cout << *l1.first << "\n";

                        if (typeid(*l1.first) == typeid(Loop)) {
                            ok2 = 1;
                            cout << *dynamic_cast<const Loop *>(l1.first) << "\n";
                        }

                        if (typeid(*l1.first) == typeid(Smash)) {
                            ok2 = 1;
                            cout << *dynamic_cast<const Smash *>(l1.first) << "\n";
                        }

                        if (typeid(*l1.first) == typeid(Slice)) {
                            ok2 = 1;
                            cout << *dynamic_cast<const Slice *>(l1.first) << "\n";
                        }

                        if (typeid(*l1.first) == typeid(Block)) {
                            ok2 = 1;
                            cout << *dynamic_cast<const Block *>(l1.first) << "\n";
                        }

                        if (!ok2) {
                            ok2 = 1;
                            cout << *l1.first << "\n";
                        }
                        // cout << "Tip lovitura: " << typeid(*l1.first).name() << "\n";

                        // cout << "Prob: " << l1.second << "\n";
                        bool reuseste = succes(l1.second);
                        if (!reuseste) {
                            cout << "\033[31m" << p1->getNume() << " a dat pe langa\nAia e, se mai intampla\n" << "\033[0m";
                            this->scorSet.second++;
                            ok = 0;
                        }
                        else {
                            // verificam daca e bun efectul
                            bool bun;
                            ok2 = 0;
                            if (typeid(*l1.first) == typeid(Loop)) {
                                ok2 = 1;
                                bun = dynamic_cast<const Loop *>(l1.first)->potrivit(efect);
                                // updatam efectul
                                delete efect;
                                efect = new Topspin();
                                efect->setIntensitate(dynamic_cast<const Loop *>(l1.first)->getIntensitateEfect());
                                cout << "\nNoul efect:\n" << *dynamic_cast<Topspin *>(efect);
                            }

                            if (typeid(*l1.first) == typeid(Smash)) {
                                ok2 = 1;
                                bun = dynamic_cast<const Smash *>(l1.first)->potrivit(efect);
                                delete efect;
                                efect = new Efect();
                                efect->setIntensitate(0);
                                cout << "\nNoul efect: " << *efect;
                                // updatam viteza
                                viteza = dynamic_cast<const Smash *>(l1.first)->getViteza();
                            }

                            if (typeid(*l1.first) == typeid(Slice)) {
                                ok2 = 1;
                                bun = dynamic_cast<const Slice *>(l1.first)->potrivit(efect);
                                delete efect;
                                efect = new Backspin();
                                efect->setIntensitate(dynamic_cast<const Slice *>(l1.first)->getIntensitateEfect());
                                cout << "\nNoul efect:\n"
                                     << *dynamic_cast<Backspin *>(efect);
                            }

                            if (typeid(*l1.first) == typeid(Block)) {
                                ok2 = 1;
                                bun = dynamic_cast<const Block *>(l1.first)->potrivit(efect);
                                efect = new Efect();
                                efect->setIntensitate(0);
                                cout << "\nNoul efect: " << *efect;
                                // updatam viteza
                                viteza = viteza * dynamic_cast<const Block *>(l1.first)->getAmplificare();
                            }

                            if (!ok2) {
                                bun = l1.first->potrivit(efect);
                                if (bun)
                                {
                                    efect = new Efect();
                                    efect->setIntensitate(0);
                                    cout << "\nNoul efect: " << *efect;
                                }
                            }

                            if (!bun) {
                                cout << "Efectul nu e bun!\n";
                                this->scorSet.second++;
                                ok = 0;
                            }
                            else  {
                                // updatam viteza
                                if (typeid(*l1.first) != typeid(Block) && typeid(*l1.first) != typeid(Smash))
                                    viteza = l1.first->getViteza();
                                cout << "Noua viteza: " << viteza << "\n";
                                rand = 2;
                            }
                        }
                    }
                    else {
                        cout << "\033[31m" << p1->getNume() << " nu a fost destul de rapid!\n" << "\033[0m";
                        ok = 0;
                        this->scorSet.second ++;
                    }
                }
                else {
                    if (rand == 2) {
                        cout << "\nRandul lui " << p2->getNume() << "\n";
                        // verificam daca e suficient de rapid sa ajunga la minge
                        if (p2->rapid(viteza)) {
                            pair <const Lovitura*, double> l2 = p2->lovesteMingea();

                            // cout << *p2->lovesteMingea().first << "\n";
                            bool ok2 = 0;
                            cout << "Lovitura aleasa: \n";
                            if (dynamic_cast<const Loop*>(l2.first) != nullptr) {
                                ok2 = 1;
                                cout << *dynamic_cast<const Loop*>(l2.first) << "\n";
                            }

                            if (dynamic_cast<const Smash*>(l2.first) != nullptr) {
                                ok2 = 1;
                                cout << *dynamic_cast<const Smash*>(l2.first) << "\n";
                            }

                            if (dynamic_cast<const Slice*>(l2.first) != nullptr) {
                                ok2 = 1;
                                cout << *dynamic_cast<const Slice*>(l2.first) << "\n";
                            }

                            if (dynamic_cast<const Block*>(l2.first) != nullptr) {
                                ok2 = 1;
                                cout << *dynamic_cast<const Block*>(l2.first) << "\n";
                            }

                            if (!ok2) {
                                ok2 = 1;
                                cout << *l2.first << "\n";
                            }
                            // cout << "Tip lovitura: " << typeid(*l2.first).name() << "\n";

                            // cout << "Prob: " << l2.second << "\n";
                            bool reuseste = succes(l2.second);
                            if (!reuseste) {
                                cout << "\033[31m" << p2->getNume() << " a dat pe langa\nAia e, se mai intampla\n" << "\033[0m";
                                this->scorSet.first ++;
                                ok = 0;
                            }
                            else {
                                // verificam daca e bun efectul
                                bool bun;
                                ok2 = 0;
                                if (typeid(*l2.first) == typeid(Loop)) {
                                    ok2 = 1;
                                    bun = dynamic_cast<const Loop*>(l2.first)->potrivit(efect);
                                    delete efect;
                                    efect = new Topspin();
                                    efect->setIntensitate(dynamic_cast<const Loop*>(l2.first)->getIntensitateEfect());
                                    cout << "\nNoul efect:\n" << *dynamic_cast<Topspin*>(efect);
                                }

                                if (typeid(*l2.first) == typeid(Smash)) {
                                    ok2 = 1;
                                    bun = dynamic_cast<const Smash*>(l2.first)->potrivit(efect);
                                    efect = new Efect();
                                    efect->setIntensitate(0);
                                    cout << "\nNoul efect: " << *efect;
                                    // updatam viteza
                                    viteza = dynamic_cast<const Smash*>(l2.first)->getViteza();
                                }

                                if (typeid(*l2.first) == typeid(Slice)) {
                                    ok2 = 1;
                                    bun = dynamic_cast<const Slice*>(l2.first)->potrivit(efect);
                                    delete efect;
                                    efect = new Backspin();
                                    efect->setIntensitate(dynamic_cast<const Slice*>(l2.first)->getIntensitateEfect());
                                    cout << "\nNoul efect:\n" << *dynamic_cast<Backspin*>(efect);
                                }

                                if (typeid(*l2.first) == typeid(Block)) {
                                    ok2 = 1;
                                    bun = dynamic_cast<const Block*>(l2.first)->potrivit(efect);
                                    efect = new Efect();
                                    efect->setIntensitate(0);
                                    cout << "\nNoul efect: " << *efect;
                                    // updatam viteza
                                    viteza = viteza * dynamic_cast<const Block*>(l2.first)->getAmplificare();
                                }

                                if (!ok2) {
                                    bun = l2.first->potrivit(efect);
                                    if (bun) {
                                        efect = new Efect();
                                        efect->setIntensitate(0);
                                        cout << "\nNoul efect: " << *efect;
                                    }
                                }

                                if (!bun) {
                                    cout << "Efectul nu e bun!\n";
                                    this->scorSet.first ++;
                                    ok = 0;
                                }
                                else {
                                    if (typeid(*l2.first) != typeid(Block) && typeid(*l2.first) != typeid(Smash))
                                        viteza = l2.first->getViteza();
                                    cout << "Noua viteza: " << viteza << "\n";
                                    rand = 1;
                                }
                            }
                        }
                        else {
                            cout << "\033[31m" << p2->getNume() << " nu a fost destul de rapid! :(\n" << "\033[0m";
                            ok = 0;
                            this->scorSet.first ++;
                        }
                    }
                }
            }

            cout << "\nScor: " << this->scorSet.first << " - " << this->scorSet.second << "\n";
            nr ++;
        }

        // s-a terminat setul
        cout << "\033[32m" << "S-a terminat setul\n" << "\033[0m";
        if (this->scorSet.first > this->scorSet.second) {
            this->scorMeci.first ++;
            cout << "\033[32m" << p1->getNume() << " a castigat setul!\n" << "\033[0m";
            p1->striga();
        }
        else {
            this->scorMeci.second ++;
            cout << "\033[32m" << p2->getNume() << " a castigat setul!\n" << "\033[0m";
            p2->striga();
        }

        this->scorSet.first = 0;
        this->scorSet.second = 0;

        cout << "Scor seturi: " << this->scorMeci.first << " - " << this->scorMeci.second << "\n";
    }

    if (this->scorMeci.first > this->scorMeci.second) {
        cout << "\033[32m" << p1->getNume() << " a castigat!\n" << "\033[0m";
        p1->striga();
        p1->updatePuncte(10);
    }
    else {
        cout << "\033[32m" << p2->getNume() << " a castigat!\n" << "\033[0m";
        p2->striga();
        p2->updatePuncte(10);
    }
}

template <class T, class U>
Joc <T, U>::~Joc() {
    if (this->p1 != NULL) {
        delete this->p1;
        this->p1 = NULL;
    }
    if (this->p2 != NULL) {
        delete this->p2;
        this->p2 = NULL;
    }
}


// meniu singleton
class Meniu {
private:
    static Meniu* meniu;
    vector <Jucator*> jucatori;
    Meniu() = default;
    Meniu(const Meniu&) = delete;
    static int nrMeniuri;

public:
    static Meniu* getMeniu() {
        nrMeniuri ++;
        if (!meniu)
            meniu = new Meniu();
        return meniu;
    }

    void adaugaJucator();
    void afiseazaJucatori() const;
    void modificaJucator();
    void stergeJucator();
    void joacaPingPong();
    void start();

    // destructor
    ~Meniu();
};

Meniu* Meniu::meniu = NULL;
int Meniu::nrMeniuri = 0;

void Meniu::adaugaJucator() {
    Jucator* jucator;

    int comanda;
    bool ok = false;
    while (!ok) {
        comanda = getInput<int>("Jucator simplu: apasa 0\nAtacant: apasa 1\nAparator: apasa 2\nAll-rounder: apasa 3\n", cin);
        ok = verifyInput<int>(comanda, 0, 3);
    }
    
    switch(comanda) {
        case 0: {
            jucator = new Jucator();
            break;
        }

        case 1: {
            jucator = new Atacant();
            break;
        }

        case 2: {
            jucator = new Aparator();
            break;
        }

        case 3: {
            jucator = new AllRounder();
            break;
        }

        default: {
            cout << "Comanda invalida\n";
            break;
        }
    }

    cin >> *jucator;
    jucatori.push_back(jucator);
}

void Meniu::afiseazaJucatori() const {
    for (int i = 0; i < this->jucatori.size(); i ++)
        cout << *this->jucatori[i] << "\n\n";
}

void Meniu::stergeJucator() {
    int i;
    bool ok = 0;
    while (!ok) {
        i = getInput<int>("Indicele jucatorului pe care vreti sa il stergeti: ", cin);
        ok = verifyInput<int>(i, 0, this->jucatori.size()-1);
    }
    this->jucatori.erase(this->jucatori.begin() + i);
}

void Meniu::modificaJucator() {
    int i;
    bool ok = 0;
    while (!ok) {
        i = getInput<int>("Indicele jucatorului pe care vreti sa il modificati: ", cin);
        ok = verifyInput<int>(i, 0, this->jucatori.size()-1);
    }
    cin >> *this->jucatori[i];
}


void Meniu::joacaPingPong() {
    try {
        if (jucatori.empty())
            throw 1;

        int i1, i2;
        bool ok = 0;
        while (!ok) {
            i1 = getInput<int>("Indicele primului jucator: ", cin);
            ok = verifyInput<int>(i1, 0, this->jucatori.size()-1);
        }

        ok = 0;
        while (!ok) {
            i2 = getInput<int>("Indicele celui de-al doilea jucator: ", cin);
            ok = verifyInput<int>(i2, 0, this->jucatori.size()-1);
        }

        int nrSeturi = getInput<int>("Nr seturi: ", cin);
        int nrPuncte = getInput<int>("Nr puncte: ", cin);

        if (dynamic_cast<AllRounder*>(this->jucatori[i1]) != nullptr && dynamic_cast<AllRounder*>(this->jucatori[i2]) != nullptr) {
            AllRounder* j1 = new AllRounder();
            *j1 = *dynamic_cast<AllRounder*>(this->jucatori[i1]);
            AllRounder* j2 = new AllRounder();
            *j2 = *dynamic_cast<AllRounder*>(this->jucatori[i2]);
            Joc<AllRounder*, AllRounder*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<AllRounder*>(this->jucatori[i1]) != nullptr && dynamic_cast<Atacant*>(this->jucatori[i2]) != nullptr) {
            AllRounder* j1 = new AllRounder();
            *j1 = *dynamic_cast<AllRounder*>(this->jucatori[i1]);
            Atacant* j2 = new Atacant();
            *j2 = *dynamic_cast<Atacant*>(this->jucatori[i2]);
            Joc<AllRounder*, Atacant*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<AllRounder*>(this->jucatori[i1]) != nullptr && dynamic_cast<Aparator*>(this->jucatori[i2]) != nullptr) {
            AllRounder* j1 = new AllRounder();
            *j1 = *dynamic_cast<AllRounder*>(this->jucatori[i1]);
            Aparator* j2 = new Aparator();
            *j2 = *dynamic_cast<Aparator*>(this->jucatori[i2]);
            Joc<AllRounder*, Aparator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<AllRounder*>(this->jucatori[i1]) != nullptr && dynamic_cast<Jucator*>(this->jucatori[i2]) != nullptr) {
            AllRounder* j1 = new AllRounder();
            *j1 = *dynamic_cast<AllRounder*>(this->jucatori[i1]);
            Jucator* j2 = new Jucator();
            *j2 = *dynamic_cast<Jucator*>(this->jucatori[i2]);
            Joc<AllRounder*, Jucator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Atacant*>(this->jucatori[i1]) != nullptr && dynamic_cast<AllRounder*>(this->jucatori[i2]) != nullptr) {
            Atacant* j1 = new Atacant();
            *j1 = *dynamic_cast<Atacant*>(this->jucatori[i1]);
            AllRounder* j2 = new AllRounder();
            *j2 = *dynamic_cast<AllRounder*>(this->jucatori[i2]);
            Joc<Atacant*, AllRounder*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Atacant*>(this->jucatori[i1]) != nullptr && dynamic_cast<Atacant*>(this->jucatori[i2]) != nullptr) {
            Atacant* j1 = new Atacant();
            *j1 = *dynamic_cast<Atacant*>(this->jucatori[i1]);
            Atacant* j2 = new Atacant();
            *j2 = *dynamic_cast<Atacant*>(this->jucatori[i2]);
            Joc<Atacant*, Atacant*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Atacant*>(this->jucatori[i1]) != nullptr && dynamic_cast<Aparator*>(this->jucatori[i2]) != nullptr) {
            Atacant* j1 = new Atacant();
            *j1 = *dynamic_cast<Atacant*>(this->jucatori[i1]);
            Aparator* j2 = new Aparator();
            *j2 = *dynamic_cast<Aparator*>(this->jucatori[i2]);
            Joc<Atacant*, Aparator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Atacant*>(this->jucatori[i1]) != nullptr && dynamic_cast<Jucator*>(this->jucatori[i2]) != nullptr) {
            Atacant* j1 = new Atacant();
            *j1 = *dynamic_cast<Atacant*>(this->jucatori[i1]);
            Jucator* j2 = new Jucator();
            *j2 = *dynamic_cast<Jucator*>(this->jucatori[i2]);
            Joc<Atacant*, Jucator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Aparator*>(this->jucatori[i1]) != nullptr && dynamic_cast<AllRounder*>(this->jucatori[i2]) != nullptr) {
            Aparator* j1 = new Aparator();
            *j1 = *dynamic_cast<Aparator*>(this->jucatori[i1]);
            AllRounder* j2 = new AllRounder();
            *j2 = *dynamic_cast<AllRounder*>(this->jucatori[i2]);
            Joc<Aparator*, AllRounder*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Aparator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Atacant*>(this->jucatori[i2]) != nullptr) {
            Aparator* j1 = new Aparator();
            *j1 = *dynamic_cast<Aparator*>(this->jucatori[i1]);
            Atacant* j2 = new Atacant();
            *j2 = *dynamic_cast<Atacant*>(this->jucatori[i2]);
            Joc<Aparator*, Atacant*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Aparator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Aparator*>(this->jucatori[i2]) != nullptr) {
            Aparator* j1 = new Aparator();
            *j1 = *dynamic_cast<Aparator*>(this->jucatori[i1]);
            Aparator* j2 = new Aparator();
            *j2 = *dynamic_cast<Aparator*>(this->jucatori[i2]);
            Joc<Aparator*, Aparator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Aparator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Jucator*>(this->jucatori[i2]) != nullptr) {
            Aparator* j1 = new Aparator();
            *j1 = *dynamic_cast<Aparator*>(this->jucatori[i1]);
            Jucator* j2 = new Jucator();
            *j2 = *dynamic_cast<Jucator*>(this->jucatori[i2]);
            Joc<Aparator*, Jucator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Jucator*>(this->jucatori[i1]) != nullptr && dynamic_cast<AllRounder*>(this->jucatori[i2]) != nullptr) {
            Jucator* j1 = new Jucator();
            *j1 = *dynamic_cast<Jucator*>(this->jucatori[i1]);
            AllRounder* j2 = new AllRounder();
            *j2 = *dynamic_cast<AllRounder*>(this->jucatori[i2]);
            Joc<Jucator*, AllRounder*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Jucator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Atacant*>(this->jucatori[i2]) != nullptr) {
            Jucator* j1 = new Jucator();
            *j1 = *dynamic_cast<Jucator*>(this->jucatori[i1]);
            Atacant* j2 = new Atacant();
            *j2 = *dynamic_cast<Atacant*>(this->jucatori[i2]);
            Joc<Jucator*, Atacant*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Jucator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Aparator*>(this->jucatori[i2]) != nullptr) {
            Jucator* j1 = new Jucator();
            *j1 = *dynamic_cast<Jucator*>(this->jucatori[i1]);
            Aparator* j2 = new Aparator();
            *j2 = *dynamic_cast<Aparator*>(this->jucatori[i2]);
            Joc<Jucator*, Aparator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }

        if (dynamic_cast<Jucator*>(this->jucatori[i1]) != nullptr && dynamic_cast<Jucator*>(this->jucatori[i2]) != nullptr) {
            Jucator* j1 = new Jucator();
            *j1 = *dynamic_cast<Jucator*>(this->jucatori[i1]);
            Jucator* j2 = new Jucator();
            *j2 = *dynamic_cast<Jucator*>(this->jucatori[i2]);
            Joc<Jucator*, Jucator*> joc(j1, j2, nrSeturi, nrPuncte, {0,0}, {0,0});
            joc.joaca();
            this->jucatori[i1]->setPuncte(j1->getPuncte());
            this->jucatori[i2]->setPuncte(j2->getPuncte());
            return;
        }
    }
    catch(int) {
        cout << "Nu exista jucatori\n";
    }
}

void Meniu::start() {
    Efect* b1 = new Backspin(50);
    Efect* b2 = new Backspin(70);
    Efect* t1 = new Topspin(40);
    Efect* t2 = new Topspin(80);

    Serva* s1 = new Serva("s1", b1);
    Serva* s2 = new Serva("s2", t1);
    Serva* s3 = new Serva("s3", b2);
    Serva* s4 = new Serva("s4", t2);

    Lovitura* l1 = new Lovitura("l1", 40);
    Lovitura* l2 = new Lovitura("l2", 70);
    Lovitura* l3 = new Lovitura("l3", 50);
    Lovitura* l4 = new Lovitura("l4", 30);

    Loop* loop1 = new Loop("loop1", 60, *dynamic_cast<Topspin*>(t2));
    Smash* smash1 = new Smash("smash1", 80, 80);
    Slice* slice1 = new Slice("slice1", 30, *dynamic_cast<Backspin*>(b1));
    Block* block1 = new Block("block1", 50, 40);

    Jucator* j1 = new AllRounder("j1", 20, 60, {s1, s2}, {0.8, 0.9}, {{*l1, 0.7}, {*l2, 0.8}}, {"choo"}, {"mxp", "mxs"}, {loop1}, {0.9}, {block1}, {0.8});
    Jucator* j2 = new AllRounder("j2", 50, 80, {s3, s4}, {0.7, 1}, {{*l3, 0.8}, {*l4, 0.6}}, {"choo"}, {"tenergy"}, {smash1}, {0.6}, {slice1}, {0.8});

    this->jucatori.push_back(j1);
    this->jucatori.push_back(j2);

    bool ok = 1;
    while (ok) {
        int comanda;
        bool ok2 = false;
        while (!ok2) {
            comanda = getInput<int>("Adauga un jucator: apasa 0\nAfiseaza jucatorii: apasa 1\nModifica un jucator: apasa 2\nSterge un jucator: apasa 3\nJoaca ping pong: apasa 4\nStop: apasa 5\n", cin);
            ok2 = verifyInput<int>(comanda, 0, 5);
        }

        switch(comanda) {
            case 0: {
                this->adaugaJucator();
                break;
            }

            case 1: {
                this->afiseazaJucatori();
                break;
            }

            case 2: {
                this->modificaJucator();
                break;
            }

            case 3: {
                this->stergeJucator();
                break;
            }

            case 4: {
                this->joacaPingPong();
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

    delete b1, b2, t1, t2, l1, l2, l3, l4, loop1, smash1, slice1, block1;
}

Meniu::~Meniu() {
    this->nrMeniuri --;
    if (this->nrMeniuri == 0) {
        if (this->meniu) {
            for (int i = 0; i < this->jucatori.size(); i ++)
                delete this->jucatori[i];
            delete this->meniu;
        }
    }
}


int main() {
    Meniu* meniu = meniu->getMeniu();
    meniu->start();

    return 0;
}