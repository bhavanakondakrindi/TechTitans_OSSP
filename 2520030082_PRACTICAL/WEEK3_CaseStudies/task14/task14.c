#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_HISTORY 100
#define MAX_COMMAND 100

char history[MAX_HISTORY][MAX_COMMAND];
int history_count = 0;

struct termios original_terminal;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal);
}

void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &original_terminal);

    atexit(disableRawMode);

    struct termios raw = original_terminal;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void addHistory(char *command)
{
    if (strlen(command) == 0)
        return;

    if (history_count < MAX_HISTORY)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
}

void showHistory()
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d  %s\n", i + 1, history[i]);
    }
}

void clearLine(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("\b \b");
    }

    fflush(stdout);
}

int main()
{
    char input[MAX_COMMAND];
    int length;
    int history_position;

    enableRawMode();

    while (1)
    {
        printf("\nmyshell> ");
        fflush(stdout);

        memset(input, 0, sizeof(input));
        length = 0;
        history_position = history_count;

        while (1)
        {
            char c;

            if (read(STDIN_FILENO, &c, 1) != 1)
                continue;

            if (c == '\n' || c == '\r')
            {
                input[length] = '\0';
                printf("\n");
                break;
            }

            if (c == 127)
            {
                if (length > 0)
                {
                    length--;
                    input[length] = '\0';

                    printf("\b \b");
                    fflush(stdout);
                }

                continue;
            }

            if (c == 27)
            {
                char seq[2];

                if (read(STDIN_FILENO, &seq[0], 1) != 1)
                    continue;

                if (read(STDIN_FILENO, &seq[1], 1) != 1)
                    continue;

                if (seq[0] == '[' && seq[1] == 'A')
                {
                    if (history_count > 0 && history_position > 0)
                    {
                        clearLine(length);

                        history_position--;

                        strcpy(input, history[history_position]);
                        length = strlen(input);

                        printf("%s", input);
                        fflush(stdout);
                    }
                }
                else if (seq[0] == '[' && seq[1] == 'B')
                {
                    clearLine(length);

                    if (history_position < history_count - 1)
                    {
                        history_position++;

                        strcpy(input, history[history_position]);
                        length = strlen(input);

                        printf("%s", input);
                    }
                    else
                    {
                        history_position = history_count;
                        input[0] = '\0';
                        length = 0;
                    }

                    fflush(stdout);
                }

                continue;
            }

            if (length < MAX_COMMAND - 1)
            {
                input[length++] = c;
                input[length] = '\0';

                putchar(c);
                fflush(stdout);
            }
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        if (strcmp(input, "history") == 0)
        {
            showHistory();
            continue;
        }

        addHistory(input);
    }

    return 0;
}
