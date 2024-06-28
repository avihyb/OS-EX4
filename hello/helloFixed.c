#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    char *string, *string_so_far = NULL; // Initialize to NULL

    int i, length; length = 0;

    for(i = 0; i < argc; i++) {
        length += strlen(argv[i]) + 1;
        string = malloc(length + 1);

        /* Copy the string built so far. */
        if(string_so_far != NULL)
            strcpy(string, string_so_far);
        else
            *string = '\0';
        
        strcat(string, argv[i]);

        if(i < argc - 1)
            strcat(string, " ");
        
        free(string_so_far);  // Free the old memory
        string_so_far = string;
    }

    printf("You entered: %s\n", string_so_far);

    free(string_so_far);  // Free the last allocation

    return 0;
}
