# procpp4ed: A code sandbox for learning Marc Gregoire, Professional C++, 4th Edition, Wrox, 2018

* Tested with GCC (typically `gcc-7`)

* Note that the following command, copied from the book, is incorrect...
  * It is because that `gcc` tries to resolve symbols in order of command-line arguments...
  * For more information on linking of `gcc`, read Chapter 7 of CS:APP3e (R. E. Bryant and D. R. O'Hallaron, Computer Systems: A Programmer's Perspective, 3rd Ed., Pearson, 2015.).

```shell
gcc -lstdc++ -std=c++17 -o <executable_name> <source1.cpp> [source2.cpp ...]
```

* Two alternatives are available:
  * The first command explicitly links the Standard C++ Library *after resolving symbols in the sources*.
  * The second command implicitly links the Standard C++ library *after resolving symbols in the sources*.

```shell
gcc -std=c++17 -o <executable_name> <source1.cpp> [source2.cpp ...] -lstdc++
g++ <source1.cpp> -o <executable_name> <source1.cpp> [source2.cpp ...]
```
