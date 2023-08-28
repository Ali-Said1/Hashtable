#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct node
{
    char *name;
    struct node *next;
}
node;

const int initials = 36;
node *table[initials];

int hash(char *input);
void printhashtable(int status);
void freememory();
bool isrepeated(char *input, node *ptr);

int main(int argc, char *argv[])
{
    if (argc == 1) // Checking if user inputed no arguments
    {
        printf("Usage: ./hashtable [values]\n");
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        if (!isdigit(argv[i][0]) && !isalpha(argv[i][0])) // Checking if any of the user input isn't valid
        {
            printf("Please enter a valid name.\n");
            return 2;
        }
    }
    bool has_values;
    for (int i = 1; i < argc; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL) // Checking if no memory left
        {
            if (has_values)
            {
                printhashtable(1);
                printf("There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n");
                freememory();
                return 3;
            }
            printf("There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n");
            return 3;
        }
        // Setting values for the pointer
        char *name = malloc(strlen(argv[i]) + 1);
        if (name == NULL)
        {
            free(n);
            if (has_values)
            {
                printhashtable(1);
                printf("There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n");
                freememory();
            }
            printf("There isn't enough memory available right now. Please try closing some programs you don't need and try again later.\n");
            return 3;
        }
        strcpy(name, argv[i]);
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
                printf("Repeated value %s wasn't added.\n", name);
                free(name);
                free(n);
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
    // Checking function call status, to print specified message
    if (status == 1)
    {
        printf("Some input couldn't be stored, maintained values:\n");
    }
    else if (status == 0)
    {
        printf("+------Successfully stored all user input------+\n");
    }
    int x = 1;
    printf("+------Hash table values------+\n");
    for (int i = 0; i < initials; i++)
    {
        if (table[i] != NULL) // Checking if the pointer points to other node(s)
        {
            for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
            {
                printf("+------Value %i------+\n", x);
                printf("Current memory address: %p\n", ptr);
                printf("Name value: %s\n", ptr->name);
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
    printf("+-------Hash table end-------+\n");
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