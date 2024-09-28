import pybind11
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext

ext_modules = [
    Extension(
        'betterdict',
        ['betterdict.cpp'],
        include_dirs=[pybind11.get_include()],
        language='c++',
    ),
]

setup(
    name='betterdict',
    version='1.0.0',
    ext_modules=ext_modules,
    cmdclass={'build_ext': _build_ext},
    install_requires=[
        'pybind11>=2.13.6'
    ],
)
