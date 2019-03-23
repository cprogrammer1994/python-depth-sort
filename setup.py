import platform

from setuptools import Extension, setup

target = platform.system().lower()

extra_compile_args = []

if target.startswith('linux'):
    extra_compile_args.append('-std=c++11')

ext = Extension(
    name='depth_sort',
    sources=['depth_sort.cpp'],
    extra_compile_args=extra_compile_args,
)

setup(
    name='depth_sort',
    version='0.1.0',
    ext_modules=[ext],
)
