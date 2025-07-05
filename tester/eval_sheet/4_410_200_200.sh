#!/bin/bash

args="4 410 200 200"

# Exécute le programme avec les arguments et un timeout de 30 secondes
timeout 30s ../philo $args > output.txt
status=$?

# Vérifie si le programme s'est terminé par timeout
if [ $status -eq 124 ]; then
    echo -e "\033[31mTest échoué ✗\033[0m"
    echo "Le programme n'a pas terminé après 30 secondes"
	cat output.txt
    rm output.txt
    exit 1
fi

# Vérifie qu'il n'y a pas de message de mort
if grep -q "est mort" output.txt; then
    echo -e "\033[31mTest échoué ✗\033[0m"
    echo "Un philosophe est mort alors qu'il ne devrait pas"
    rm output.txt
    exit 1
else
    echo -e "\033[32mTest réussi ✓\033[0m"
    rm output.txt
    exit 0
fi
