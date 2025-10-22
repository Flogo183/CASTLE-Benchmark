#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isValidText(char *input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isalpha(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <text>\n", argv[0]);
        return 1;
    }

    /* PATCH:
       - Read input from environment variable instead of command line argument [because Mole's sources need to be call sites]
       - Assign input directly into argv[1] so analyzer sees getenv call site without extra local copies
       - Add a minimal NULL check to avoid passing NULL to validation and printf
    */
    argv[1] = getenv("text");
    if (!argv[1])
    {
        fprintf(stderr, "missing environment variable: text\n");
        return 1;
    }

    if (!isValidText(argv[1]))
    {
        printf("Invalid parameter!");
        return 1;
    }

    printf(argv[1]);
    return 0;
}
