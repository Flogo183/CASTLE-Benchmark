#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 1)
    {

        /* PATCH:
           - Read input from environment variable instead of command line argument [because Mole's sources need to be call sites]
           - Assign input directly into argv[1] so analyzer sees getenv call site without extra local copies
           - Add a minimal NULL check to avoid passing NULL to snprintf
        */
        argv[1] = getenv("user_input");
        if (!argv[1])
        {
            fprintf(stderr, "missing environment variable: user_input\n");
            return 1;
        }

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), "%s", argv[1]);
        printf("%s", buffer);
    }
    return 0;
}
