#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void expand_symbol(FILE *output, char symbol, int repeat) {
    for (int i = 0; i < repeat; i++) {
        fputc(symbol, output);
    }
}

int parse_number(const char *str, int *i) {
    int num = 0;
    while (isdigit(str[*i])) {
        num = num * 10 + (str[*i] - '0');
        (*i)++;
    }
    return num;
}

void compile_mbf_to_bf(const char *input_filename, const char *output_filename) {
    FILE *input = fopen(input_filename, "r");
    if (!input) {
        printf("Failed to open input file: %s\n", input_filename);
        return;
    }

    FILE *output = fopen(output_filename, "w");
    if (!output) {
        printf("Failed to open output file: %s\n", output_filename);
        fclose(input);
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        int len = strlen(buffer);
        for (int i = 0; i < len; i++) {
            if (buffer[i] == '{') {
                // Parse {symbol|n} format
                char symbol = buffer[++i];
                if (buffer[++i] == '|' && isdigit(buffer[++i])) {
                    int repeat = parse_number(buffer, &i);
                    if (buffer[i] == '}') {
                        expand_symbol(output, symbol, repeat);
                    }
                }
            } else if (strchr("+-<>[].,", buffer[i])) {
                fputc(buffer[i], output);
            }
        }
    }

    fclose(input);
    fclose(output);
    printf("Compilation complete! Output written to %s\n", output_filename);
}

void run_bf_interpreter(const char *bf_file) {
    printf("Running Brainf**k interpreter on %s...\n", bf_file);

    if (execlp("brainc", "brainc", "-i", bf_file, (char *)NULL) == -1) {
        perror("Error executing Brainf**k interpreter");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int keep_flag = 0;
    const char *input_mbf = NULL;

    // Argument parsing
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--keep") == 0) {
            keep_flag = 1;
        } else {
            input_mbf = argv[i];
        }
    }

    if (!input_mbf) {
        printf("Usage: %s <input.mbf> [-k|--keep]\n", argv[0]);
        return 1;
    }

    char output_bf[256];
    snprintf(output_bf, sizeof(output_bf), "%s.bf", input_mbf);

    compile_mbf_to_bf(input_mbf, output_bf);

    // Fork a child process to run the BF interpreter
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error during fork");
        return 1;
    }

    if (pid == 0) {
        // Run interpretator as child
        run_bf_interpreter(output_bf);
    } else {
        int status;
        waitpid(pid, &status, 0);

        // If -k or --keep is not specified, delete the .bf file
        if (!keep_flag) {
            if (remove(output_bf) == 0) {
                printf("Deleted output file: %s\n", output_bf);
            } else {
                perror("Error deleting .bf file");
            }
        }
    }

    return 0;
}
