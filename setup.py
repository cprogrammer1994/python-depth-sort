from setuptools import Extension, setup

ext = Extension(
    name='depth_sort',
    sources=['depth_sort.cpp'],
)

setup(
    name='depth_sort',
    version='0.1.0',
    ext_modules=[ext],
)
