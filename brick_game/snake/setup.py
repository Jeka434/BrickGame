import os
import inspect
from setuptools import setup
from setuptools.extension import Extension
from Cython.Build import cythonize

if os.name == "nt":
    standart = "/std:c++17"
else:
    standart = "-std=c++17"

current_dir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parent_dir = os.path.dirname(current_dir)

ext_modules = [Extension("game",
                         ["game.pyx", "model/model.cc",
                          "controller/controller.cc"],
                         extra_compile_args=[standart],
                         include_dirs=[parent_dir, os.path.join(parent_dir, "common")],
                         language='c++')]


setup(
    name='game',
    ext_modules=ext_modules
)
