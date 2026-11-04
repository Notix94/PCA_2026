
prog : main.c list.c testListHelpers.c list.h testListHelpers.h
	gcc -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g main.c list.c testListHelpers.c -o prog