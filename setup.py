import sys
from setuptools import setup, Extension
import pybind11
import platform

extra_compile_args = []
extra_link_args = []

if platform.system() == "Windows":
    extra_compile_args.append("/openmp")
else:
    extra_compile_args.append("-fopenmp")
    extra_link_args.append("-fopenmp")

ext_modules = [
    Extension(
        "omp_arrays",
        ["omp_arrays.cpp"],
        include_dirs=[pybind11.get_include()],
        extra_compile_args=extra_compile_args,
        extra_link_args=extra_link_args,
        language="c++"
    ),
]

setup(
    name="omp_arrays",
    version="0.1",
    author="Your Name",
    author_email="your_email@example.com",
    description="Array operations algorithms using OpenMP and Pybind11",
    ext_modules=ext_modules,
    install_requires=["pybind11"],
)
