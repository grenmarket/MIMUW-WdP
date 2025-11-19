#!/bin/bash

# Skrypt testujący program ze ścieżki zdefiniowanej na zmiennej $program.
#
# Zakłada, że testy w plikach *.in i odpowiadające im wyniki w plikach *.out 
# znajdują się w podkatalogu testy.
#
# Test uznaje się za zaliczony, jeśli valgrind nie zgłosi błędu i wynik jest 
# zgodny z oczekiwanym.


program=./algorytm_x
wszystkie=0
zaliczone=0

for t in testy/*.in
do
    echo --- ${t%.in} ---
    wszystkie=$((wszystkie + 1))
    if valgrind --leak-check=full -q --error-exitcode=1 $program < $t > wynik.out
    then
        if diff -q "${t%in}out" wynik.out
        then
            zaliczone=$((zaliczone + 1))
            echo zaliczony
        else
            diff "${t%in}out" wynik.out
            echo niezaliczony
        fi
    else
        echo valgrind zgłasza błąd
    fi
done

echo "Zaliczone ${zaliczone} z ${wszystkie} testów"

rm wynik.out 2>/dev/null
