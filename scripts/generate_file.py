#!venv/bin/python3
'''
Course: High Performance Computing 2021/2022

Lecturer: Francesco Moscato    fmoscato@unisa.it

Group:
De Stefano Alessandro   0622701470  a.destefano56@studenti.unisa.it
Della Rocca Marco   0622701573  m.dellarocca22@studenti.unisa.it

MPI implementation of mergesort algorithm
Copyright (C) 2022 Alessandro De Stefano (EarendilTiwele) Marco Della Rocca
(marco741)

This file is part of OMP Mergesort implementation.

MPI Mergesort implementation is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MPI Mergesort implementation is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MPI Mergesort implementation.  If not, see
<http://www.gnu.org/licenses/>.
'''

"""
Generates an input file of random numbers
"""


import argparse
import random
from tqdm import tqdm
from pathlib import Path
parser = argparse.ArgumentParser(description='Generate fixed amount of random integers and saves it in the INPUT file')
parser.add_argument('N', metavar='N', type=int,
                    help='the amount of numbers to be generated. Max (2^64 - 2^32).')
parser.add_argument('--max', dest='max', default=2**31 - 1, type=int,
                    help="""maximum number that can be generated;
                    default: 2**31 - 1""")
parser.add_argument('--min', dest='min', type=int,
                    help="""minimum number that can be generated;
                    default: -max
                    """)
parser.add_argument('--input', dest='input', default="input/in.txt",
                    help="""input file name;
                    default: 2**31 - 1""")


def generate_file(N, min_value=None, max_value=2**31 - 1, filename="input/in.txt"):
    """Generates N integers between min_value and max_value and exports the results in the file filename

    Args:
        N (int): Amount of integers to be generated
        min_value (int, optional): Minimum number that can be generated. Defaults to -max_value.
        max_value (int, optional): Maximum number that can be generated. Defaults to 2**31-1.
        filename (str, optional): Name of the file to export to. Defaults to "input/in.txt".
    """

    # Before generating creates the parent folder if doesn't already exist
    Path(filename).parent.mkdir(parents=True, exist_ok=True)
    with open(filename, "w") as f:
        f.write(str(N)+"\n")
        for _ in tqdm(range(N)):
            r = random.randint(min_value, max_value)
            f.write(f"{r} ")


def main():
    N = parser.parse_args().N
    _max = parser.parse_args().max
    _min = parser.parse_args().min
    _input = parser.parse_args().input

    if N < 0 or N > (2**64 - 2**32):
        print("Invalid value for N")
        return
    _min = _min if _min is not None else -_max

    print(f"N: {N}, max: {_max}, min: {_min}, filename: {_input}")

    generate_file(N, _min, _max, _input)


if __name__ == "__main__":
    main()
