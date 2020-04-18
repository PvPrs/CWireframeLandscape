# 3D Wireframe Landscapes
Generate a 3D wireframe landscape from a simple input without the use of any standard libraries, written in C.
### result:
<img src="42.gif"></br>

#### Install & Usage:
To download & setup the project simply clone the repository into the desired directory and run the Makefile.
```
git clone https://github.com/ophionB/fdf.git
cd fdf
make
```
To run the project with one of the example maps execute the following command in the terminal.
```
./fdf maps/42.fdf
```
#### Input
The input is represented by 'values' ordered in position which simply represent the <b>height</b> of a specific coordinate.
in the example map <b>Coordinate: 2, 2</b> has a height of 10.
```
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
  0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
  0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
  0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
  0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
  0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
  0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

