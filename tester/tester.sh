#!/bin/bash

# Couleurs pour l'affichage
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

echo -e "\n=== Tests des cas où le philosophe doit mourir ===\n"

# Exécute tous les tests dans le dossier should_die
for test in eval_sheet/*.sh; do
    echo -n "Test $(basename $test): "
    bash "$test"
done
