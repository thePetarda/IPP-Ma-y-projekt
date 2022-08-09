#!/usr/bin/bash
gcc -o projekt projekt.c
for f in example5.in; do ./projekt <"$f" > "${f%in}mout"; echo "Plik: $f Kod: $?."; done
# for f in error*.in; do ./projekt <"$f" > "${f%in}mout"; echo "Plik: $f Kod: $?."; done

# for f in *.in; do echo "Plik: $f"; if diff "${f%in}err" "${f%in}mout"; then echo "NICE"; else echo "UGH"; fi; done 
