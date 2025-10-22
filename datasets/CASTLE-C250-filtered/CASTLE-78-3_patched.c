#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char cat[] = "cat ";
    char *command;
    unsigned long long commandLength;

    if (argc != 2)
    {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    /* PATCH:
       - Read inputs from environment variables instead of command line arguments [because Mole's sources need to be call sites]
       - Assign input directly into argv[1] so analyzer sees getenv call site without extra local copies
       - Add a minimal NULL check to avoid dereferencing a NULL getenv result
    */
    argv[1] = getenv("file_path");
    if (!argv[1])
    {
        fprintf(stderr, "missing environment variable: file_path\n");
        return 1;
    }

    commandLength = strlen(cat) + strlen(argv[1]) + 1;
    command = (char *)malloc(commandLength);
    if (command == NULL)
    {
        return 1;
    }

    strncpy(command, cat, commandLength);
    strncat(command, argv[1], (commandLength - strlen(cat)));

    system(command);
    free(command);
    return 0;
}
