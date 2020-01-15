# AAL_Projekt

Projekt na przedmiot AAL,
autor: Robert Ostoja - Lniski, Eiti PW.

Specyfikacja:
Rozwiązanie problemu przydziału pracowników do projektów na podstawie sieci przepływowej przy
użyciu algorytmu BFS oraz reprezentacji grafu w postaci wektora wektorów.
Każdy pracownik należy do danego jednego działu i bierze udział w dowolnej ilości projektów.
Należy wybrać przedstawicieli do projektów, w taki sposób aby w wybranych zbiorze pracowników
nie było ponad połowy pracowników z tego samego działu. Jeden pracownik może być przedstawicielem
tylko jednego projektu.

Projekt:
Projekt składa się z katalogów
bin - tutaj znajdują się pliki binarne dla 
  a) programu
  b) testów jednostkowych
  
scripts - tutaj znajdują się skrypty do
  a) kompilacji
  b) wykonania i sprawdzenia testów jednostkowych
  c) wygenerowania danych testowych
  d) zebrania iformacji o czasie wykonania programu dla danych testowych
  
include - pliki nagłówkowe

source - pliki źródłowe

testing - programy do testowania, testy jednostkowe oraz dane testowe

Program jest rozwiązany przy użyciu algorytmu forda fulkersona obługującego grafy
skierowane oraz nieskierowane. Przeszukiwanie grafu jest liniowe w oparciu o 
algorytm BFS, złożoność problemu to 0(n^3). Dodatkowo w celu ułatwienia przetwarzania
danych znajdują się klasy pomocnicze.


Na branchu Master jest rozwiązanie problemu algorytmicznego, dodatki ( generatory testów, narzędzia do wizualizacji )
znajdują się na branchu files organising.

Rozwiązanie projektu jest oparte na algorytmie Forda-Fulkersona i BFS ( wyznaczany jest maksymalny przepływ w grafie ).

Aby uruchomić program na branchu master wystarczy skompilować pliki *.src

Aby w pełni przetestować program i wygenerować raporty trzeba:

1) przejść na branch files_organising

2) przejść do folderu scripts

3) uruchomić skrypt compile.sh 
  -> kompilacja plików źródłowych
  -> utworzenie pliku a.out w katalogu bin
  
5) uruchomić skrypt make_test.sh
  -> generowanie testów ( ich liczba jest zdefiniowana w pliku testing/test_app/test.cpp )
  -> testy znajduja sie w folderze testing
  
6) uruchomić skrypt gather_data.sh <liczba_testow> liczba testow powinna wynosic o jeden mniej niz liczba 
zdefiniowana w pliku testing/test_app/test.cpp

7) w folderze visualisation znajdują się raporty do wygenerowania wykresu.

8) Należy otworzyć w programie jupyter-notebook skrypt AAL_Visualisation, w zakładce kernel wybrać opcję Restart & Run All
