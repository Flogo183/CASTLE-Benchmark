#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSIZE 64

int check(const char *str)
{
    int i;

    for (i = 0; i < strlen(str); ++i)
        if (!isalnum(str[i]))
            return -1;

    return 0;
}

void test(char *str)
{
    char buf[MAXSIZE];

    if (check(str) < 0)
        return;

    snprintf(buf, sizeof buf, "/bin/echo %s", str);
    if (system(buf) < 0)
        fprintf(stderr, "Error running command: %s\n", buf);
}

int main(int argc, char **argv)
{
    char *userstr;

    if (argc > 1)
    {
        /* PATCH:
           - Read inputs from environment variables instead of command line arguments [because Mole's sources need to be call sites]
           - Assign input directly into argv[1] so analyzer sees getenv call site without extra local copies
           - Add a minimal NULL check to avoid passing a NULL pointer into strlen/check
        */
        argv[1] = getenv("userstr");
        if (!argv[1])
        {
            fprintf(stderr, "missing environment variable: userstr\n");
            return 1;
        }

        userstr = argv[1];
        test(userstr);
    }
    return 0;
}
