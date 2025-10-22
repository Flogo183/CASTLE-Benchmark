#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_MAX 256

int main(int argc, char **argv)
{
    char cmd[CMD_MAX] = "/usr/bin/cat ";

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

    strncat(cmd, argv[1], CMD_MAX - 14);
    system(cmd);
    return 0;
}
