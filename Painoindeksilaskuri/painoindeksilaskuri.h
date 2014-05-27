#pragma once
#include <vector>
#include <map>
#include <fstream>

class Painoindeksilaskuri
{
private:
	struct Henkilo {
		string sukunimi = "";
		string etunimi = "";
		double pituus = 0.0;
		double paino = 0.0;
		int indeksi = 0;

	};

	vector < Henkilo > henkilot;
	const string asiakastiedosto = "Asiakkaat.csv";

public:
	Painoindeksilaskuri();
	~Painoindeksilaskuri();
	int Main();
	void LaskeIndeksi();
			
private:
	void lisaaHenkilo();
	bool lisaaHenkilo(map<string, string> ominaisuudet);
	int LaskeIndeksi(Henkilo);										// Jos halutaan laskea käyttäjän indeksi

	int LaskeIndeksi(double pituus, double paino) { // Jos halutaan laskea indeksi ilman käyttäjätietoa
		if (pituus > 0.0 && paino > 0.0) return static_cast<int>(paino / (pituus*pituus));
		else return -1;
	}
	string IndeksinTulos(int indeksi);		// Palauttaa string-muodossa arvion, mikä on argumenttina annetun painoindeksin kertoma
	void NaytaAsiakkaat();
	void NaytaAsiakas(Henkilo* asiakas);
	void MuutaAsiakasta(Henkilo * asiakas);
	
	double StringToDouble(string);

	bool Lopeta();
	bool Tallenna();
	bool Lataa();
	vector<string> pilkorivi(string rivi);
};

