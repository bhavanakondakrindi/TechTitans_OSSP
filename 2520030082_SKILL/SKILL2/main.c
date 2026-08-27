#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 5

/* Linked list node */
typedef struct Node
{
    char *data;
    struct Node *next;
} Node;

/* Dynamically add a string to an array */
void add_to_array(char ***array, int *size, int *count, const char *value)
{
    /* Resize when array becomes full */
    if (*count >= *size)
    {
        int new_size = (*size) * 2;

        char **temp = realloc(*array, new_size * sizeof(char *));

        if (temp == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        *array = temp;
        *size = new_size;

        printf("Array resized to %d elements.\n", new_size);
    }

    /* Allocate memory for the new string */
    (*array)[*count] = malloc(strlen(value) + 1);

    if ((*array)[*count] == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy((*array)[*count], value);

    (*count)++;
}

/* Display dynamic array */
void display_array(char **array, int count)
{
    printf("\nDynamic Array:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, array[i]);
    }
}

/* Create linked list node */
Node *create_node(const char *value)
{
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = malloc(strlen(value) + 1);

    if (new_node->data == NULL)
    {
        free(new_node);
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new_node->data, value);
    new_node->next = NULL;

    return new_node;
}

/* Add node to linked list */
void add_to_list(Node **head, const char *value)
{
    Node *new_node = create_node(value);

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    Node *current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;
}

/* Display linked list */
void display_list(Node *head)
{
    printf("\nLinked List:\n");

    Node *current = head;
    int position = 1;

    while (current != NULL)
    {
        printf("%d. %s\n", position, current->data);

        current = current->next;
        position++;
    }
}

/* Free linked list memory */
void free_list(Node *head)
{
    Node *current = head;

    while (current != NULL)
    {
        Node *next = current->next;

        free(current->data);
        free(current);

        current = next;
    }
}

/* Free dynamic array memory */
void free_array(char **array, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(array[i]);
    }

    free(array);
}

int main()
{
    int size = INITIAL_SIZE;
    int count = 0;

    /* Dynamically allocate array */
    char **array = malloc(size * sizeof(char *));

    if (array == NULL)
    {
        printf("Initial memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    Node *head = NULL;

    printf("=====================================\n");
    printf("       Skill 2 Memory Manager\n");
    printf("=====================================\n");

    printf("\nAdding values to dynamic array...\n");

    add_to_array(&array, &size, &count, "Linux");
    add_to_array(&array, &size, &count, "Operating Systems");
    add_to_array(&array, &size, &count, "C Programming");
    add_to_array(&array, &size, &count, "Dynamic Memory");
    add_to_array(&array, &size, &count, "Valgrind");
    add_to_array(&array, &size, &count, "Linked Lists");
    add_to_array(&array, &size, &count, "Memory Management");

    display_array(array, count);

    printf("\nAdding values to linked list...\n");

    add_to_list(&head, "Node 1");
    add_to_list(&head, "Node 2");
    add_to_list(&head, "Node 3");
    add_to_list(&head, "Node 4");

    display_list(head);

    printf("\nMemory cleanup started...\n");

    free_array(array, count);
    free_list(head);

    printf("All dynamically allocated memory has been released.\n");

    return 0;
}
