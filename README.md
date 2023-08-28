# Hashtable

This program implements a simple hashtable using a linked list to handle collisions. The hashtable stores user inputted values and organizes them based on the first letter of each value.

## Compilation

To compile and run the program, use the following command:

```
clang -o hashtable hashtable.c
./hashtable [values]
```

Note: Replace `[values]` with the values you want to store in the hashtable.

## Usage

The program requires user input of values as command line arguments. The values can be alphanumeric strings.

### Example

```
./hashtable John Apple Banana Alice 123
```

## Functions

### int hash(char *input)

This function calculates the hash value for a given input. It returns an integer used to determine the index in the hashtable.

### void printhashtable(int status)

This function prints the values stored in the hashtable. It displays the memory address, name value, and next name (if applicable) for each node in the hashtable. The `status` parameter specifies the status of the function call and determines the message displayed before printing the values.

### void freememory()

This function frees the memory allocated for all the nodes in the hashtable.

### bool isrepeated(char *input, node *ptr)

This function checks if a given input is repeated in a linked list. It returns `true` if the input is repeated and `false` otherwise.