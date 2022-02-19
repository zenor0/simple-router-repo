# simple-router

## Introduction

This repository is used to store OOP pre-learning labs.

This simple router implements packet classification (linear search, hi-cuts undone yet).



Compiled by **mingw64 + CMake**.

## Usage

usage: simple-router [options] ... <rule file> <data file>
options:
  -o, --open         Output File         - assign an output file <list file> (overwrite existed file). (string [=ans])
  -b, --benchmark    Benchmark Mode      - run router as the assigned <list file>. (string [=list.dat])
  -d, --debug        Debug Mode          - run router in debug mode.
  -i, --info         Show info           - show info, including time and memory info.
  -?, --help         print this message


## Acknowledgment

command line parsing is supported by an opensource repo - cmdline[https://github.com/tanakh/cmdline].
