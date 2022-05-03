# simple-router

## Introduction

This is a repository storing OOP pre-learning project.

A simple router implements packet classification (linear search and unoptimized hi-cuts algorithms).



Compiled by **mingw64 + CMake**.

An Error was known when compiling this project with `-O3`. (owing to my terrible codes)

## Usage

```bash
usage: simple-router [options] ... <rule file> <data file>
options:
  -o, --open         Output File         - assign an output file <list file> (overwrite existed file). (string [=ans])
  -b, --benchmark    Benchmark Mode      - run router as the assigned <list file>. (string [=list.dat])
  -d, --debug        Debug Mode          - run router in debug mode.
  -i, --info         Show info           - show info, including time and memory info.
  -?, --help         print this message
```

## Acknowledgment

command line parsing is powered by an opensource repo - [cmdline](https://github.com/tanakh/cmdline).
