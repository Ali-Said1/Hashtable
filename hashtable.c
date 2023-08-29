#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct node
{
    char *name;  // String value stored in the node
    struct node *next;  // Pointer to the next node in the list
}
node;

const int initials = 36;  // Number of initial letters (A-Z and 0-9)
node *table[initials];  // Array of pointers to nodes for each initial letter

int hash(char *input);  // Function to calculate the hash value for a given input
void printhashtable(int status);  // Function to print the contents of the hash table
void freememory();  // Function to free the memory allocated for the hash table
bool isrepeated(char *input, node *ptr);  // Function to check if a name is repeated in a linked list

int main(int argc, char *argv[])
{
    if (argc == 1) // Checking if user inputed no arguments
    {
        printf(RED"Usage: ./hashtable [values]\n"RESET);
        return 1;
    }
    bool has_values;  // Flag to track if values were added to the hash table
    for (int i = 1; i < argc; i++)
    {
        if (!isdigit(argv[i][0]) && !isalpha(argv[i][0])) // Checking if any of the user input isn't valid
        {
            printf(RED"%s is an invalid name, skipping.\n"RESET, argv[i]);
        }
        else
        {
            node *n = malloc(sizeof(node)); // Create a new node
            if (n == NULL) // Checking if no memory left
            {
                if (has_values)
                {
                    printhashtable(1);
                    freememory();
                    return 3;
                }
                printf(YELLOW"There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n"RESET);
                return 3;
            }
            // Setting values for the pointer
            char *name = malloc(strlen(argv[i]) + 1);  // Allocate memory for the name string
            if (name == NULL)
            {
                free(n);
                if (has_values)
                {
                    printhashtable(1);
                    freememory();
                }
                printf(YELLOW"There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n"RESET);
                return 3;
            }
            strcpy(name, argv[i]);  // Copy the input name to the allocated memory
            // Assigning the values to the current node
            n->name = name;
            n->next = NULL;
            // Getting the hash value for the first letter of the name
            int index = hash(name);
            if (table[index] == NULL) // Checking if there is another node with name value of the same initial
            {
                table[index] = n;
                if (!has_values)
                {
                    has_values = true;
                }
            }
            else
            {
                if (!isrepeated(name, table[index])) // Checking if the input is repeated
                {
                    // Prepending
                    node *tmp = table[index];
                    table[index] = n;
                    n->next = tmp;
                }
                else
                {
                    printf(YELLOW"Repeated value %s wasn't added.\n"RESET, name);
                    free(name);
                    free(n);
                }
            }
        }
    }
    printhashtable(0);
    freememory();
}

int hash(char *input)
{
    unsigned int hashreturn;
    if (isdigit(input[0]))
    {
        hashreturn = input[0] - '0';
        return hashreturn;
    }
    hashreturn = toupper(input[0]) - 'A';
    return hashreturn;
}

void printhashtable(int status)
{
    printf("\n\n");
    // Checking function call status, to print specified message
    if (status == 1)
    {
        printf(YELLOW"Some input couldn't be stored, maintained values:\n"RESET);
    }
    else if (status == 0)
    {
        printf(GREEN"+------Successfully stored all user input------+\n"RESET);
    }
    int x = 1;
    printf("+------"CYAN"Hash table values"RESET"------+\n");
    for (int i = 0; i < initials; i++)
    {
        if (table[i] != NULL) // Checking if the pointer points to other node(s)
        {
            for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
            {
                printf("+------Value %i------+\n", x);
                printf("Current memory address: "YELLOW"%p\n"RESET, ptr);
                printf("Name value: "GREEN"%s\n"RESET, ptr->name);
                if (ptr->next != NULL) // Checking if there is another node linked to the current
                {
                    printf("Next name: %s\n", ptr->next->name);
                }
                else
                {
                    // Searching for the next available node
                    int j = i + 1;
                    while (j < initials)
                    {
                        if (table[j] != NULL)
                        {
                            break;
                        }
                        else
                        {
                            j++;
                        }
                    }
                    if (j < initials - 1 || (j == initials - 1 && table[j] != NULL))
                    {
                        printf("Next name: %s\n", table[j]->name);
                    }
                }
                x++;
            }
        }
    }
    printf("+-------"CYAN"Hash table end"RESET"-------+\n");
    if (status == 1)
    {
        printf(YELLOW"There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n"RESET);
    }
    printf("\n\n");
}

void freememory()
{
    for (int i = 0; i < initials; i++)
    {
        if (table[i] != NULL)
        {
            node *ptr = table[i];
            while (ptr != NULL)
            {
                node *tmp = ptr->next;
                free(ptr->name);
                free(ptr);
                ptr = tmp;
            }
        }
    }
}

bool isrepeated(char *input, node *ptr)
{
    for (node *tmp = ptr; ptr != NULL; ptr = ptr->next)
    {
        if (!strcasecmp(input, ptr->name))
        {
            return true;
        }
    }
    return false;
}
