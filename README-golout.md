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
