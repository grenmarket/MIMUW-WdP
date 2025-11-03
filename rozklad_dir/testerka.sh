gcc rozklad.c -o roz

echo "Autor: Slawomir Blicharz"
num="0"
passed="0"
for t in *.in
do
    echo --- "${t%.in}" ---
    ./roz < "$t" > wynik.out
    if diff "${t%in}out" wynik.out
    then
        echo zaliczony
        passed=$((passed + 1))
    else
        echo niezaliczony
        diff "${t%in}out" wynik.out
    fi
    num=$((num + 1))
done
echo "${num} - liczba testow"
echo "${passed} testow zakonczonych sukcesem"

rm wynik.out 2>/dev/null
rm roz 2>/dev/null