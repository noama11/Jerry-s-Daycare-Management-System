# Jerry Management System Based on Core Data Structures

## Introduction

This project demonstrates the design and implementation of three **generic data structures**: a **Linked List**, a **Hash Table**, and a **Fire Table**. These structures are built for versatility, allowing them to manage a wide range of data types through customizable functions. The project also includes a **Key-Value Pair** object, used in both the Hash Table and Fire Table implementations. 

In the second part of the project, these data structures are applied to manage custom **Jerry objects**, highlighting their practical applications in efficiently handling data.

## Data Structures

### 1. Linked List
The **Linked List** provides a dynamic way to store and manipulate data. It supports:
- **Insertion**: Add new data.
- **Deletion**: Remove data.
- **Search by Position**: Retrieve data based on its position.
- **Search by Value**: Find data based on its content.

This structure is well-suited for scenarios that require flexible memory usage and sequential data management.

### 2. Hash Table
The **Hash Table** allows **O(1) average time complexity** for lookups using a key-value mechanism. It is designed with:
- **Constant-Time Lookup**: Quickly find values based on keys.
- **Collision Handling**: Uses linked lists to resolve key collisions within hash buckets.
- **Single Value per Key**: Each key maps to a single value for efficient storage.

### 3. MultiValueHashTable
The **Fire Table** extends the functionality of the Hash Table, enabling the mapping of **multiple values** to a single key:
- **Multi-Value Mapping**: Each key is associated with a list of values.
- **Efficient Value Storage**: Supports scenarios where a key needs to reference several related data points.

### Generic Design
All structures are **generic**, meaning they can handle any data type through custom **copy**, **compare**, **destroy**, and **create** functions. This flexibility makes them reusable for a wide range of applications.

## Jerry Object Management

In the second part of the project, the data structures are utilized to manage **Jerry objects**, a type of custom object representing unique entities. Using the previously created data structures, the system supports:
- **Adding a New Jerry**: Insert a new Jerry into the system.
- **Deleting a Jerry**: Remove an existing Jerry.
- **Adding Attributes**: Attach additional properties to a Jerry object.
- **Displaying Jerry Information**: Print detailed data about a Jerry.

These operations demonstrate how generic data structures can be applied in real-world use cases, making the system both powerful and flexible.

## Key Features
- **Efficiency**: O(1) average lookup time in the Hash Table ensures fast data retrieval.
- **Flexibility**: Fully generic structures allow for easy adaptation to any data type.
- **Scalability**: Supports complex data relationships, such as multiple values mapped to a single key in the Fire Table.
- **Reusability**: The modular design makes these structures easy to integrate into other projects.

## Makefile

The provided **Makefile** automates the compilation process, ensuring efficient builds and clean workspace management:

- **Target `JerryBoree`**: Compiles all necessary object files (`*.o`) and links them to produce the final executable.
- **Modular Compilation**: Each `.o` file is generated from its respective source files, ensuring that changes in one file do not require recompiling everything.
- **Clean Command**: The `clean` command removes all object files, ensuring a tidy working environment.

### Example:
```makefile
JerryBoree: Jerry.o KeyValuePair.o LinkedList.o HashTable.o MultiValueHashTable.o JerryBoreeMain.o
    gcc *.c -o JerryBoree
clean:
    rm -f *.o
```

