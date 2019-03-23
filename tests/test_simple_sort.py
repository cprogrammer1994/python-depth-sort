import itertools

import numpy as np
import pytest

import depth_sort


def test_simple_mesh():
    triangles = np.array([
        [[0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 1.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 4.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 3.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 2.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
    ], dtype='f4')

    result = np.frombuffer(depth_sort.sort((0.0, 0.0, -1.0), triangles, 12), 'i4')
    expected = [6, 7, 8, 9, 10, 11, 12, 13, 14, 3, 4, 5, 0, 1, 2]
    np.testing.assert_equal(result, expected)


def test_indexed_mesh():
    triangles = np.array([
        [[0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 1.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 4.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 3.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
        [[0.0, 0.0, 2.0], [0.0, 0.0, 0.0], [0.0, 0.0, 0.0]],
    ], dtype='f4')

    index = np.array([
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [9, 10, 11],
        [12, 13, 14],
    ], dtype='i4')

    result = np.frombuffer(depth_sort.isort((0.0, 0.0, -1.0), triangles, index, 12), 'i4')
    expected = [6, 7, 8, 9, 10, 11, 12, 13, 14, 3, 4, 5, 0, 1, 2]
    np.testing.assert_equal(result, expected)


if __name__ == '__main__':
    pytest.main([__file__])
