# How to use C-Python
# https://docs.python.org/3.7/extending/building.html#building

On the module directory, run "python setup.py build install"

This will compile the C++ file module.

You first need to set

export CFLAGS="-stdlib=libc++  -std=c++14"


https://www.oreilly.com/library/view/python-cookbook/0596001673/ch16s03.html


https://docs.python.org/2.0/ext/buildValue.html

