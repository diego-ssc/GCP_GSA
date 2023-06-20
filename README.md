# GCP_GSA
Graph Coloring Problem/Gravitational Search Algorithm in C.

The following program uses the Gravitational Search Algorithm to find
solutions to the Graph Coloring Problem.

## Installation
Run:

```
meson setup -Dbuildtype=release build
```
in the root directory.

and:

```
meson compile -C build/
```
to compile the program.


## Usage:
```
./GCP_GSA -f [input file] [options]
```
# Options:
```
-s the seed
-n the hypothesized chromatic number
-d the graph dimension
-i the maximum number of iterations
-c the maximum degree of comfort
-v verbose execution
-r the color radius
```

## Dependencies

### [Meson](https://www.sqlite.org/download.html)
```
meson
Version: 1.0.0
```
