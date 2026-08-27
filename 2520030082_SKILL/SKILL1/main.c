#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUFFER_SIZE 1024
#define HISTORY_SIZE 20

char history[HISTORY_SIZE][BUFFER_SIZE];
int history_count = 0;

/* Enable terminal raw mode */
void enable_raw_mode(struct termios *original)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/* Restore normal terminal mode */
void disable_raw_mode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

/* Add command to history */
void add_to_history(const char *command)
{
    if (strlen(command) == 0)
        return;

    if (history_count < HISTORY_SIZE)
    {
        strcpy(history[history_count], command);
        history_count++;
    }
    else
    {
        for (int i = 1; i < HISTORY_SIZE; i++)
        {
            strcpy(history[i - 1], history[i]);
        }

        strcpy(history[HISTORY_SIZE - 1], command);
    }
}

/* Clear current input from terminal */
void clear_input(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("\b \b");
    }

    fflush(stdout);
}

/* Read keyboard input */
int read_input(char *buffer)
{
    struct termios original;
    int position = 0;
    int history_index = history_count;

    enable_raw_mode(&original);

    while (1)
    {
        char c;

        if (read(STDIN_FILENO, &c, 1) <= 0)
        {
            disable_raw_mode(&original);
            return 0;
        }

        /* Ctrl + D */
        if (c == 4)
        {
            disable_raw_mode(&original);

            if (position == 0)
            {
                printf("\n");
                return 0;
            }

            continue;
        }

        /* Enter key */
        if (c == '\n' || c == '\r')
        {
            buffer[position] = '\0';
            printf("\n");

            disable_raw_mode(&original);
            return 1;
        }

        /* Backspace */
        if (c == 127 || c == 8)
        {
            if (position > 0)
            {
                position--;
                buffer[position] = '\0';

                printf("\b \b");
                fflush(stdout);
            }

            continue;
        }

        /* Arrow keys */
        if (c == 27)
        {
            char sequence[2];

            if (read(STDIN_FILENO, &sequence[0], 1) <= 0)
                continue;

            if (sequence[0] != '[')
                continue;

            if (read(STDIN_FILENO, &sequence[1], 1) <= 0)
                continue;

            /* Up arrow */
            if (sequence[1] == 'A')
            {
                if (history_index > 0)
                {
                    history_index--;

                    clear_input(position);

                    strcpy(buffer, history[history_index]);
                    position = strlen(buffer);

                    printf("%s", buffer);
                    fflush(stdout);
                }
            }

            /* Down arrow */
            else if (sequence[1] == 'B')
            {
                if (history_index < history_count - 1)
                {
                    history_index++;

                    clear_input(position);

                    strcpy(buffer, history[history_index]);
                    position = strlen(buffer);

                    printf("%s", buffer);
                    fflush(stdout);
                }
                else
                {
                    history_index = history_count;

                    clear_input(position);

                    position = 0;
                    buffer[0] = '\0';

                    fflush(stdout);
                }
            }

            continue;
        }

        /* Normal printable character */
        if (c >= 32 && c <= 126)
        {
            if (position < BUFFER_SIZE - 1)
            {
                buffer[position++] = c;
                buffer[position] = '\0';

                putchar(c);
                fflush(stdout);
            }
        }
    }
}

/* Main interactive loop */
int main()
{
    char input[BUFFER_SIZE];

    printf("=====================================\n");
    printf("       Skill 1 Interactive Shell\n");
    printf("=====================================\n");
    printf("Type commands or 'exit' to quit.\n");
    printf("Use Up/Down arrows for command history.\n\n");

    while (1)
    {
        printf("skill1> ");
        fflush(stdout);

        if (!read_input(input))
        {
            break;
        }

        /* Exit conditions */
        if (strcmp(input, "exit") == 0 ||
            strcmp(input, "quit") == 0)
        {
            printf("Exiting Skill 1...\n");
            break;
        }

        /* Empty input */
        if (strlen(input) == 0)
        {
            continue;
        }

        /* Store command in history */
        add_to_history(input);

        /* Display received command */
        printf("Command received: %s\n", input);
    }

    return 0;
}
