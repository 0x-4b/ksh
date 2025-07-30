#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ksh_cd(char **argv);
int ksh_exit(char **argv);
int ksh_help(char **argv);
int ksh_clear(char **argv);

char *builtin_str[] = {
    "cd",
    "exit",
    "help",
    "clear"};

int (*builtin_func[])(char **argv) = {
    &ksh_cd,
    &ksh_exit,
    &ksh_help,
    &ksh_clear};

int ksh_builtin_num()
{
    return sizeof(builtin_func) / sizeof(char *);
}

int ksh_cd(char **argv)
{
    if (argv[1] == NULL)
    {
        fprintf(stderr, "ksh: cd requires path\n");
    }
    else
    {
        if (chdir(argv[1]) != 0)
        {
            perror("ksh");
        }
    }
    return 1;
}

int ksh_exit(char **argv)
{
    return 0;
}

int ksh_help(char **argv)
{
    printf("Hello, this is KSH\n");
    printf("To execute a command: <command> <arguments>\n");
    printf("These are some builin commands: \n");

    for (int i = 0; i < ksh_builtin_num(); ++i)
    {
        printf("%s\n", builtin_str[i]);
    }

    return 1;
}

int ksh_clear(char **argv)
{
    printf("\033[2J\033[H");
    return 1;
}

int ksh_launch(char **argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            perror("ksh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("ksh");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int ksh_exec(char **argv)
{
    if (argv[0] == NULL)
    {
        return 1;
    }

    for (int i = 0; i < ksh_builtin_num(); ++i)
    {
        if (strcmp(argv[0], builtin_str[i]) == 0)
        {
            return (builtin_func[i](argv));
        }
    }

    return ksh_launch(argv);
}

#define KSH_RL_BUFSIZE 1024
char *ksh_read_line(void)
{
    int bufsize = KSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * KSH_RL_BUFSIZE);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "ksh: error allocation\n");
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
                fprintf(stderr, "ksh: error allocation\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define KSK_SL_BUFSIZE 64
#define KSH_SL_DELIM " \t\r\n\a"
char **ksh_split_line(char *line)
{
    int bufsize = KSK_SL_BUFSIZE, position = 0;
    char **tokens = malloc(KSK_SL_BUFSIZE * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "ksh: error allocation\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, KSH_SL_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += KSH_RL_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "ksh: error allocation\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, KSH_SL_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void ksh_loop(void)
{
    char *line;
    char *last_command = NULL;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = ksh_read_line();

        if (strcmp(line, "!!") == 0)
        {
            if (last_command == NULL)
            {
                fprintf(stderr, "ksh: no previous command\n");
                free(line);
                continue;
            }
            else
            {
                free(line);
                line = strdup(last_command);
            }
        }
    
            free(last_command);
            last_command = strdup(line);

            args = ksh_split_line(line);
            status = ksh_exec(args);

            free(line);
            free(args);
        
    } while (status);
}

int main(int argc, char **argv)
{
    ksh_loop();

    return EXIT_SUCCESS;
}
