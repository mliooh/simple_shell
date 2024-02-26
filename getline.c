#include "main.h"

char *my_getline()
{
    static char buffer[BUFFER_SIZE];
    static char *current_position = buffer;
    static ssize_t remaining_bytes = 0;
    
    if (remaining_bytes <= 0)
    {
        /* error occurred or end of data */
        return (NULL);
    }

    line = malloc(BUFFER_SIZE);

    if (line == NULL)
    {
        perror("malloc");
        return (NULL);
    }

    for (i = 0; i < remaining_bytes; i++)
    {
        line[i] = *current_position;

        if (*current_position == '\n')
        {
            /* null terminate */
            line[i + 1] = '\0';

            /* update current position and remaining bytes*/

            current_position += i + 1;
            remaining_bytes -= i + 1;

            return (line);
        }
        current_position++;
    }

    more_data = my_getline();

    if (more_data == NULL)
    {

        /* error or end of data */

        free(line);
        return NULL;
    }

    /* concatenated data doesn't exceed buffer size*/


    total_length = strlen(line) + strlen(more_data) + 1;
    if (total_length < BUFFER_SIZE)
    {
        /*Reallocate memory for the line*/

        char *temp = realloc(line, total_length);
        if (temp == NULL)
        {
            perror("realloc");
            free(line);
            free(more_data);
            return NULL;
        }
        line = temp;
        strcat(line, more_data);

        free(more_data);
    }
    else
    {
        /* buffer overflow*/

        free(line);
        free(more_data);
        return NULL;
    }
    
    return (NULL);
}
