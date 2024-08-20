import os
import inspect
from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)

ext_modules = [Extension("game",
                         ["game.pyx", "figures.c", "fsm.c", "tetris.c"],
                         include_dirs=[parent_dir, os.path.join(parent_dir, "common")],
                         language='c')]

setup(
    name='game',
    ext_modules=ext_modules
)
