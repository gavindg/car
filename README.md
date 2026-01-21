# CAR
a `C`++ `A`scii `R`enderer
written by Gavin Gee

## About
This project is a simple software rasterizer that renders scenes to your terminal.

This was my final project for CS112: Computer Graphics at UCI, and as 
such it is just a proof of concept / learning exercise

## Building + Running the Program
First, build the program using the given Makefile:
```bash
make
```
If you are on windows and have the GNU compiler collection installed, you should run 
```bash
make win
```
instead.

To run the program, simply run the generated executable. It takes a few flags:
```bash
./car [0|1] ['tris'|'depth']
```
The first flag is the scene number, which can be 0 or 1. Scene 0 is a rotating cube,
and scene 1 is a set of overlapping triangles to prove the correctness of z-sorting.

The second flag is the material for the model. `tris` will display the triangle number
on each fragment in a triangle, and `depth` will visualize the depth of each fragment.

When ran without any arguments, it will display scene 0 with material `tris`.
