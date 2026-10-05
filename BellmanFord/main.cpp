#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

// Ovaj program implementira Bellman-Ford algoritam
// Graf je opisan listom ivica (edge list)

int main() {

    //***********************************************************************
    // Dodajemo rad sa tokovima kako bi upis i ispis rezultata bili laksi :D
    // Da bi kod radio na vasem racunaru potrebno je path editovati u sljedece dvije linije
    // upis.txt dolazi kao prilog kodovima :D
    std::ifstream fin("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/upis.txt");
    std::ofstream fout("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/Rezultati simulacije/ispis_Bellman_Ford.txt");

    // Prvo inicijaliziramo varijable za broj cvorova i ivica:
    int br_cvorova, br_ivica;
    fout << "Unesi broj cvorova:" << std::endl;
    fin >> br_cvorova;
    fout << "Unesi broj ivica:" << std::endl;
    fin >> br_ivica;

    // Sada unosimo ivice (graf je usmjeren):
    std::vector<std::pair<int, int> > ivice(br_ivica);
    std::vector<int> tezine_ivica(br_ivica);

    // Unosimo graf:
    fout << "Unesi pocetni i krajnji cvor i tezinu ivice:\n";
    fout << "Oznake za cvorove su od 0 do " << br_cvorova - 1 << ".\n";
    for(int i = 0; i < br_ivica; i++) {
        int pocetni, krajnji, tezina;
        fin >> pocetni >> krajnji >> tezina;
        ivice.at(i) = std::make_pair(pocetni, krajnji);
        tezine_ivica.at(i) = tezina;
    }
    // Sada imamo graf u memoriji

    // Treba unijeti koji put zelimo :D
    fout << "Upisi indeks pocetnog cvora:" << std::endl;
    int pocetni_cvor;
    fin >> pocetni_cvor;

    fout << "Upisi indeks krajnjeg cvora:" << std::endl;
    int krajnji_cvor;
    fin >> krajnji_cvor;

    //************************************************************************
    // Bellman-Ford sada pocinje

    // Za svaki cvor se pamtni koliko je udaljen od pocetnog cvora
    // Inicijalizirani su na 2^29 (beskonacno za nase svrhe)
    std::vector<int> distance(br_cvorova, 1 << 29);
    // Za pocetni cvor znamo da nije beskonacno udaljen od samog sebe:
    distance.at(pocetni_cvor) = 0;

    int broj_iteracija = 0;
    for(int i = 0; i < br_cvorova - 1; i++) {
        bool flag = false;
        for(int j = 0; j < br_ivica; j++) {
            if(distance.at(ivice.at(j).first) + tezine_ivica.at(j) <  distance.at(ivice.at(j).second)) {
                distance.at(ivice.at(j).second) = distance.at(ivice.at(j).first) + tezine_ivica.at(j);
                flag = true;
            }
            broj_iteracija++;
        }
        if(!flag) break;
    }

    bool flag_neg_ciklusi = false;
    for(int j = 0; j < br_ivica; j++) {
        if(distance.at(ivice.at(j).first) + tezine_ivica.at(j) <  distance.at(ivice.at(j).second)) {
            flag_neg_ciklusi = true;
        }
        broj_iteracija++;
    }


    fout << "****************************************************" << std::endl;
    if(flag_neg_ciklusi)
        fout << "Postoje negativni ciklusi u grafu!" << std::endl;
    else {
        fout << "Najkraca distanca od " << pocetni_cvor << "-og do " << krajnji_cvor << "-og cvora iznosi: " << distance.at(krajnji_cvor) << "." << std::endl;
        fout << "U grafu nema negativnih ciklusa." << std::endl;
    }
    fout << std::endl;
    fout << "Kompleksnost Bellman-Ford algoritma je O(broj cvorova * broj ivica) u najgorem slucaju." << std::endl;
    fout << "Izracunate su najkrace udaljenosti od pocetnog do svakog drugog cvora." << std::endl;
    fout << std::endl;
    fout << "Broj iteracija algoritma je bio " << broj_iteracija << " (jedna iteracija je poredjenje dvije vrijednosti duzina)." << std::endl;
    fout << "****************************************************" << std::endl;

    return 0;
}
