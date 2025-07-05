#!/bin/bash

args="5 800 200 200 7"
expected="All philosophers have eaten 7 times !"

# Exécute le programme avec les arguments
../philo $args > output.txt
wait $!

# Lit l'avant avant dernière ligne du fichier et vérifie si elle contient le message attendu
actual=$(tail -n 4 output.txt | head -n 1 | tr -d '\r' | sed 's/\x1b\[[0-9;]*m//g')
expected=$(echo -n "$expected" | tr -d '\r')

if [ "$actual" = "$expected" ]; then
    echo -e "\033[32mTest réussi ✓\033[0m"
    rm output.txt
    exit 0
else
    echo -e "\033[31mTest échoué ✗\033[0m"
    echo "Sortie attendue: >$expected<"
    echo "Sortie reçue: >$actual<"
    rm output.txt
    exit 1
fi