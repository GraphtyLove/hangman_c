# Hangman C

Simple hangman game written in C.

The goal was just to explore the language.

## Run the game

You need GCC to be installed.

```bash
gcc main.c -o main;
./main;
```

or with Make:
```bash
make;
./game;
```

## Constraints

I used a few additionnal flags while compiling to ensure code quality:

```sh
gcc main.c -Wall -Werror -Wextra -g -o main && ./main
```
