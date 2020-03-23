# standard

Standard of language.

Each `<num>` hold **4** bytes and is **signed** and use **little endian**.

There are to registers `A`, `B` and `C` to use.

One statement must takes one line, redudant spaces and blank lines will be ignored. Lower statement is allowed.

Comment must be on its own line, and start with `#`.

## operation

```
// system operation
NOP
HALT

// register operation
REGA
REGB
REGC
LOADA
LOADB
LOADC

// stack operation
READ
PUSH <num>
DUP
POP

// logic operation
JMP
IF <identifier>
IFNO <identifier>
IFP <identifier>

// arithmetic operation
ADD
SUB
MULTI
DIV
MOD
```

## bit defination

### system operation

- `NOP` just do nothing, can be used as `<identifier>`.
- `HALT` shutdown the program, and print the content in the stack.

```
NOP     => 0x01
HALT    => 0X00
```

### register operation

There are three register, the first two register will be use by arithmetic, the third can be use by programmer as he/she like.

- `REGA` / `REGB` / `REGC` register the value on top of stack to register **A** / **B** / **C** and **pop it**.
- `LOADA` /`LOADB` /`LOADC` load the value in register **A** / **B** / **C** to stack, the value in register will **remain**.

```
REGA  => 0x10
REGB  => 0x11
REGC  => 0x12

LOADA => 0X14
LOADB => 0X15
LOADC => 0X16
```

### stack operation

- `READ` read a **signed integer** from standard input and push it to stack.
- `PUSH` push `<num>` to stack.
- `DUP` duplicate the top of stack.
- `POP` remove the value on the top of stack.

```
READ  => 0X24
PUSH  => 0x25
DUP   => 0X26
POP   => 0x27
```

```
READ        => 0000: 24
PUSH 3      => 0000: 25 03 00 00 00
DUP         => 0000: 26
POP         => 0000: 27
```

### logic operation

`<identifier>` is the declared like `:[a-zA-Z_][a-zA-Z0-9_]*`

**The stack will be popped after judge.**

- `JMP` jump to `<identifier>`.
- `IF` jump to `<identifier>` if the top of stack **equal to zero**.
- `IF` jump to `<identifier>` if the top of stack **not equal to zero**.
- `IFP` jump to `<identifier>` if the top of stack **bigger than zero**.

```
JMP     => 0x30
IF      => 0x31
IFNO    => 0x32
IFP     => 0x33
```

```
ident:
...

# suppose the ident's offset of program is 0x78563412
JMP ident       => 0000: 30 12 34 56 78
IF ident        => 0000: 31 12 34 56 78
IFNO ident      => 0000: 32 12 34 56 78
IFP ident       => 0000: 33 12 34 56 78
```

### arithmetic operation

Calculate with two values in registers and **push result to stack**. Suppose the value in register **A** is `a`, and **B** is `b`, the operatation will like `a <op> b`.

```
ADD     => 0x40
SUB     => 0x41
MULTI   => 0x42
DIV     => 0x43
MOD     => 0x44
```
