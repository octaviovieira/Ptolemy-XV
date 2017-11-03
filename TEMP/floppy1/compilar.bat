gcc -c serpent-aux.c -o serpent-aux.o
gcc -c serpent-reference.c -o serpent-reference.o
gcc -c serpent-test.c -o serpent-test.o
gcc serpent-aux.o serpent-reference.o serpent-test.o -o serpent
pause