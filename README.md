# AAL_Projekt

Projekt na przedmiot AAL,
autor: Robert Ostoja - Lniski PW.

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
