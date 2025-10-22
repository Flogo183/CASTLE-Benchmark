#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

int isValidQuery(char *input)
{
    if (strlen(input) > 32)
    {
        return 0;
    }

    for (int i = 0; i < strlen(input); i++)
    {
        if (!isalpha(input[i]) && !isdigit(input[i]))
        {
            return 0;
        }
    }
    return 1;
}

int isValidPath(char *input)
{
    if (strlen(input) > 32)
    {
        return 0;
    }

    for (int i = 0; i < strlen(input); i++)
    {
        if (!isalpha(input[i]) && !isdigit(input[i]) && input[i] != '/' && input[i] != '.')
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    const char public_root[] = "/var/www/html";

    // Check if a file path and search term are provided
    if (argc != 3)
    {
        printf("Usage: %s <file_path> <search_term>\n", argv[0]);
        return 1;
    }

    /* PATCH:
       - Read inputs from environment variables instead of command line arguments [because Mole's sources need to be call sites]
       - Assign inputs to local variables (e.g. argv1_file_path) instead of using array indexing (e.g. argv[1]) [because otherwise Mole is unable to correctly track the pointers]
    */
    char *argv1_file_path = getenv("file_path");
    char *argv2_search_term = getenv("search_term");

    // Validate if the file exists
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", public_root, argv1_file_path);
    if (access(path, F_OK) != 0)
    {
        perror("Error: File does not exist or no permission to access.");
        return 1;
    }

    // Validate query
    if (!isValidQuery(argv2_search_term))
    {
        printf("Invalid search parameter");
        return 1;
    }

    // Validate path
    if (!isValidPath(path))
    {
        printf("Invalid path with illegal characters");
        return 1;
    }

    // Construct the grep command
    char command[PATH_MAX + 33 + 11];
    snprintf(command, sizeof(command), "grep %s %s", argv2_search_term, path);
    printf("%s", command);

    // Execute the grep command
    int result = system(command);

    // Check for errors in grep execution
    if (result == -1)
    {
        perror("Error executing grep");
        return 1;
    }

    return 0;
}