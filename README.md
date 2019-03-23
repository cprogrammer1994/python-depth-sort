# python-depth-sort

A simple module to sort the triangles of a mesh for python.

## Install

This module is **not available through pip**, it was designed to be forked and extended. Simplicity is a key goal in design. This module is using [glm](https://glm.g-truc.net/) and the Python's [c-api](https://docs.python.org/3/c-api/). The implementation can be found in the [depth_sort.cpp](depth_sort.cpp).

```
git clone https://github.com/cprogrammer1994/python-depth-sort
cd python-depth-sort
python setup.py develop
```

## Cheat Sheet

```py
import depth_sort
```

### simple mesh

```py
# vertices
mesh = np.array([
    [[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]],
    [[0.0, 0.0, 1.0], [1.0, 0.0, 1.0], [0.0, 1.0, 1.0]],
], dtype='f4')

result = depth_sort.sort(direction=(0.0, 0.0, -1.0), mesh=triangles, stride=12)
# stride is the number of bytes to skip in mesh to get a new vertex
# result is a bytes object

sorted_index = np.frombuffer(result, dtype='i4').reshape(-1, 3)
```

### indexed mesh

```py
# vertices
mesh = np.array([
    [[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]],
    [[0.0, 0.0, 1.0], [1.0, 0.0, 1.0], [0.0, 1.0, 1.0]],
], dtype='f4')

# faces
index = np.array([
    [0, 1, 2],
    [3, 4, 5],
], dtype='i4')

result = depth_sort.isort(direction=(0.0, 0.0, -1.0), mesh=triangles, index=index, stride=12)
# stride is the number of bytes to skip in mesh to get a new vertex
# result is a bytes object

sorted_index = np.frombuffer(result, dtype='i4').reshape(-1, 3)
```
