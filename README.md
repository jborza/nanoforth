# nanoforth

An incomplete minimal Forth for Arduino, in C. The communication happens over the serial console.

Currently supports these words:
#### arithmetic
+
-
*
/
mod

#### comparison
<
>
=

#### stack
dup
drop
swap

#### output

emit
.
.s (print stack)



#### bitwise:
- and
- or
- xor
- invert
