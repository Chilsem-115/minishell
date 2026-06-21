# minishell

`minishell` is a small interactive Unix shell written in C. meant as a recreational project that reproduces the core command-processing behavior of Bash
that includes: prompt handling, command history, quoting, environment
expansion, pipelines, redirections, built-in commands, and signal-aware process
execution.

The project is primarily an exercise in parsing and Unix process control. Input
is not executed directly, it goes through multiple steps: tokenized, expanded, converted into an abstract syntax tree (AST), and then evaluated by the execution layer.

## Supported behavior

- Interactive prompt with the current working directory and Readline history.
- Executable lookup through `PATH`, plus relative and absolute command paths.
- Single and double quotes.
- Environment variable expansion (`$NAME`) and exit-status expansion (`$?`).
- command pipelines using `|`.
- Input redirection with `<`.
- Output truncation and append redirection with `>` and `>>`.
- Here-documents with `<<`.
- Exit-status propagation from commands, pipelines, and signals.
- Interactive handling of `Ctrl-C`, `Ctrl-\`, and end-of-file (`Ctrl-D`).

The following built-ins are implemented:

| Built-in | Behavior |
| --- | --- |
| `echo` | Prints arguments; accepts repeated valid `-n` options |
| `cd` | Changes directory and updates `PWD` and `OLDPWD` |
| `pwd` | Prints the current working directory |
| `export` | Adds or updates environment variables; lists them without arguments |
| `unset` | Removes environment variables |
| `env` | Prints the current environment |
| `exit` | Exits with optional numeric status validation |

This is not intended to be a complete POSIX or Bash implementation. Features
outside the current grammar include logical operators (`&&`, `||`), command
lists (`;`), subshells, wildcard expansion, job control, and command
substitution.
It is however built in a flexible way and designed to make it easier to add more operators and components to it.

## Processing model

Each non-empty input line passes through four distinct stages:

1. **Tokenization** identifies words, pipes, and redirection operators while
   validating quote and operator syntax.
2. **Expansion** resolves environment variables and `$?`, preserves quoting
   semantics, and splits expanded unquoted text into tokens.
3. **AST generation** represents commands, redirections, and pipelines as a
   tree instead of relying on ad hoc string processing.
4. **Execution** applies redirections, dispatches built-ins, creates pipes and
   child processes, resolves executable paths, and records the final status.

## Repository structure

```text
.
├── Makefile
├── libft/                       custom C utility library and ft_printf
└── main/
    ├── messh.c                  initialization, signals, and entry point
    ├── core.c                   read-evaluate loop
    ├── tokenizer/               lexical analysis and syntax validation
    ├── expansion/               variables, exit status, and quote removal
    ├── ast_generator/           AST construction and node definitions
    ├── execution/
    │   ├── built_in/            shell built-ins
    │   ├── cmd_execute/         external command dispatch
    │   ├── environment/         internal environment representation
    │   ├── pipe/                pipeline process management
    │   └── redirection/         files and here-documents
    └── memory/                  token and AST cleanup
```

Runtime state is held in a central `t_context`, which owns the current line,
token list, AST, environment list, exit status, and execution bookkeeping.

The environment is copied into a linked list at startup and converted back to an
`envp`-style array when an external command is launched.

## Requirements

- A Linux or compatible Unix-like environment
- `cc` with C compilation support
- GNU Make
- GNU Readline development headers and library

Install the build dependencies for your distribution:

**Void Linux**

```sh
sudo xbps-install -S base-devel readline-devel
```

**Debian/Ubuntu**

```sh
sudo apt install build-essential libreadline-dev
```

**Fedora**

```sh
sudo dnf install gcc make readline-devel
```

**Arch Linux**

```sh
sudo pacman -S --needed base-devel readline
```

## Build and run

Build the shell from the repository root:

```sh
make
./minishell
```

The Makefile compiles with `-Wall -Wextra -Werror` and links the local `libft` and Readline libraries.

Available maintenance targets:

```sh
make clean     # remove object files
make fclean    # remove object files, libraries, and the binary
make re        # perform a clean rebuild
```

## Usage examples

```sh
echo "user: $USER"
printf "alpha\nbeta\n" | grep beta | wc -l
cat < input.txt > output.txt
echo first > log.txt
echo second >> log.txt
cat << EOF
current directory: $PWD
EOF
export PROJECT=minishell
env | grep PROJECT
echo $?
```

## Implementation notes

- Built-ins execute in the current process when used as a standalone command,
  allowing state-changing operations such as `cd`, `export`, and `unset` to
  persist. Within a pipeline they execute in a child process.
- Pipeline status follows the rightmost command, consistent with conventional
  shell behavior.
- Standard input and output are duplicated before command execution and
  restored afterward, so redirections do not leak into the next prompt cycle.
- Here-document input is collected before AST execution and stored in a
  restricted temporary file used as redirected standard input.
- The code uses a project-level allocation collector alongside explicit cleanup
  for tokens, AST nodes, environment entries, and process resources.

## Current engineering scope

The repository does not currently include an automated test suite or a CI
configuration. validation should therefore compare interactive results and exit statuses against Bash
for syntax that lies within the supported feature set.
