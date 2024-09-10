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
[                       use loop to set the next four cells to 70/100/30/10
    > {+|7}
    > {+|10} 
    > {+|3}                  
    > +                     
    {<|4} -                
]                   
> ++ .                  print 'H'
> + .                   print 'e'
{+|5} ++ .              print 'l'
.                       print 'l'
+++ .                   print 'o'
> ++ .                  print ' '
<< {+|15} .             print 'W'
> .                     print 'o'
+++ .                   print 'r'
{-|5} - .               print 'l'
{-|5} --- .             print 'd'
> + .                   print '!'
> .                     print '\n'
```

Just lets you specify how many of stuff you want to put 
