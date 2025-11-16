gcc-15 @opcje wielomiany.c -o wielomiany

num="0"
passed="0"
for t in *.in
do
    ./wielomiany < "$t" > "w${t%in}out"
    if diff "${t%in}out" "w${t%in}out"
    then
        passed=$((passed + 1))
    else
        echo --- "${t%.in}" ---
    fi
    num=$((num + 1))
done
echo "${num} - liczba testow"
echo "${passed} testow zakonczonych sukcesem"

rm wielomiany 2>/dev/null
