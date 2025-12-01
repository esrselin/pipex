# **pipex – Recreating Shell Pipe Behavior (42 Project)**

The **pipex** project is about recreating the behavior of a shell pipeline such as:

```
< infile cmd1 | cmd2 > outfile
```

You will implement a program that:

* Opens and reads from a file
* Executes commands with arguments
* Pipes the output of one command into another
* Redirects final output into a file
* Handles errors cleanly
* Reproduces shell behavior as closely as possible

This project teaches:

* Process creation (`fork`)
* Executing commands (`execve`)
* File descriptor manipulation (`dup2`)
* Using `pipe`
* Working with environment variables
* Error handling & memory management

---

## 📌 **Table of Contents**

1. [Introduction](#introduction)
2. [How Pipex Works](#how-pipex-works)
3. [Mandatory Requirements](#mandatory-requirements)
4. [Bonus Requirements](#bonus-requirements)
5. [Project Structure](#project-structure)
6. [Compilation](#compilation)
7. [Usage](#usage)
8. [Examples](#examples)
9. [Error Handling](#error-handling)
10. [Detailed Explanation](#detailed-explanation)

---

## 🧩 **Introduction**

**pipex** recreates the behavior of the shell pipeline:

```
cmd1 < infile | cmd2 > outfile
```

The program must:

* Read from an **infile**
* Redirect standard input & output using `dup2`
* Execute two commands using `execve`
* Use a pipe to connect outputs
* Write the final output into an **outfile**

Your task is to emulate a small part of the shell.

---

## 🔧 **How Pipex Works**

For the command below:

```
./pipex infile "ls -l" "wc -l" outfile
```

pipex performs:

1. Open `infile`
2. Execute `ls -l`

   * Redirect `infile` → cmd1 → pipe
3. Execute `wc -l`

   * Read from pipe → cmd2 → redirect to outfile
4. Close all file descriptors and wait for children

Diagram:

```
   infile ----> cmd1 ----> pipe ----> cmd2 ----> outfile
```

---

## 📜 **Mandatory Requirements**

### Program Format

```
./pipex infile cmd1 cmd2 outfile
```

You must:

* Open `infile` for reading
* Open `outfile` for writing (create if not exists, truncate)
* Create a pipe
* Fork twice
* Replace processes using `execve`
* Search commands via PATH
* Handle absolute and relative paths
* Handle errors gracefully

---

## 📁 **Project Structure**

Example structure:

```
pipex/
│
├── src/
│   ├── pipex.c
│   ├── p_utils.c
│   ├── main.c
│   └── pre_pipex.c
│
├── includes/
│   └── pipex.h
│
├── Makefile
└── README.md
```

---

## 🛠️ **Compilation**

### Compile mandatory part:

```bash
make
```

### Compile bonus part:

```bash
make bonus
```

### Cleaning:

```bash
make clean
make fclean
make re
```

---

## 🚀 **Usage**

### Mandatory:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

## 📘 **Examples**

### **Example 1: Simple pipeline**

```
./pipex input.txt "grep hello" "wc -l" output.txt
```

Equivalent to:

```
grep hello < input.txt | wc -l > output.txt
```

---

### **Example 2: Using absolute paths**

```
./pipex file "/bin/cat" "/usr/bin/grep hello" out
```

## ❗ **Error Handling**

Your program must handle the following:

### File Errors

* Infile does not exist
* Permission denied
* Outfile can't be opened/created

### Command Errors

* Command not found
* Invalid paths
* execve failure

### Pipe/Fork Errors

* pipe() failed
* fork() failed
* dup2() failed

### Argument Errors

* Not enough arguments
* Here_doc wrong format

Always print meaningful messages.

Example:

```
pipex: command not found: asd123
```

---

## 📚 **Detailed Explanation**

### 🔹 Finding the Path for Commands

You must read the PATH variable from `envp`:

```
PATH=/usr/local/bin:/usr/bin:/bin
```

Split paths by `:` and try:

```
/usr/local/bin/ls
/usr/bin/ls
/bin/ls
```

Use `access()` to check executability.

---

### 🔹 Using pipe()

A pipe gives two file descriptors:

```
pipe_fd[0] → read end
pipe_fd[1] → write end
```

cmd1 writes to pipe:

```
dup2(pipe_fd[1], STDOUT_FILENO)
```

cmd2 reads from pipe:

```
dup2(pipe_fd[0], STDIN_FILENO)
```

---

### 🔹 Forking children

First child handles cmd1
Second child handles cmd2

Parent closes all pipes and waits.

---

### 🔹 Using execve()

`execve(path, argv, envp)` replaces the current process image with a new one.

If execve fails → print error.
