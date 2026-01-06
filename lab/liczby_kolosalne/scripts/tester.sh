#!/bin/bash

# Testerka została zrrobiona na bazie testerki Igancego do zadania Algorytm X

program=$EXE

subdir=$1
memcheck=$2
limit=$3

passed=0
failed=0

for t in $TESTS_DIR/$subdir/*.in
do
    if ( [ "$memcheck" = "false" ] && $program < $t > wynik.out ) || \
       ( [ "$memcheck" != "false" ] && valgrind --leak-check=full -q --error-exitcode=1 $program < $t > wynik.out )
    then
        if diff -q "${t%in}out" wynik.out
        then
            passed=$((passed + 1))
        else
            diff "${t%in}out" wynik.out -y
            failed=$((failed + 1))
        fi
    else
        echo valgrind zgłasza błąd w teście ${t%.in}
    fi

    if (( limit <= passed + failed )); then
            break
    fi
done

rm wynik.out 2>/dev/null

echo Passed: $passed / Failed: $failed