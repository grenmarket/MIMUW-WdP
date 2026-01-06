# Liczby kolosalne

1. Plik config

Tutaj znajdują się wszystkie ustawienia. Przede wszystkim trzeba ustawić tu nazwę pliku z kodem źródłowym swojego programu.
Do tego można tu zmienić też limity testów, kompilator i ścieżki do folderów

WAŻNE!!! Aby wszystko działało poprawnie, ZA KAŻDYM RAZEM przy odpaleniu terminala, należy uruchomić komendę `source config`

2. Makefile

make -s / make testall - puszcza make build, make test i make testmem
make test - puszcza wszystkie testy (bez valgrinda)
make testmem - puszcza 5 testów z każdej kategorii z valgrindem
make build - kompiluje program

3. tester.sh (alias: test)

Użycie:
test [paczka] [valgrind (true|false)] [limit]

4. c.sh (alias: c)

Oblicza wartość liczby kolosalnej w systemie dziesiętnym. Jest to skrót do komendy z uwag z Moodle'a, więc działa tylko dla małych liczb

Użycie:
c [kolosalna]

5. h.sh (alias: h)

Zwraca liczbę kolosalną jako ciąg operacji, ułatwia czytanie liczb kolosalnych
Użycie:
h [kolosalna]

6. l.sh (alias: l)

Oblicza znormalizowaną liczbę kolosalną na podstawie danej liczby w systemie dziesiętnym

Użycie:
l [liczba]