#include <stdlib.h>
#include <stdio.h>

#define KSH_RL_BUFSIZE 1024
char *ksh_read_line(void)
{
    int bufsize = KSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * KSH_RL_BUFSIZE);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "lsh: error allocation\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += KSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            if (!buffer)
            {
                fprintf(stderr, "lsh: error allocation\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void ksh_loop(void)
{
}

int main(int argc, char **argv)
{
    ksh_loop();

    EXIT_SUCCESS;
}
