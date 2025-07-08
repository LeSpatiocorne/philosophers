# Philosophers
This project is the well know dining philosophers problem.
The idea behind this project is to understand and experiment the management of multiple process working at the same time without causing them to block each other.

# How to try this project yourself

This project have been tested on Ubuntu and MacOS.
Should work fine on similar distro.

### Clone the project on your own computer :
```
git clone https://github.com/LeSpatiocorne/philosophers.git
```
### in the root directory
```
make
```
### then run the executable with the following arguments :
- number of philo
- time to die : 
- time to eat
- time to sleep
- (optionnal) number of dinner before stopping the simulation
### common example :
```
./philo 5 800 200 200 5
```

# Tester included in this project
under the folder tester you'll find "tester.sh" that you can `chmod` and run to make multiple tests.
Two types of test are included "die_tests" and "alive_tests"
Some test are supposed to be infinite loop, so in order to not make them really infinite they run with a 30 seconds timeout.

Every time you run the tester, all the outputs goes under the results folder where you can check for the full execution log.

To make your own test, you can simply add the execution command in the corresponding file by adding a line, since the test will take a line in the file as an executable command.

# Valgrind.sh
This is a really usefull shortcut argument to test philosophers.
It's the way to know if your philosophers suposed to live are dying from an obvious deadlock.
