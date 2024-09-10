# mbfk-chain
Compiles .mbf files into .bf files
## Todo
Add other compiler support (right now it requires brainc in path)
## WIP howto
1. Make it
2. Use it but if you want to keep the output specify with `-k` or `--keep` ya
## Wtf is mbf
BF for people who aint got the time for all of that typing. Example helloworld.mbf:
```
{+|10}
[
   > {+|7}
   > {+|10}
   > {+|3}
   > + 
   {<|4} - 
]

> ++ .      C2 Now eq to 72 H
> + .       C3 Now eq to 101 e
{+|5} ++ .. C3 Now eq to 108 l
+++ .       C3 Now eq to 111 o

> ++ .      C4 Now eq to 32 space

<< {+|15} . C2 Now eq to 87 W
> .         C3 Eq to o
+++ .       C3 Now eq to 114 r
{-|6} .     C3 Now eq to 108 l
{-|8} .     C3 Now eq to 100 d
> + .       C4 Now eq to 33 !
```

Just lets you specify how many of stuff you want to put 
