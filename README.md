# Jerry Management System

## Table of Contents

1. [Introduction](#introduction)
2. [Data Structures](#data-structures)
   - [Linked List](#1-linked-list)
   - [Hash Table](#2-hash-table)
   - [MultiValue Hash Table](#3-multivalue-hash-table)
3. [Jerry Object Management](#jerry-object-management)
4. [Key Features](#key-features)
5. [Instructions](#instructions)
   - [Prerequisites](#1-prerequisites)
   - [Compilation](#2-compilation)
   - [Running the Program](#3-running-the-program)
   - [Cleaning Up](#4-cleaning-up)
6. [Makefile Explanation](#makefile)
7. [Example Usage](#example-usage)
8. [Notes](#notes)

---

## #Introduction

This project demonstrates the design and implementation of three **generic data structures**: a **Linked List**, a **Hash Table**, and a **MultiValue Hash Table**. These structures are designed to manage various data types through customizable functions, offering flexibility for many applications.

In the second part, these data structures are applied to manage custom **Jerry objects**, demonstrating practical applications in handling data efficiently.

---

## Data Structures

### 1. Linked List

A **Linked List** is a dynamic data structure that supports:
- **Insertion**: Add new data.
- **Deletion**: Remove data.
- **Search by Position**: Retrieve data at a specific position.
- **Search by Value**: Find data based on its value.

This structure is ideal for flexible memory usage and sequential data management.

### 2. Hash Table

A **Hash Table** enables fast lookups using a key-value pair mechanism:
- **Constant-Time Lookup**: Fast retrieval of values by their keys.
- **Collision Handling**: Manages key collisions through linked lists in hash buckets.
- **Single Value per Key**: Each key maps to a single value, optimizing storage.

### 3. MultiValue Hash Table

The **MultiValue Hash Table** extends the Hash Table by allowing:
- **Multi-Value Mapping**: Each key can map to multiple values.
- **Efficient Value Storage**: Useful when a key needs to reference multiple related data points.

### Generic Design

These structures are **generic**, allowing them to handle any data type through custom functions for **copying**, **comparing**, **destroying**, and **creating** data. This makes them flexible and reusable across different use cases.

---

## Jerry Object Management

In the second part, the data structures are used to manage **Jerry objects**. The system provides options for:
- **Adding a New Jerry**: Insert a new Jerry into the system.
- **Deleting a Jerry**: Remove a Jerry from the system.
- **Adding Attributes**: Attach custom properties to a Jerry.
- **Displaying Jerry Information**: Print detailed information about a Jerry.

This demonstrates how generic data structures can be adapted to solve real-world problems.

---

## Key Features

- **Efficiency**: O(1) average lookup time with the Hash Table ensures quick data retrieval.
- **Flexibility**: The generic design allows for easy adaptation to various data types.
- **Scalability**: Supports complex relationships, like mapping multiple values to a single key.
- **Reusability**: The modular design makes it easy to integrate these structures into other projects.

---

## Instructions

### 1. Prerequisites

Before running the project, make sure you have `gcc` installed. You can install it using:

```bash
sudo apt-get install gcc
```

### 2. Compilation

To compile the project, navigate to the project directory and use the `Makefile` provided:

1. **Navigate to the project directory**:
   ```bash
   cd /path/to/project/directory
   ```

2. **Compile the program**:
   ```bash
   make
   ```

This will compile all `.c` files and create an executable called `JerryBoree`.

### 3. Running the Program

Run the `JerryBoree` executable with the required parameters:

```bash
./JerryBoree [number_of_planets] [configuration_file_path]
```

- **[number_of_planets]**: An integer representing the number of planets used to set up the planet list.
- **[configuration_file_path]**: A string representing the path to a file containing the planet and Jerry data.

For example:

```bash
./JerryBoree 4 configuration_file.txt
```

This will start the Jerry management system using 4 planets, reading data from `configuration_file.txt`.

### 4. Cleaning Up

After you run the program, you can clean up the compiled files with:

```bash
make clean
```

This removes all object files (`*.o`) and the executable.

---

## Makefile

The **Makefile** automates the build process. It includes the following key rules:

- **Compiling**: The `make` command compiles all source files into object files.
- **Linking**: It links the object files to create the `JerryBoree` executable.
- **Cleaning**: The `make clean` command removes the object files and the executable.

---

## Example Usage

1. **Compile the project**:
   ```bash
   make
   ```

2. **Run the program**:
   ```bash
   ./JerryBoree 4 configuration_file.txt
   ```

3. **Clean up the directory**:
   ```bash
   make clean
   ```

---

## Notes

- Ensure the input file `configuration_file.txt` is in the same directory as the executable.
- You can modify the input file to adjust the program’s behavior.

---
