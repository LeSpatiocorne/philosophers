#!/bin/bash

mkdir -p results
LOGFILE_DIE="results/logtest_die"
LOGFILE_ALIVE="results/logtest_alive"

> "$LOGFILE_DIE"
> "$LOGFILE_ALIVE"

function run_tests() {
	local file="$1"
	local log="$2"

	echo "Execution of the tests in $file"
	while IFS= read -r line || [ -n "$line" ]; do
		echo -n "testing \"$line\" : "
		echo "Exécution : $line" >> "$log"
		
		# Remplace seulement './philo' par '../philo' sans toucher à timeout ou autre
		cmd=$(echo "$line" | sed 's|^\(.*\)\./philo|\1../philo|')

		# Exécution et nettoyage des couleurs ANSI
		eval "$cmd" | sed 's/\x1b\[[0-9;]*[a-zA-Z]//g' >> "$log" 2>&1

		echo "complete"
		echo "-----------------------------" >> "$log"
		echo "---------END OF TEST---------" >> "$log"
		echo "-----------------------------" >> "$log"
	done < "$file"
}

run_tests die_tests "$LOGFILE_DIE"
run_tests alive_tests "$LOGFILE_ALIVE"
