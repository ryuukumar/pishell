# The shorthand PiShell guide

PiShell 0.1
(c) Aditya Kumar 2024

PiShell is a simple shell written in C++ for embedded systems. It works on a live interpreter. It has 32 64-bit integers numbered 0-31 addressable as their indices.

Commands are not case-sensitive. Arguments are listed in the order they appear using alphabets a-z.

## Basic Operations

### `exit`

```exit```

Exit the shell.

### `echo`

```echo <text>```

Print everything after the command. There is no requirement for quotes.

### `input`

```input <Rx>```

Input a 64-bit integer value into register x.

### `help`

```help```

Print the help message.

### `mem`

```mem```

List the number of registers, number of functions definable, maximum function name size and maximum function length.

### `set`

```set <Rx> <64-bit value>```

Store some constant value in the register x.

### `val`

```val <Rx>```

Print the value of register x.

### `drop`

```drop```

Set the value of all registers to zero.

### `show`

```show```

Print the values of all the registers.

## Arithmetic and Comparison

### `and`

```and <Rx> <Ry> <Rz>```

Store the value of the logical AND of values in registers x and y into the register z.

### `or`

```or <Rx> <Ry> <Rz>```

Store the value of the logical OR of values in registers x and y into the register z.

### `add`

```add <Rx> <Ry> <Rz>```

Store the value of the sum of values in registers x and y into the register z.

### `sub`

```sub <Rx> <Ry> <Rz>```

Store the value of the difference of values in registers x and y into the register z.

### `mul`

```mul <Rx> <Ry> <Rz>```

Store the value of the product of values in registers x and y into the register z.

### `div`

```div <Rx> <Ry> <Rz>```

Store the value of the quotient of values in registers x and y into the register z.

### `inv`

```inv <Rx> <Ry>```

Store the value of the logical NOT of value in register x into the register z.

### `blinv`

```blinv <Rx> <Ry>```

Store the boolean inverse of the value in register x into the register z.

The boolean inverse is given by:
- 0, if the input value is anything other than 0
- 1, if the input value is 0

### `cmp`

```cmp <Rx> <op> <Ry>```

Store the result of the comparison between the two values stored in registers x and y. The comparison operation specified in <op> is specified by the strings:

- '='
- '<'
- '>'
- '<='
- '>='
- '!='

Example comparison: `cmp 0 != 1`

The result of this comparison is stored in a special register Rc, and this register can be read by some other instruction.

### `stcmp`

```stcmp <Rx>```

Store the result of most recent `cmp` operation (as stored in Rc) to the register x.

## Defining a Function
To define a function, use the `deffxn` instruction. The interpreter shell will switch from usual input prompt ` > ` to function input prompt ` + `. All instructions entered until the `endfxn` instruction is entered is not syntax-checked (but it is checked for valid operation) and it is directly stored into the function text storage.

There is no specific requirement for order of function definition, as long as it is designed in such a manner that the function is defined before the first `jmp` instruction calling the function.

Functions do not receive a fresh set of registers, and the same set of registers are available to the function as well as the global space.

Functions cannot return values, hence any return data will have to be stored in registers.

Nested functions are not supported and will lead to undefined behavior.

### `deffxn`

```deffxn <string>```

Define a function with the name as given in the argument. **Names are case sensitive.** The limit for name length is usually 25, but it can be checked by the `mem` instruction.

### `endfxn`

```endfxn```

End function mode and store the entered function. Shell returns to normal execution mode.

### `jmpt`

```jmpt <function>```

If the value of last comparison (as stored in Rc) evaluates to true, jump to the function as specified in the argument.

### `jmp`

```jmp  <function>```

Jump to the function as specified in the argument.

### `snit`

```snit```

If the value of last comparison (as stored in Rc) evaluates to true, skip the next instruction.

### `lfxn`

```lfxn```

Print out the name and text of all the functions currently stored.