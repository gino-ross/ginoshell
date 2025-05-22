# ginoshell

A mininal unix shell written in c99. Supports basic command execution, built-in commands, and process control

## Features

- Execute external commands (e.g `ls`, `gcc`, `./program`)
- Built-in commands:
  - `cd [dir]` - Change directory
  - `exit` - Exit the shell
- Clean output with error messaging

## Build

1. Clone the repository:

```bash
git clone https://github.com/gino-ross/ginoshell.git
cd ginoshell
```

2. Compile the code:

```bash
make
```

3. Run the shell:

```bash
./ginoshell
```

## Things to and

- Piping with | and redirection with > and <
- Basic tab completion for files/directories

