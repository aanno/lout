# Readme golout

This is a fork of the original lout system from 
`git@github.com:william8000/lout.git` (referenced as 'upstream').

The ultimate goal is to port upstream to go(lang). However, this is a long
term goal and as this is a pure hobbyist project, perhaps this will never
been archived.

The '_basser lout_' implementation will be referenced as `clout` in this
document. The (currently non-existing) '_go(-lang) lout_' implementation
will be referenced as `golout`.

However, there number of steps towards the goal:

- [x] Turn lout into a shared library.
- [x] Make it possible to use the shared library from go.
- [x] Compilation with C17 std with no warnings.
- [x] Use `clang` instead of `gcc` as (standard) compiler.
- [ ] Ongoing: Substantial reduction of macros (and `#define`s) in favour of
      _inline_ functions.
- [ ] Ongoing: Substantial reduction of (constant) `#define`s in favour of
      constant types (like `const char* const`). See `z00.c` for details.
- [ ] Ongoing: Substantial reduction of (constant) `#define`s in favour of
      enum where this is appropriate.
- [ ] Ongoing: Restructure of `externs.h` where needed to enable more 
      _inline_ functions.
- [ ] Typesafe enums.

## Golang port milestones

- [ ] Structs from `externs.h`: Rewrite struct nesting to struct* nesting
- [ ] Structs from `externs.h`: Remove struct bitfields (not supported in go)
- [ ] Structs from `externs.h`: Remove unions (not supported in go)
- [ ] Turn structs from `externs.h` to go struct (_not_ go `C.struct`)
- [ ] Use these golang structs from remaining C lout code.


## References and (old) contributed documents

* https://en.wikipedia.org/wiki/Lout_(software)
* [Home Page of Jeffrey H. Kingston](http://jeffreykingston.id.au/)
* Kingston, Jeffrey H (September 1993). "The Design and Implementation of the Lout Document Formatting Language". Software: Practice and Experience. 23 (9): 1001–41. CiteSeerX 10.1.1.45.9433. doi:10.1002/spe.4380230906. S2CID 22952199.
  + http://ftp.math.utah.edu/pub/tex/bib/spe.html#Kingston:1993:DIL
* Kahl, Wolfram (January 1999). "Beyond Pretty-Printing: Galley Concepts in Document Formatting Combinators". Practical Aspects of Declarative Languages: First International Workshop.
  + http://www.cas.mcmaster.ca/~kahl/Publications/Conf/Kahl-1999a.html
* https://people.bordeaux.inria.fr/lcourtes/doc/lout-20120925.pdf
