/* main.c - calculator compiler that translates math into assembly */
// made on halloween or saturween, which is rare i guess, my first saturween as a kid and last time

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int operater = 0;

    if (argc == 0) {
	printf("usage: %s <file.txt>\n", argv[0]);
	return 1;
    }

    if (argc == 2) {
        // open file
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
	    perror("fatal");
	    return 1;
        }

	mode_t old_mask = umask(0);

	// create file
	int create = open("math.asm", O_WRONLY | O_CREAT | O_CREAT | O_TRUNC, 0666);
	umask(old_mask);

	if (create == -1) {
	    perror("error creating file");
	    return 1;
	}

	write(create, "section .text\n", 14);
	write(create, "\tglobal _start\n", strlen("\tglobal _start\n"));
	write(create, "_start:\n", strlen("_start:\n"));

	int lines; // hold each charatcer temporary
	while ((lines = fgetc(file)) != EOF) {
	    // translate math into assembly

	    // skip whitespace
	    if (isspace(lines)) {
	        continue;
	    }

	    // check for text
	    if (isalpha(lines)) {
		fprintf(stderr, "%s: detected text... exiting\n", argv[0]);
		return 1;
	    }

	    // check for numbers
	    if (isdigit(lines)) {
		int num = 0;
		while (lines != EOF && isdigit(lines)) {
		    num = (num * 10) + (lines - '0');
		    lines = fgetc(file);
		}

		char buffer[64];
		int first = snprintf(buffer, sizeof(buffer), "\tmov rax, %d\n\tpush rax\n", num);
		write(create, buffer, first);

		/* 1 == Addition
		   2 == Subtraction
		   3 == Multiplication
		   4 == Division
		*/

		if (operater == 1) {
		    const char *add = "\tpop rbx\n\tpop rax\n\tadd rax, rbx\n\tpush rax\n";
		    write(create, add, strlen(add));
		} else if (operater == 2) {
		    const char *sub = "\tpop rbx\n\tpop rax\n\tsub rax, rbx\n\tpush rax\n";
		    write(create, sub, strlen(sub));
		} else if (operater == 3) {
		    const char *times = "\tpop rbx\n\tpop rax\n\timul rax, rbx\n\tpush rax\n";
		    write(create, times, strlen(times));
		} else if (operater == 4) {
		    const char *divide = "\tpop rbx\n\tpop rax\n\tcqo\n\tidiv rax\n\tpush rax\n";
		    write(create, divide, strlen(divide));
		}
		operater = 0;
	    }

	    else if (lines == '+') { operater = 1; }
	    else if (lines == '-') { operater = 2; }
	    else if (lines == '*') { operater = 3; }
	    else if (lines == '/') { operater = 4; }

	}

	// exit line
	const char *exit = "\tmov rax, 60\n\tmov rdi, 0\n\tsyscall\n";
	write(create, exit, strlen(exit));

	close(create);
	fclose(file);
	return 0;
    } else {
	printf("usage: %s <file.txt>\n", argv[0]);
        return 1;
    }
}
