#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Exceptie : public exception {
public:
	Exceptie(const char* mesaj) : exception(mesaj) {};
};

class MateriePrima {
private:
	char* numeMatPrima=nullptr;
	float stocMatPrima=0;
	static int totalMateriiPrime;
public:
	MateriePrima(){
		totalMateriiPrime++;
	}

	MateriePrima(const char* numeMatPrima) {
		if (strlen(numeMatPrima) >= 2) {
			this->numeMatPrima = new char[strlen(numeMatPrima) + 1];
			strcpy(this->numeMatPrima, numeMatPrima);
		}
	}

	MateriePrima(const char* numeMatPrima, float stocMatPrima){
		if (strlen(numeMatPrima) >= 2) {
			this->numeMatPrima = new char[strlen(numeMatPrima) + 1];
			strcpy(this->numeMatPrima, numeMatPrima);
		}
		if (stocMatPrima > 0)
			this->stocMatPrima = stocMatPrima;
		totalMateriiPrime++;
	}

	void setNumeMatPrima(const char* numeNou) {
		if (strlen(numeNou) >= 2) {
			this->numeMatPrima = new char[strlen(numeNou) + 1];
			strcpy(this->numeMatPrima, numeNou);
		}
	}

	void setStocMatPrima(float stocNou) {
		if (stocNou >= 0)
			this->stocMatPrima = stocNou;
	}

	char* getNumeMatPrima() const {
		return this->numeMatPrima;
	}
	
	float getStocMatPrima() const {
		return this->stocMatPrima;
	}

	static int getNumarTotalMateriiPrime() {
		return totalMateriiPrime;
	}

	MateriePrima(const MateriePrima& m){
		if (strlen(m.numeMatPrima) >= 2) {
			this->numeMatPrima = new char[strlen(m.numeMatPrima) + 1];
			strcpy(this->numeMatPrima, m.numeMatPrima);
		}
		if (m.stocMatPrima > 0)
			this->stocMatPrima = m.stocMatPrima;
	}

	MateriePrima& operator=(const MateriePrima& m) {
		if (this != &m) {
			delete[] this->numeMatPrima;
			this->numeMatPrima = nullptr;
			if (strlen(m.numeMatPrima) >= 2) {
				this->numeMatPrima = new char[strlen(m.numeMatPrima) + 1];
				strcpy(this->numeMatPrima, m.numeMatPrima);
			}
			if (m.stocMatPrima > 0)
				this->stocMatPrima = m.stocMatPrima;
		}
		return *this;

	}

	//operatorul cast implicit 
	operator float() {
		return this->stocMatPrima;
	}

	//operatorul == pentru a testa egalitatea dintre 2 obiecte
	bool operator==(const MateriePrima& m) const {
		return (strcmp(this->numeMatPrima, m.numeMatPrima) == 0) && (this->stocMatPrima == m.stocMatPrima);
	}

	//operatorul pentru negatie
	bool operator!() const {
		return (this->stocMatPrima <= 0);
	}

	friend ostream& operator<<(ostream& out, MateriePrima& m) {
		out << "\n-----------------";
		out << "\nMateria prima: " << m.numeMatPrima;
		out << "\nStocul de materie prima: " << m.stocMatPrima;
		out << "\n-----------------";
		return out;
	}

	friend istream& operator>>(istream& in, MateriePrima& m) {
		delete[] m.numeMatPrima;
		m.numeMatPrima = nullptr;
		cout << "\nIntroduceti numele materiei prime: ";
		string buffer;
		getline(in, buffer);
		m.numeMatPrima = new char[buffer.size() + 1];
		strcpy(m.numeMatPrima, buffer.data());
		cout << "\nIntroduceti stocul de materie prima: ";
		in >> m.stocMatPrima;
		if (m.stocMatPrima <= 0)
			m.stocMatPrima = 0;
		return in;
	}

	~MateriePrima() {
		delete[] this->numeMatPrima;
		this->numeMatPrima = nullptr;
		totalMateriiPrime--;
		}
};

int MateriePrima::totalMateriiPrime = 0;

class Reteta {
private:
	MateriePrima* ingrediente = nullptr;
	int nrIngrediente=0;
	float* cantitatiIngrediente = nullptr;
public:
	Reteta() {

	}

	Reteta(int nrIngrediente) {
		if(nrIngrediente>0)
		this->nrIngrediente = nrIngrediente;
	}

	Reteta(int nrIngrediente, MateriePrima* ingrediente, float* cantitatiIngrediente) {
		if (nrIngrediente <= 0) {
			this->nrIngrediente = 0;
			this->ingrediente = nullptr;
			this->cantitatiIngrediente = nullptr;
		}
		else {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new MateriePrima[this->nrIngrediente];
			this->cantitatiIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->ingrediente[i] = ingrediente[i];
				this->cantitatiIngrediente[i] = cantitatiIngrediente[i];
			}
		}
	}

	void adaugaIngredient(const MateriePrima& ingredientNou, float cantitateNoua) {
		if (strlen(ingredientNou.getNumeMatPrima()) > 2 && cantitateNoua > 0) {
			MateriePrima* tempIngredient = new MateriePrima[this->nrIngrediente + 1];
			float* tempCantitate = new float[this->nrIngrediente + 1];
			for (int i = 0; i < this->nrIngrediente; i++) {
				tempIngredient[i] = this->ingrediente[i];
				tempCantitate[i] = this->cantitatiIngrediente[i];
			}
			bool ok = 1;
			for (int i = 0; i < this->nrIngrediente; i++) {
				if (ingredientNou == tempIngredient[i])
					ok = 0;
			}
			if (ok == 1) {
				tempIngredient[this->nrIngrediente] = ingredientNou;
				tempCantitate[this->nrIngrediente] = cantitateNoua;
				delete[] this->ingrediente;
				delete[] this->cantitatiIngrediente;
				this->ingrediente = tempIngredient;
				this->cantitatiIngrediente = tempCantitate;
				this->nrIngrediente++;
			}
		}
	}

	MateriePrima* getIngredient() const{
		return this->ingrediente;
	}

	int getNrIngrediente() const{
		return this->nrIngrediente;
	}

	float* getCantitateIngredient() const{
		return this->cantitatiIngrediente;
	}

	Reteta(const Reteta& r) {
		if (r.nrIngrediente <= 0) {
			this->nrIngrediente = 0;
			this->ingrediente = nullptr;
			this->cantitatiIngrediente = nullptr;
		}
		else {
			this->nrIngrediente = r.nrIngrediente;
			this->ingrediente = new MateriePrima[this->nrIngrediente];
			this->cantitatiIngrediente = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->ingrediente[i] = r.ingrediente[i];
				this->cantitatiIngrediente[i] = r.cantitatiIngrediente[i];
			}
		}
	}

	Reteta& operator=(const Reteta& r) {
		if (this != &r) {
			delete[] this->ingrediente;
			delete[] this->cantitatiIngrediente;
			this->ingrediente = nullptr;
			this->cantitatiIngrediente = nullptr;
			if (r.nrIngrediente <= 0) {
				this->nrIngrediente = 0;
				this->ingrediente = nullptr;
				this->cantitatiIngrediente = nullptr;
			}
			else {
				this->nrIngrediente = r.nrIngrediente;
				this->ingrediente = new MateriePrima[this->nrIngrediente];
				this->cantitatiIngrediente = new float[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++) {
					this->ingrediente[i] = r.ingrediente[i];
					this->cantitatiIngrediente[i] = r.cantitatiIngrediente[i];
				}
			}
		}
		return *this;
	}

	//operatorul de indexare
	float& operator[](int index) {
		if (index >= 0 && index < this->nrIngrediente) {
			return this->cantitatiIngrediente[index];
		}
		else {
			throw exception("Indexul nu este in limita definita");
		}
	}

	friend ostream& operator<<(ostream& out, Reteta& r)
	{
		out << "\n-----------------";
		if (r.nrIngrediente > 0) {
			for(int i=0;i<r.nrIngrediente;i++)
				out << "\nIngredient: " << r.ingrediente[i].getNumeMatPrima() << "; Cantitate necesara: " << r[i];//operator[]
		}
		else {
			throw exception( "\nNu exista ingrediente pt aceasta reteta.");
		}
		out << "\n-----------------";
		return out;
	}

	friend istream& operator>>(istream& in, Reteta& r) {
		delete[] r.ingrediente;
		delete[] r.cantitatiIngrediente;
		cout << "\nIntroduceti numarul de ingrediente: ";
		in >> r.nrIngrediente;
		if (r.nrIngrediente <= 0) {
			r.nrIngrediente = 0;
			r.ingrediente = nullptr;
			r.cantitatiIngrediente = nullptr;
		}
		else {
			r.ingrediente = new MateriePrima[r.nrIngrediente];
			r.cantitatiIngrediente = new float[r.nrIngrediente];
			for (int i = 0; i < r.nrIngrediente; i++) {
				cout << "\nINGREDIENTUL "<<i+1<<": ";
				in.ignore();
				in >> r.ingrediente[i];
				cout << "\nIntroduceti cantitatea necesara de ingredient " << i + 1 << ": ";
				in >> r.cantitatiIngrediente[i];
			}
		}
		return in;
	}

	~Reteta() {
		delete[] this->ingrediente;
		delete[] this->cantitatiIngrediente;
		this->ingrediente = nullptr;
		this->cantitatiIngrediente = nullptr;
	}
};

class Produs {
private:
	char* numeProdus = nullptr;
	Reteta reteta;
	const float pretMaxim=100;
	float pret=0;
public:
	Produs() {
	}

	Produs(const char* numeProdus) {
		if (strlen(numeProdus) >= 2) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
	}

	Produs(const char* numeProdus, Reteta reteta, float pret){
		if (strlen(numeProdus) > 2) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
		this->reteta = reteta;
		if (pret <= this->pretMaxim)
			this->pret = pret;
		else
			throw exception("Pretul adaugat il depaseste pe cel maxim setat.(100 lei)");
	}
	
	void setNumeProdus(const char* numeProdus) {
		if (strlen(numeProdus) > 2) {
			this->numeProdus = new char[strlen(numeProdus) + 1];
			strcpy(this->numeProdus, numeProdus);
		}
	}

	void setReteta(Reteta reteta) {
		if(reteta.getNrIngrediente()>0)
		this->reteta = reteta;
	}

	void setPret(float pretNou) {
		if (pretNou > 5 && pretNou<=this->pretMaxim)
			this->pret = pretNou;
		else
			throw exception("Pretul adaugat il depaseste pe cel maxim setat.(100 lei)");
	}

	float getPret() const {
		return this->pret;
	}
	
	Reteta getReteta() const {
		return this->reteta;
	}

	char* getNumeProdus() const {
		return this->numeProdus;
	}


	Produs(const Produs& p){
		if (strlen(p.numeProdus) > 2) {
			this->numeProdus = new char[strlen(p.numeProdus) + 1];
			strcpy(this->numeProdus, p.numeProdus);
		}
		this->reteta = p.reteta;
		if (p.pret <= this->pretMaxim)
		this->pret = p.pret;
		else
			throw exception("Pretul adaugat il depaseste pe cel maxim setat.(100 lei)");
	}

	Produs& operator=(const Produs& p) {
		if (this != &p) {
			delete[] this->numeProdus;
			this->numeProdus = nullptr;
			if (strlen(p.numeProdus) > 2) {
				this->numeProdus = new char[strlen(p.numeProdus) + 1];
				strcpy(this->numeProdus, p.numeProdus);
			}
			this->reteta = p.reteta;
			if (p.pret <= this->pretMaxim)
			this->pret = p.pret;
			else
				throw exception("Pretul adaugat il depaseste pe cel maxim setat.(100 lei)");
		}
		return *this;
	}

	//++pre-incrementare
	Produs& operator++() {
		if(this->pret<this->pretMaxim)
		++this->pret;
		return *this;
	}

	//++post-incrementare
	Produs operator++(int) {
		Produs temp(*this);
		if (this->pret < this->pretMaxim)
		this->pret++;
		return temp;
	}
	
	//operatorul conditional <
	bool operator<(const Produs& p) const {
		return (this->pret < p.pret);
	}

	friend ostream& operator<<(ostream& out, Produs& p) {
		if (p.numeProdus != nullptr) {
			out << p.numeProdus;
		}
		out << "\nIngrediente: ";
		for (int i = 0; i < p.reteta.getNrIngrediente(); i++)
			out << p.reteta.getIngredient()[i].getNumeMatPrima() <<"-" << p.reteta[i]<<"; ";
		out << "   Pret: " << p.pret << " lei.";
		out << "\n-----------------";
		return out;
	}

	friend istream& operator>>(istream& in, Produs& p) {
		in.ignore();
		cout << "\nIntroduceti numele produsului: ";
		delete[] p.numeProdus;
		p.numeProdus = nullptr;
		string buffer;
		getline(in, buffer);
		p.numeProdus = new char[buffer.size() + 1];
		strcpy(p.numeProdus, buffer.data());
		in >> p.reteta;
		cout << "\nIntroduceti pretul produsului: ";
		in >> p.pret;
		if (p.pret <= 0)
			p.pret = 0;
		return in;
	}

	~Produs() {
		delete this->numeProdus;
		this->numeProdus = nullptr;
	}
};

class Comanda {
private:
	Produs* produse = nullptr;
	int nrProduse = 0;
public:
	Comanda() {}

	Comanda(int nrProduse) {
		if(nrProduse>0)
		this->nrProduse = nrProduse;
	}

	Comanda(int nrProduse, Produs* produse) {
		if (nrProduse <= 0) {
			this->nrProduse = 0;
			this->produse = nullptr;
		}
		else {
			this->nrProduse = nrProduse;
			this->produse = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produse[i] = produse[i];
		}
	}

	void setProdus(Produs produsNou) {
		if (strlen(produsNou.getNumeProdus()) > 3) {
			Produs* temp = new Produs[this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse; i++) {
				temp[i] = this->produse[i];
			}
			temp[this->nrProduse] = produsNou;
			delete[] this->produse;
			this->produse = temp;
			this->nrProduse++;
		}
	}

	//operatorul matematic +
	Comanda operator+(const Produs& produsNou) const {
		if (strlen(produsNou.getNumeProdus()) > 3) {
			Comanda result(*this);
			Produs* temp = new Produs[result.nrProduse + 1];
			for (int i = 0; i < result.nrProduse; i++) {
				temp[i] = result.produse[i];
			}
			temp[result.nrProduse] = produsNou;
			delete[] result.produse;
			result.produse = temp;
			result.nrProduse++;
			return result;
		}
	}

	Comanda& operator+=(const Produs& produsNou) {
		if (strlen(produsNou.getNumeProdus()) > 3) {
			Produs* temp = new Produs[this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse; i++) {
				temp[i] = this->produse[i];
			}
			temp[this->nrProduse] = produsNou;
			delete[] this->produse;
			this->produse = temp;
			this->nrProduse++;
			return *this;
		}
	}

	Produs* getProduse() const {
		return this->produse;
	}

	int getNrProduse() const {
		return this->nrProduse;
	}

	Comanda(const Comanda& c) {
		if (c.nrProduse <= 0) {
			this->nrProduse = 0;
			this->produse = nullptr;
		}
		else {
			this->nrProduse = c.nrProduse;
			this->produse = new Produs[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				this->produse[i] = c.produse[i];
		}
	}

	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->produse;
			this->produse = nullptr;
			if (c.nrProduse <= 0) {
				this->nrProduse = 0;
				this->produse = nullptr;
			}
			else {
				this->nrProduse = c.nrProduse;
				this->produse = new Produs[this->nrProduse];
				for (int i = 0; i < this->nrProduse; i++)
					this->produse[i] = c.produse[i];
			}
		}
		return *this;
	}

	//operatorul de indexare[]
	Produs& operator[](int index) {
		if (index >= 0 && index < this->nrProduse) {
			return this->produse[index];
		}
		else {
			throw exception("Indexul nu este in limita definita");
		}
	}

	friend ostream& operator<<(ostream& out, Comanda& c) {
		if(c.nrProduse>0){
			out << "\nProdusele comandate: \n";
			for (int i = 0; i < c.nrProduse; i++)
				out << c[i]<<endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c) {
		delete[] c.produse;
		cout << "\nIntroduceti numarul de produse din comanda: ";
		in >> c.nrProduse;
		if (c.nrProduse <= 0) {
			c.nrProduse = 0;
			c.produse = nullptr;
		}
		else {
			c.produse = new Produs[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++) {
				in >> c.produse[i];
			}
		}
		return in;
	}

	~Comanda() {
		delete[] this->produse;
		this->produse = nullptr;
	}
};

class Restaurant {
private:
	Produs* meniu = nullptr;
	int numarProduseInMeniu = 0;
	string numeRestaurant = " ";
public:
	Restaurant(){}

	Restaurant(string numeRestaurant) {
		this->numeRestaurant = numeRestaurant;
	}

	Restaurant(string numeRestaurant,Produs* meniu, int numarProduseInMeniu) {
		this->numeRestaurant = numeRestaurant;
		if (numarProduseInMeniu > 0 && meniu != nullptr) {
			this->numarProduseInMeniu = numarProduseInMeniu;
			this->meniu = new Produs[numarProduseInMeniu];
			for (int i = 0; i < numarProduseInMeniu; ++i) {
				this->meniu[i] = meniu[i];
			}
		}
	}

	Restaurant(const Restaurant& r) {
		this->numeRestaurant = r.numeRestaurant;
		if (r.numarProduseInMeniu > 0 && r.meniu != nullptr) {
			this->numarProduseInMeniu = r.numarProduseInMeniu;
			this->meniu = new Produs[r.numarProduseInMeniu];
			for (int i = 0; i < r.numarProduseInMeniu; ++i) {
				this->meniu[i] = r.meniu[i];
			}
		}
	}

	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			delete[] this->meniu;
			this->meniu = nullptr;
			this->numeRestaurant = r.numeRestaurant;
			if (r.numarProduseInMeniu > 0 && r.meniu != nullptr) {
				this->numarProduseInMeniu = r.numarProduseInMeniu;
				this->meniu = new Produs[r.numarProduseInMeniu];
				for (int i = 0; i < r.numarProduseInMeniu; ++i) {
					this->meniu[i] = r.meniu[i];
				}
			}
		}
		return *this;
	}

	string getNumeRestaurant() const {
		return this->numeRestaurant;
	}

	Produs* getProduseMeniu() const {
		return this->meniu;
	}

	int getNrProduseMeniu() const {
		return this->numarProduseInMeniu;
	}

	void setNumeRestaurant(string numeNou) {
		if (numeNou.length() > 2)
			this->numeRestaurant = numeNou;
	}

	void adaugaProdusInMeniu(const Produs& produs) {
		if (strlen(produs.getNumeProdus()) > 3) {
			Produs* temp = new Produs[this->numarProduseInMeniu + 1];
			for (int i = 0; i < this->numarProduseInMeniu; ++i) {
				temp[i] = this->meniu[i];
			}
			temp[this->numarProduseInMeniu] = produs;
			delete[] this->meniu;
			this->meniu = temp;
			this->numarProduseInMeniu++;
		}
	}

	Restaurant& operator+=(const Produs& produs) {
		if (strlen(produs.getNumeProdus()) > 3) {
			Produs* temp = new Produs[this->numarProduseInMeniu + 1];
			for (int i = 0; i < this->numarProduseInMeniu; ++i) {
				temp[i] = meniu[i];
			}
			temp[this->numarProduseInMeniu] = produs;
			delete[] this->meniu;
			this->meniu = temp;
			this->numarProduseInMeniu++;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Restaurant& r) {
		out << "\nMeniul restaurantului " << r.numeRestaurant <<" :\n"<< endl;
		for (int i = 0; i < r.numarProduseInMeniu; ++i) {
			out <<i+1<<". "<<r.meniu[i] << endl;
		}
		return out;
	}

	float calculeazaNotaDePlata(const Comanda& comanda) const {
		float notaDePlata = 0;
		for (int i = 0; i < comanda.getNrProduse(); i++)
			notaDePlata += comanda.getProduse()[i].getPret();
		return notaDePlata;
	}



	Comanda creareComanda() {
		Comanda comanda;
		int numarProduse;
		cout << "Introduceti numarul de produse dorite: ";
		cin >> numarProduse;
		vector<vector<float>> stocuriDisponibile(this->numarProduseInMeniu, vector<float>(MateriePrima::getNumarTotalMateriiPrime(), 0));
		for (int i = 0; i < numarProduse; ++i) {
			int index;
			cout << "Selectati un produs din meniu (introduceti indexul): ";
			cin >> index;
			int indexProdus = index - 1;
			if (indexProdus >= 0 && indexProdus < this->numarProduseInMeniu) {
				const Produs& produs = this->meniu[indexProdus];
				const Reteta& reteta = produs.getReteta();
				bool stocInsuficient = false;
				for (int j = 0; j < reteta.getNrIngrediente(); ++j) {
					MateriePrima& ingredient = reteta.getIngredient()[j];
					float cantitateNecesara = reteta.getCantitateIngredient()[j];
					if (cantitateNecesara > ingredient.getStocMatPrima() - stocuriDisponibile[indexProdus][j]) {
						stocInsuficient = true;
						break;
					}
				}

				if (!stocInsuficient) {
					for (int j = 0; j < reteta.getNrIngrediente(); ++j) {
						float cantitateNecesara = reteta.getCantitateIngredient()[j];
						stocuriDisponibile[indexProdus][j] += cantitateNecesara;
					}
					comanda += produs;
				}
				else {
					throw exception("\nStoc insuficient de materie prima pentru a finaliza comanda");
				}
			}
			else {
				throw exception("\nIndexul introdus nu exista in meniu.");
			}
		}
		return comanda;
	}



	
	friend istream& operator>>(istream& in, Restaurant& r) {
		delete[] r.meniu;
		cout << "\nIntroduceti numele restaurantului: ";
		getline(in,r.numeRestaurant);
		cout << "\nIntroduceti numarul de produse din meniu: ";
		in >> r.numarProduseInMeniu;
		if (r.numarProduseInMeniu <= 0) {
			r.numarProduseInMeniu = 0;
			r.meniu = nullptr;
		}
		else {
			r.meniu = new Produs[r.numarProduseInMeniu];
			for (int i = 0; i < r.numarProduseInMeniu; i++) {
				in >> r.meniu[i];
			}
		}
		return in;
	}
	
	~Restaurant() {
		delete[] this->meniu;
		this->meniu = nullptr;
	}
};

int main() {
	// Definirea materiilor prime
	MateriePrima faina("Faina", 5000);  // gram
	MateriePrima oua("Oua", 500);  // buc
	MateriePrima unt("Unt", 500);  // gram
	MateriePrima carneVita("Carne de vita", 2000);  // gram
	MateriePrima cartofi("Cartofi", 2000);  // gram
	MateriePrima smantana("Smantana", 400);  // ml
	MateriePrima ciocolata("Ciocolata", 600);  // gram
	MateriePrima zahar("Zahar", 1000);  // gram
	MateriePrima usturoi("Usturoi", 50);  // buc
	MateriePrima cafea("Cafea", 500);  // gram
	MateriePrima lapte("Lapte", 1000);  // ml
	MateriePrima ciuperci("Ciuperci", 400);  // gram
	MateriePrima bacon("Bacon", 300);  // gram
	MateriePrima paste("Paste", 1000);  // gram
	MateriePrima chifla("Chifla Burger", 1);  // buc
	MateriePrima tahini("Pasta de tahini", 850);  // gram
	MateriePrima lamaie("Lamaie", 50);  // buc
	MateriePrima naut("Naut", 400);  // gram
	MateriePrima uleiMasline("Ulei de masline", 80);  // ml
	MateriePrima apa("Apa", 2000);  // ml

	// Definirea vectorilor de ingrediente și cantități
	MateriePrima ingrediente1[] = { faina, oua, zahar };
	float cantitati1[] = { 400, 4, 200 };
	MateriePrima ingrediente2[] = { carneVita, cartofi };
	float cantitati2[] = { 300, 300 };
	MateriePrima ingrediente3[] = { faina, ciocolata, unt };
	float cantitati3[] = { 300, 100, 150 };
	MateriePrima ingrediente4[] = { cafea, smantana };
	float cantitati4[] = { 40, 50 };
	MateriePrima ingrediente5[] = { faina, oua, zahar, unt, ciocolata };
	float cantitati5[] = { 300, 3, 150, 100, 100 };
	MateriePrima ingrediente6[] = { carneVita, cartofi, usturoi };
	float cantitati6[] = { 400, 400, 3 };
	MateriePrima ingrediente7[] = { faina, oua, zahar, unt, ciocolata };
	float cantitati7[] = { 250, 4, 120, 80, 120 };
	MateriePrima ingrediente8[] = { cafea, smantana, zahar };
	float cantitati8[] = { 25, 60, 30 };
	MateriePrima ingrediente9[] = { paste, carneVita, smantana, usturoi };
	float cantitati9[] = { 200, 200, 50, 2 };
	MateriePrima ingrediente10[] = { chifla, carneVita, cartofi, smantana, bacon };
	float cantitati10[] = { 1, 150, 100, 30, 20 };
	MateriePrima ingrediente11[] = { tahini, naut, uleiMasline, usturoi };
	float cantitati11[] = { 100, 100, 20, 2 };
	MateriePrima ingrediente12[] = { lamaie, apa, zahar };
	float cantitati12[] = { 1, 300, 30 };

	// Definirea retetelor
	Reteta retetaPrajitura(3, ingrediente1, cantitati1);
	Reteta retetaFriptura(2, ingrediente2, cantitati2);
	Reteta retetaCiocolata(3, ingrediente3, cantitati3);
	Reteta retetaCafea(2, ingrediente4, cantitati4);
	Reteta retetaTiramisu(5, ingrediente5, cantitati5);
	Reteta retetaGulas(3, ingrediente6, cantitati6);
	Reteta retetaChec(5, ingrediente7, cantitati7);
	Reteta retetaCappuccino(3, ingrediente8, cantitati8);
	Reteta retetaPaste(4, ingrediente9, cantitati9);
	Reteta retetaBurger(5, ingrediente10, cantitati10);
	Reteta retetaHummus(4, ingrediente11, cantitati11);
	Reteta retetaLimonada(3, ingrediente12, cantitati12);

	// Crearea produselor
	Produs prajitura("Tort Diplomat", retetaPrajitura, 21);
	Produs friptura("Ribeye Steak", retetaFriptura, 97);
	Produs negresa("Negresa cu Ciocolata", retetaCiocolata, 19);
	Produs frappe("Frappe", retetaCafea, 17);
	Produs tiramisu("Tiramisu", retetaTiramisu, 25);
	Produs gulas("Gulas", retetaGulas, 43);
	Produs chec("Chec Pufos", retetaChec, 15);
	Produs cappucino("Cappuccino", retetaCappuccino, 18);
	Produs pasteAlfredo("Paste Alfredo", retetaPaste, 41);
	Produs burgerDeluxe("Burger Deluxe", retetaBurger, 55);
	Produs hummusTraditional("Hummus Melouk", retetaHummus, 30);
	Produs limonadaFresh("Limonada Clasica", retetaLimonada, 19);
	Produs meniu[] = {hummusTraditional,gulas, pasteAlfredo, burgerDeluxe, friptura, chec, prajitura, negresa,tiramisu};

	Restaurant restaurant("HMR Bistro", meniu, 9);
	restaurant += frappe;
	restaurant += cappucino;
	restaurant += limonadaFresh;
	
	cout << restaurant;
	try {
		Comanda comanda = restaurant.creareComanda();
		float notaDePlata = restaurant.calculeazaNotaDePlata(comanda);
		cout << comanda;
		cout << "Nota de plata: " << notaDePlata << " lei."<<endl;
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
	
	return 0;
}

