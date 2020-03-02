# standard

Standard of language.

Each `<num>` and `<offset>` hold **4** bytes and **is signed**.

The `<num>` use little endian.

The `<offset>` is relative to the value of `PC` right now.

One statement must takes one line, redudant spaces and blank lines will be ignored. Lower statement is allowed.

Comment must be on its own line, and start with `#`.

## operation

```
// stack operation
PUSH <num>
DUP
POP

// arithmetic operation
ADD
SUB
MULTI
DIV
MOD

// logic operation
IF <offset>
IFNO <offset>

// system operation
NOP
HALT
```

## bit defination

### stack operation

**PUSH** push `<num>` to stack.

**DUP** duplicate the top of stack.

**POP** remove the value on the top of stack.

```
PUSH  => 0x05
DUP   => 0X06
POP   => 0x07
```

```
PUSH 3      => 0000: 05 00 00 00 03
POP         => 0000: 06
```

### arithmetic operation

The arithmetic operation **has no operation number**. While being used, it will pop two variable on the top of stack, calculate them and push result back to stack. For example:

```
stack                         stack
before:   operation: DIV      after:
  2       expression: 4 / 2      
  4                            2
  1                            1 
 ---                          ---
```

```
ADD     => 0x09
SUB     => 0x0A
MULTI   => 0x0B
DIV     => 0x0C
MOD     => 0x0D
```

### logic operation

Logic operation wile **pop stack after judge**, it will apply `<offset>` to PC if the top is (not) zero.

**The `<offset>` will be applied to PC and PC will not increase one automatically** if judge result is `true`. Else this instruction will be ignored and PC go to next instruction.

`IF` add the `<offset>` to PC if the top of stack **equal to zero**.

`IFNO` add the `<offset>` to PC if the top of stack **not equal to zero**.

```
IF      => 0x11
IFNO    => 0x10
```

```
IF 16       => 0000: 11 00 00 00 10
IFNO 32     => 0000: 10 00 00 00 20
```

### system operation

`NOP` just do nothing.

`HALT` shutdown the program.

```
NOP     => 0x01
HALT    => 0X00
```