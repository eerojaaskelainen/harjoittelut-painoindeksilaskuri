// Painoindeksilaskuri.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "");

	Painoindeksilaskuri pi;

	pi.Main();

	return 0;
}

/*
T6)
Tee ohjelma, joka kysyy k‰ytt‰j‰lt‰ pituuden ja painon. Ohjelma laskee painoindeksin kaavalla
indeksi = paino / (pituus * pituus)
Paino annetaan kiloina ja pituus metrein‰.
Jos indeksi on 20-25, ohjelma toteaa sinut normaalipainoiseksi.
Jos indeksi on < 20, ohjelma ehdottaa syˆmisen lis‰‰mist‰. Jos indeksi on 25-30, ohjelma ehdottaa pient‰ liikunnan lis‰yst‰. Jos indeksi on yli 30, ohjelma kehottaa tekem‰‰n jotain radikaalia.

*/

/*
T16)
Kehit‰p‰ painoindeksi-ohjelmaa (T6) niin, ett‰ tiedot kysyt‰‰n tietueeseen, jossa on nimi, pituus, paino sek‰ paikka painoindeksille, joka lasketaan ohjelmassa.
Laskemisen j‰lkeen tulostetaan tietueen kaikki tiedot.


*/
Painoindeksilaskuri::Painoindeksilaskuri() {
	// Konstruktori: K‰y lataamassa tiedostosta asiakkaat. Jos haku ei onnistu, tulostetaan k‰ytt‰j‰lle virheilmoitus, mutta k‰ytt‰j‰ voi jatkaa:

	if (this->Lataa() == false) {
		cout << "Tiedoston lataus ei onnistunut!!!" << endl << "Voi olla ett‰ tiedosto on myˆs tyhj‰, mutta asiakkaita ei ole." << endl;
		system("pause");
	}

}

int Painoindeksilaskuri::Main()
{
	// Painonhallinnan p‰‰funktio: N‰ytt‰‰ p‰‰valikon, josta edet‰‰n suorittaviin funktioihin k‰ytt‰j‰n syˆtteen mukaisesti:

	int valinta = 0;		// Asiakkaan tekem‰ valinta syˆtet‰‰n

	do {
		system("cls");

		cout << "Painoindeksilaskuri" << endl
			<< "===================" << endl
			<< "      PƒƒVALIKKO " << endl << endl
			<< "Mit‰ haluat tehd‰:" << endl
			<< "1 : Lis‰‰ asiakas" << endl
			<< "2 : Laske indeksi (anonyymi)" << endl
			<< "3 : N‰yt‰ kaikki asiakkaat" << endl
			<< "0 : Lopeta ja tallenna" << endl
			<< endl << " Valintasi: ";

		cin >> valinta;
		cin.sync();

		switch (valinta)
		{
		case 1:	// Henkilˆn lis‰ys
			this->lisaaHenkilo();
			break;
		case 2:	// Anonyymi indeksin laskenta (ei tarvitse olla tallennettu)
			this->LaskeIndeksi();
			break;
		case 3:// Kaikkien asiakkaiden listaus:
			this->NaytaAsiakkaat();
			break;
		default:	// Muuten lopetetaan ohjelma. Ennen destructoria yritet‰‰n tallentaa asiakkaat tiedostoon:

			if (this->Lopeta() == false) {	// Tiedoston tallennus ei onnistunut. K‰ytt‰j‰ voi perua lopetuksen tai jatkaa menett‰en tiedot.
				cout << "Varoitus!!!" << endl
					<< "Asiakkaiden tallentaminen ep‰onnistui!" << endl
					<< "Haluatko lopettaa siit‰ huolimatta (K/E)? ";
				char vahvistus;
				cin >> vahvistus;
				if (vahvistus == 'E' || vahvistus == 'e') {
					valinta = -1;
				}
			}
			break;
		}


	} while (valinta != 0);

	return 0;
}

bool Painoindeksilaskuri::Lopeta() {
	//Asiakkaan poistuessa p‰‰valikosta ajetaan tallennus tiedostoon. Tallennuksen onnistuminen viestitet‰‰n boolean-paluuarvolla.
	if (this->Tallenna() == true) {
		return true;
	}
	else
		return false;

}
Painoindeksilaskuri::~Painoindeksilaskuri()
{

}

void Painoindeksilaskuri::LaskeIndeksi() {
	// Anonyymin painoindeksin kyselykaavake. Tulostaa tietojen kyselyn j‰lkeen painoindeksin sek‰ indeksin tulkinnan k‰ytt‰j‰lle.
	string syote = "";
	do {
		double pituus = 0.0;
		double paino = 0.0;
		int indeksi = 0;

		system("cls");
		cout << "Painoindeksin laskenta (anonyymi)" << endl
			<< "=================================" << endl
			<< "Anna pituus: ";
		cin >> syote;

		// Jos painon pituuden kohdassa annettiin 0; halutaan lopettaa.
		pituus = this->StringToDouble(syote);
		if (syote == "0") {
			break;
		}
		cout << "Anna paino: ";
		cin >> syote;
		paino = this->StringToDouble(syote);

		// Jos painon annon kohdassa annettiin 0; halutaan lopettaa.
		if (syote == "0") {
			break;
		}
		// Arvot saatu, lasketaan indeksi:
		indeksi = this->LaskeIndeksi(pituus, paino);
		cout << "Painoindeksisi on " << indeksi << "." << endl << this->IndeksinTulos(indeksi) << endl;

		system("pause");

	} while (syote != "0");
}

void Painoindeksilaskuri::lisaaHenkilo() {
	// Henkilˆn lis‰ysfunktio: Kysyt‰‰n k‰ytt‰j‰lt‰ henkilˆn tiedot ja talletetaan henkilˆt-vektoriin.

	Henkilo h;
	string input = "";

	system("cls");

	cout << "Henkilˆn lis‰ys" << endl
		<< "================" << endl
		<< "Anna uuden henkilˆn tiedot:" << endl;

	cout << "Sukunimi: "; getline(cin, input); h.sukunimi = input;
	cout << "Etunimi: "; getline(cin, input); h.etunimi = input;
	cout << "Pituus (m): "; getline(cin, input); h.pituus = this->StringToDouble(input);
	cout << "Paino (kg): "; getline(cin, input); h.paino = stod(input);

	int painoindeksi = this->LaskeIndeksi(h.pituus, h.paino);
	if (painoindeksi >0)
	{
		h.indeksi = painoindeksi;
		this->henkilot.push_back(h);
		cout << "Henkilˆ lis‰tty! \n(Henkilˆn painoindeksi on " << painoindeksi << " eli " << this->IndeksinTulos(painoindeksi) << ")" << endl;
	}

	else cout << "Painoindeksin laskenta ei onnistunut! Katso ett‰ pituus ja paino ovat kelvolliset (esim. pituus metrein‰)!";
	system("pause");

}






string Painoindeksilaskuri::IndeksinTulos(int indeksi) {
	// Painoindeksin tulkintafunktio. Palauttaa string -arvona viestin mit‰ argumenttina annettu painoindeksi tarkoittaa k‰yt‰nnˆss‰.

	if (indeksi < 20) {
		return "Olet alipainoinen! Lis‰‰ ruokaa!";
	}
	else if (indeksi <= 25) {
		return "Olet normaalipainoinen. Hyvin menee! Jatka samaan malliin!";
	}
	else if (indeksi < 30) {
		return "Melkein normaalin rajoissa mutta hieman yli. Ehdotan pient‰ liikunnan lis‰‰mist‰.";
	}
	else
	{
		return "Nyt menn‰‰n jo riskirajoilla! Reippaasti v‰hemm‰n ruokaa ja enemm‰n liikuntaa!";
	}
}

void Painoindeksilaskuri::NaytaAsiakkaat()
{
	// N‰ytet‰‰n kaikki vektorissa Henkilot -olevat asiakkaat. K‰ytt‰j‰ voi valita asiakkaista yhden, jonka tietoja tarkastelee.

	int valinta = 0;
	do {
		system("cls");
		cout << "Asiakkaamme" << endl
			<< "===========" << endl;

		for (int i = 0; i < henkilot.size(); i++) {
			cout << i + 1 << " : " << henkilot[i].sukunimi << " " << henkilot[i].etunimi << " = Pituus: " << henkilot[i].pituus << " m, Paino: " << henkilot[i].paino << " kg, Painoindeksi: " << henkilot[i].indeksi << endl;
		}
		cout << endl << "Valitse asiakas numero (0 jos haluat keskeytt‰‰): ";
		cin >> valinta;
		if (valinta > henkilot.size()) { cout << "valitse asiakkaan numero (v‰lilt‰ 1-" << henkilot.size() << "!" << endl; system("pause"); }
		else if (valinta <= 0) return;
		else {
			NaytaAsiakas(&henkilot[valinta - 1]);
		}
	} while (valinta != 0);
}

void Painoindeksilaskuri::NaytaAsiakas(Henkilo* asiakas) {
	// N‰ytt‰‰ argumenttina tulevan pointterin kohteena olevan henkilˆn tiedot. Asiakas voi myˆs halutessaan muuttaa tai poistaa kyseisen henkilˆn.

	system("cls");
	int valinta = 0;
	while (true) {
		cout << endl << "==============================================" << endl
			<< asiakas->etunimi << " " << asiakas->sukunimi << endl
			<< "--------------------------------" << endl
			<< "Pituus: " << asiakas->pituus << endl
			<< "Paino: " << asiakas->paino << endl
			<< "Painoindeksi: " << asiakas->indeksi << endl
			<< this->IndeksinTulos(asiakas->indeksi) << endl
			<< "===================================================" << endl << endl
			<< "Haluatko" << endl
			<< "1 : Muuttaa asiakkaan tietoja " << endl
			<< "2 : Poistaa asiakkaan?" << endl
			<< endl << "Valintasi: ";
		cin >> valinta;
		cin.sync();

		switch (valinta)
		{
		case 1: // Muutetaan asiakkaan tietoja:
			this->MuutaAsiakasta(asiakas);
			break;
		case 2: // Poistetaan asiakas
			for (vector<Henkilo>::iterator i = henkilot.begin(); i != henkilot.end(); ++i) {
				if (i._Ptr == asiakas){
					henkilot.erase(i);
					cout << "Asiakas poistettu.";
					break;
				}
			}

		default:	// Muussa tapauksessa lopetetaan funktio
			return;
			break;
		}
	}
}

void Painoindeksilaskuri::MuutaAsiakasta(Painoindeksilaskuri::Henkilo* asiakas) {
	// Muutetaan asiakkaan tietoja: K‰ytt‰j‰lle tulostetaan asiakkaan ominaisuudet, joita h‰n voi halutessaan muuttaa. Pelkk‰ rivinvaihto j‰tt‰‰ kyseisen arvon alkuper‰iseksi.

	system("cls");
	cout << "Muuta asiakkaan " << asiakas->etunimi << " " << asiakas->sukunimi << "tietoja" << endl
		<< "==============================================" << endl
		<< "J‰t‰ tyhjiksi ne osat, joita et halua muuttaa." << endl << endl;
	string input = "";

	cout << "Sukunimi (" << asiakas->sukunimi << "): "; getline(cin, input); if (input != "") asiakas->sukunimi = input;
	cout << "Etunimi (" << asiakas->etunimi << "): "; getline(cin, input); if (input != "") asiakas->etunimi = input;
	cout << "Pituus (" << asiakas->pituus << " m): "; getline(cin, input); if (input != "") asiakas->pituus = this->StringToDouble(input);
	cout << "Paino (" << asiakas->paino << " kg): "; getline(cin, input); if (input != "") asiakas->paino = this->StringToDouble(input);

}

double Painoindeksilaskuri::StringToDouble(string alkuperainen) {
	// Koska stod() -funktio ei suomenkielisess‰ lokaalissa ymm‰rr‰ muuttaa pistett‰ (.) desimaalierottimeksi, k‰yd‰‰n argumenttina tulleen muuttujan piste -merkit muuttamassa pilkuiksi (,) ja palautetaan
	// double -arvo

	double tallenna = 0.0;
	string muunnos = alkuperainen;
	for (int i = 0; i < muunnos.size(); i++) {
		if (muunnos[i] == '.') muunnos[i] = ',';
	}
	return stod(muunnos);

}


bool Painoindeksilaskuri::Tallenna() {
	// Henkilot -vektorin tallennus CSV -tiedostoon. Kyseinen tiedosto tyhjennet‰‰n, mink‰ j‰lkeen siihen lis‰t‰‰n jokainen vektorin yksilˆ per rivi (ominaisuudet eroteltuna puolipisteell‰)
	// Tallentaa onnistuessaan truen. Jos tiedostoa ei saatu auki, palauttaa falsen.

	if (this->henkilot.size() == 0) {
		//Ei asiakkaita, ei tallennusta mutta palautetaan ookoo.
		return true;
	}

	ofstream talletus(this->asiakastiedosto, ios::out);

	if (talletus.is_open()) {

		for each (auto asiakas in this->henkilot) {		// Jokainen vektorin yksilˆ k‰yd‰‰n l‰pi, ja vied‰‰n siit‰ oleelliset muuttujat tiedostoon. Painoindeksi luodaan pituudesta ja painosta, joten sit‰ ei tarvitse tallentaa erikseen.
			talletus
				<< asiakas.sukunimi << ";"
				<< asiakas.etunimi << ";"
				<< asiakas.pituus << ";"
				<< asiakas.paino << ";" << endl;
		}

		talletus.close();
		return true;
	}
	else
		return false;

}



bool Painoindeksilaskuri::Lataa() {
	// Henkilˆt -vektorin t‰yttˆ tiedostosta
	// Jokainen tiedoston rivi on yksi henkilˆ. T‰m‰ rivi puretaan ja siin‰ olevat ominaisuudet (eroteltuna puolipisteell‰) talletetaan uutena Henkilo -struktina vektoriin.
	// Palauttaa onnistuessaan (vektorissa ainakin yksi yksilˆ) truen, muuten falsen.
	Henkilo h;

	ifstream lataus(this->asiakastiedosto);
	string rivi;

	if (lataus.is_open())
	{
		while (getline(lataus, rivi))
		{
			vector<string> ominaisuudet = this->pilkorivi(rivi);
			if (ominaisuudet.size() > 0) {
				h.sukunimi = ominaisuudet[0];
				h.etunimi = ominaisuudet[1];
				h.pituus = this->StringToDouble(ominaisuudet[2]);
				h.paino = this->StringToDouble(ominaisuudet[3]);

				h.indeksi = this->LaskeIndeksi(h.pituus, h.paino);
				this->henkilot.push_back(h);
			}
		}


		lataus.close();
	}

	if (this->henkilot.size() == 0){
		return false;
	}
	else {
		return true;
	}
}

vector<string> Painoindeksilaskuri::pilkorivi(string rivi){
	char erotin = ';';
	vector < string > tiedot;
	string buffer = "";

	for (int i = 0; i < rivi.size(); i++) {
		if (rivi[i] != erotin) {
			buffer.push_back(rivi[i]);
		}
		else {
			tiedot.push_back(buffer);
			buffer = "";
		}
	}

	return tiedot;
};