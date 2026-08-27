# Skill 1 - Interactive Command Loop

## Objective

To create an interactive command loop that displays a prompt, reads user input, handles exit conditions, and manages keyboard input.

## Features

- Displays an interactive prompt.
- Reads user input.
- Supports Enter key processing.
- Supports Backspace.
- Supports multi-character commands.
- Maintains an input buffer.
- Supports Up Arrow for previous commands.
- Supports Down Arrow for next commands.
- Maintains command history.
- Supports exit and quit commands.
- Supports Ctrl+D for exiting the program.

## Compilation

gcc main.c -o skill1

## Execution

./skill1

## Example

skill1> hello
Command received: hello

skill1> test123
Command received: test123

skill1> exit
Exiting Skill 1...

## Control Flow

Start
  |
  v
Display Prompt
  |
  v
Read Keyboard Input
  |
  v
Process Input
  |
  +----> Backspace ------> Update Buffer
  |
  +----> Arrow Keys -----> Navigate History
  |
  +----> Enter ----------> Process Command
  |
  v
Check Exit Condition
  |
  +---- Yes ---> Exit
  |
  +---- No ----> Display Prompt Again
  |
  v
Repeat

## Testing

The program was tested for:

1. Interactive prompt display.
2. Single-character input.
3. Multi-character commands.
4. Backspace handling.
5. Enter key processing.
6. Previous command history.
7. Next command history.
8. Exit using the exit command.
9. Exit using Ctrl+D.
