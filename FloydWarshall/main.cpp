#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <fstream>

// Ovaj program implementira Floyd-Warshall algoritam
// Graf je opisan matricom susjedstva

int main() {

    //***********************************************************************
    // Dodajemo rad sa tokovima kako bi upis i ispis rezultata bili laksi :D
    // Da bi kod radio na vasem racunaru potrebno je path editovati u sljedece dvije linije
    // upis.txt dolazi kao prilog kodovima :D
    std::ifstream fin("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/upis.txt");
    std::ofstream fout("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/Rezultati simulacije/ispis_Floyd_Warshall.txt");

    // Prvo inicijaliziramo varijable za broj cvorova i ivica:
    int br_cvorova, br_ivica;
    fout << "Unesi broj cvorova:" << std::endl;
    fin >> br_cvorova;
    fout << "Unesi broj ivica:" << std::endl;
    fin >> br_ivica;

    // Sada unosimo susjedstva cvorova (graf je usmjeren):
    std::vector<std::vector<int> > matrica_udaljenosti(br_cvorova, std::vector<int>(br_cvorova, 1 << 29));

    // Unosimo graf:
    fout << "Unesi pocetni i krajnji cvor i tezinu ivice:\n";
    fout << "Oznake za cvorove su od 0 do " << br_cvorova - 1 << ".\n";
    for(int i = 0; i < br_ivica; i++) {
        int pocetni, krajnji, tezina;
        fin >> pocetni >> krajnji >> tezina;
        matrica_udaljenosti.at(pocetni).at(krajnji) = tezina;
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
    // Floyd-Warshall sada pocinje

    int broj_iteracija = 0;
    for(int i = 0; i < br_cvorova; i++) {
        for(int j = 0; j < br_cvorova; j++) {
            for(int k = 0; k < br_cvorova; k++) {
                if(matrica_udaljenosti.at(i).at(j) + matrica_udaljenosti.at(j).at(k) < matrica_udaljenosti.at(i).at(k))
                    matrica_udaljenosti.at(i).at(k) = matrica_udaljenosti.at(i).at(j) + matrica_udaljenosti.at(j).at(k);
                broj_iteracija++;
            }
        }
    }

    fout << "****************************************************" << std::endl;
    fout << "Najkraca distanca od " << pocetni_cvor << "-og do " << krajnji_cvor << "-og cvora iznosi: " << matrica_udaljenosti.at(pocetni_cvor).at(krajnji_cvor) << "." << std::endl;
    fout << std::endl;
    fout << "Kompleksnost Floyd-Marshall algoritma je O((broj cvorova)^3) u najgorem slucaju." << std::endl;
    fout << "Izracunate su najkrace udaljenosti od svakog pocetnog do svakog drugog cvora." << std::endl;
    fout << std::endl;
    fout << "Broj iteracija algoritma je bio " << broj_iteracija << " (jedna iteracija je poredjenje dvije vrijednosti duzina)." << std::endl;
    fout << "****************************************************" << std::endl;

    return 0;
}
