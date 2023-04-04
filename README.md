# Triangle_3D

Input: N - number of triangles and N ones of triangles in 3D (by 9 doubles or other types - 3 vertexes).

Output: numbers of triangles that intersect with any other. 

For example: <br>
Input:
``` bash
6
1 0 0 0 1 0 0 0 1
3 0 0 0 3 0 0 0 3
0 0 0 0 0 4 0 4 0
0 0 2 4 1 0 1 4 0
0 0 10 3 7 0 7 3 0
0 -4 0 0 -6 0 2 -5 0

```
Output:
```bash
3 4
```
Or output:
```bash
4 3
```
P.S (4 3 also is right)

## • About algorithm

The Möller algorithm is used. The theory is explaned in [this article](http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf). <br>

There are some optimisations in the project. 

## • How to make?

### - On Linux:

with script from the repo
```bash
bash build.sh
```
or using standart cmake command
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## • How to test?
There are two types of tests in directory [unit_tests](https://github.com/AlexArutiunian/Triangle_3D/tree/main/unit_tests).<br>
1) [algos](https://github.com/AlexArutiunian/Triangle_3D/tree/main/unit_tests/algos) - for testing function in [intersection.hpp](https://github.com/AlexArutiunian/Triangle_3D/blob/main/lib/intersection.hpp) <br>(as example, for testing The Möller algorithm)

2) [interface](https://github.com/AlexArutiunian/Triangle_3D/tree/main/unit_tests/interface) - for testing of containers like vector_3D, line_segment and so on.

### - To make tests on Linux:

```bash
bash build.sh
./tests_matrix
```