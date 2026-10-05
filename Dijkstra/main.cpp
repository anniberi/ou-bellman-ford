#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <fstream>

// Ovaj program implementira Dijkstrin algoritam
// Graf je opisan listom susjedstva (adjecency list)

int main() {

    //***********************************************************************
    // Dodajemo rad sa tokovima kako bi upis i ispis rezultata bili laksi :D
    // Da bi kod radio na vasem racunaru potrebno je path editovati u sljedece dvije linije
    // upis.txt dolazi kao prilog kodovima :D
    std::ifstream fin("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/upis.txt");
    std::ofstream fout("/home/anniberi/Documents/Fakultet/2. semestar/OU/Seminarski/Rezultati simulacije/ispis_Dijkstra.txt");

    // Prvo inicijaliziramo varijable za broj cvorova i ivica:
    int br_cvorova, br_ivica;
    fout << "Unesi broj cvorova:" << std::endl;
    fin >> br_cvorova;
    fout << "Unesi broj ivica:" << std::endl;
    fin >> br_ivica;

    // Sada unosimo susjedstva cvorova (graf je usmjeren):
    std::vector<std::vector<std::pair<int, int> > > susjedstva(br_cvorova);

    // Unosimo graf:
    fout << "Unesi pocetni i krajnji cvor i tezinu ivice (tezine ne smiju biti negativne):\n";
    fout << "Oznake za cvorove su od 0 do " << br_cvorova - 1 << ".\n";
    for(int i = 0; i < br_ivica; i++) {
        int pocetni, krajnji, tezina;
        fin >> pocetni >> krajnji >> tezina;
        susjedstva.at(pocetni).push_back(std::make_pair(krajnji, tezina));
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
    // Dijkstra sada pocinje

    // Pravimo priority queue da bismo znali koji je preostali cvor najblizi pocetnom
    // Ovako ide konstrukcija ako zelimo da priority queue daje prednost najmanjem, a ne najvecem
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > iduci_cvor;
    std::vector<bool> posjecen(br_cvorova, false);

    // Pocetni cvor je uvijek 0 udaljen od samog sebe:
    iduci_cvor.push(std::make_pair(0, pocetni_cvor));
    int udaljenost = -1;

    int broj_iteracija = 0;
    std::pair<int, int> trenutni_cvor;
    while(!iduci_cvor.empty()) {
        trenutni_cvor = iduci_cvor.top();
        iduci_cvor.pop();
        if(posjecen.at(trenutni_cvor.second)) continue;
        posjecen.at(trenutni_cvor.second) = true;
        if(trenutni_cvor.second == krajnji_cvor) {
            udaljenost = trenutni_cvor.first;
        }
        // Moramo proci kroz sve susjede od trenutni_cvor.first
        for(auto x : susjedstva.at(trenutni_cvor.second)) {
            if(posjecen.at(x.first)) continue;
            iduci_cvor.push(std::make_pair(trenutni_cvor.first + x.second, x.first));
            broj_iteracija++;
        }
    }

    fout << "****************************************************" << std::endl;
    if(udaljenost < 0)
        fout << "Ne postoji put od cvora " << pocetni_cvor << " do " << krajnji_cvor << "." << std::endl;
    else {
        fout << "Najkraca distanca od " << pocetni_cvor << "-og do " << krajnji_cvor << "-og cvora iznosi: " << udaljenost << "." << std::endl;
        fout << std::endl;
        fout << "Kompleksnost Dijkstra algoritma je O(broj ivica + broj cvorova * log(broj cvorova)) u najgorem slucaju." << std::endl;
        fout << "Izracunata je samo potrebna distanca." << std::endl;
        fout << std::endl;
        fout << "Broj iteracija algoritma je bio " << broj_iteracija << " (jedna iteracija je poredjenje dvije vrijednosti duzina)." << std::endl;
        fout << "****************************************************" << std::endl;
    }

    return 0;
}
