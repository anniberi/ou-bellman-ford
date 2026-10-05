# Bellman-Ford Algorithm for Optimal Path Finding

A study of the Bellman-Ford shortest-path algorithm, covering its mathematical proof, pseudocode and complexity analysis, along with C++ implementations of Bellman-Ford, Dijkstra and Floyd-Warshall that run on the same test graph. The paper compares the three algorithms by iteration count and asymptotic complexity, and it shows why Bellman-Ford remains the right tool when a graph has negative edge weights or negative cycles.

> **Note:** Apart from this summary, everything in this project is written in Bosnian: the rest of this README, the source code, the comments and the technical documentation.

> **Napomena:** Izvorni kod, komentari i tehnička dokumentacija za ovaj projekat su napisani na bosanskom jeziku.

## O projektu

Seminarski rad izrađen na Odsjeku za automatiku i elektroniku Elektrotehničkog fakulteta Univerziteta u Sarajevu (2023. godina).

U mnogim primjenama teorije grafova potrebno je pronaći najkraći put (optimalnu stazu) između dva zadana čvora. Rad daje pregled Bellman-Fordovog algoritma:

- definiše terminologiju i notaciju te daje matematički dokaz i pseudokod algoritma;
- analizira kompleksnost algoritma, koja u najgorem slučaju iznosi O(|V| · |E|);
- poredi Bellman-Fordov algoritam s Dijkstrinim i Floyd-Warshallovim algoritmom i ističe prednosti i ograničenja svakog od njih.

Ključni zaključak: Dijkstrin algoritam je najbrži, ali ne radi s negativnim težinama grana. Bellman-Fordov algoritam može detektovati negativne cikluse. Floyd-Warshallov algoritam ih također može detektovati, ali za tu namjenu zahtijeva modifikaciju.

## Struktura repozitorija

```
.
├── BellmanFord/          # C++ implementacija Bellman-Fordovog algoritma (lista ivica)
├── Dijkstra/             # C++ implementacija Dijkstrinog algoritma (lista susjedstva, prioritetni red)
├── FloydWarshall/        # C++ implementacija Floyd-Warshallovog algoritma (matrica udaljenosti)
├── Generisanje grafova/  # Jupyter notebook za grafove procijenjenog broja iteracija
├── Izvjestaj/            # LaTeX izvorni kod rada (IEEE konferencijski format) i slike
├── upis.txt              # Testni graf koji koriste sve tri implementacije
└── OU_Seminarski_Ahmed_Imamovic_Berina_Biberovic.pdf   # Finalna verzija rada
```

Svaki direktorij s implementacijom sadrži `main.cpp` i projektnu datoteku za Code::Blocks (`.cbp`).

## Format ulazne datoteke

Datoteka `upis.txt` opisuje usmjereni težinski graf:

1. prva linija sadrži broj čvorova;
2. druga linija sadrži broj ivica;
3. svaka sljedeća linija opisuje jednu ivicu u obliku `početni_čvor krajnji_čvor težina`;
4. posljednje dvije linije sadrže indeks početnog i indeks krajnjeg čvora.

Priloženi primjer opisuje graf s 12 čvorova i 23 ivice, a traži se najkraći put od čvora 0 do čvora 11.

## Pokretanje

Programi čitaju ulaz iz datoteke i upisuju rezultat u izlaznu `.txt` datoteku. Putanje do tih datoteka su apsolutne i zadane na početku funkcije `main` (`std::ifstream fin` i `std::ofstream fout`). Prije pokretanja ih je potrebno prilagoditi vlastitom računaru, na primjer:

```cpp
std::ifstream fin("../upis.txt");
std::ofstream fout("ispis_Bellman_Ford.txt");
```

Prevođenje i pokretanje iz komandne linije (primjer za Bellman-Ford):

```bash
cd BellmanFord
g++ -std=c++11 -O2 main.cpp -o BellmanFord
./BellmanFord
```

Alternativno, projekat se može otvoriti u okruženju Code::Blocks preko odgovarajuće `.cbp` datoteke. Ako se `fin` i `fout` zamijene sa `std::cin` i `std::cout`, programi rade s konzolnim ulazom i izlazom.

### Generisanje grafova

Notebook `Generisanje grafova/generisi grafove.ipynb` koristi `numpy` i `matplotlib`. Poredi procijenjeni broj iteracija sva tri algoritma za „prosječan" graf, kod kojeg je broj ivica |E| ≈ |V|·√|V|:

```bash
pip install numpy matplotlib jupyter
jupyter notebook "Generisanje grafova/generisi grafove.ipynb"
```

### Prevođenje rada

Rad koristi paket `minted`, pa je za prevođenje potreban Python paket `Pygments` i opcija `-shell-escape`:

```bash
cd Izvjestaj
pdflatex -shell-escape conference_101719.tex
biber conference_101719
pdflatex -shell-escape conference_101719.tex
```

## Metodologija

- Sva tri algoritma implementirana su u jeziku C++. Kompajlirani jezik bez *garbage collector*-a daje pouzdanije vrijeme izvršavanja.
- Pošto su testni grafovi mali i vrijeme izvršavanja se ne može precizno izmjeriti, algoritmi se porede prema **broju iteracija**, gdje je jedna iteracija jedno poređenje dvije vrijednosti dužina.
- Bellman-Fordova implementacija prekida rad čim u nekoj iteraciji nema ažuriranja udaljenosti. Dodatnim prolazom kroz sve ivice provjerava postojanje negativnih ciklusa.
- Teorijska poređenja kompleksnosti prikazana su grafički za grafove do 100 i do 1000 čvorova.

## Autori

- Berina Biberović
- Ahmed Imamović

Elektrotehnički fakultet, Univerzitet u Sarajevu, Odsjek za automatiku i elektroniku
