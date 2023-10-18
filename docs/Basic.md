# Basic

## vimrc

### Description
vimrc.

1. Be careful of the version (currently `gnu++20` for WF)
2. `setxkbmap` command should be executed in terminal or smt.

### Test Status
No test needed

## Debug Macro

### Description
Debug code for dumping information.
### Test Status
No test needed.

## Increase Stack
### Description
Increase the stack size
### Test Status
Not even used

## Pragma Optimization
### Description
Magic Pragmas. It depends to choose Ofast or O3. For target related stuff, adding `arch=skylake` should work (no need for others). 
Also, a [way](https://codeforces.com/blog/entry/104586) to avoid [denormal numbers](https://en.wikipedia.org/wiki/Subnormal_number).
0x8000 for FTZ and 0x0040 for DAZ. [Intel Compiler Docs](https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-10/set-the-ftz-and-daz-flags.html).
Only works for SSE/AVX stuff.
### Test Status
Rarely used, no test

## IO Optimization
### Description
I/O bounded program needs this sweet optimization.
### Test Status
Rarely used, no test.

## SVG Writer
### Description
A helper to generate SVG. Support Line, Circle, and Text.
Should adjust sizes properly.
### Test Status
No Test
