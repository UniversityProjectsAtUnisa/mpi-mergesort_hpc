# Course: High Performance Computing 2021/2022
#
# Lecturer: Francesco Moscato    fmoscato@unisa.it
#
# Group:
# De Stefano Alessandro   0622701470  a.destefano56@studenti.unisa.it
# Della Rocca Marco   0622701573  m.dellarocca22@studenti.unisa.it
#
# MPI implementation of mergesort algorithm
# Copyright (C) 2022 Alessandro De Stefano (EarendilTiwele) Marco Della Rocca
# (marco741)
#
# This file is part of OMP Mergesort implementation.
#
# MPI Mergesort implementation is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MPI Mergesort implementation is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MPI Mergesort implementation.  If not, see
# <http://www.gnu.org/licenses/>.

# release is default, for debugging : make BUILD=debug
BUILD := debug
flags.debug = -g -Wall
flags.release = -w

# parallel is default, for serial : make EXECUTION=serial
O := 0
FILENAME := input/in.txt
N := 10000
MAX := 2147483647
MIN := -$(MAX)

# Wildcard to commands recipe
space := #
space +=
semicolon := ;

IDIR = include
SRCDIR = src
BUILDDIR = build
TESTDIR = test
EXECUTABLE = main.out

CC = mpicc
RUN = mpirun
CFLAGS = ${flags.${BUILD}} -I$(IDIR)
LDFLAGS = -lm

COMMON = utils
COMMON_OBJECTS = $(addsuffix .o, $(COMMON))
TESTS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(TESTDIR)/$(BUILDDIR)/%.o,$(TESTS))
TEST_EXECUTABLES = $(patsubst %.o,%.out,$(TEST_OBJECTS))
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEPS = $(wildcard $(IDIR)/*.h)

.PHONY: all
all: dir $(BUILDDIR)/$(EXECUTABLE) $(TEST_EXECUTABLES)

.PHONY: dir
dir:
	mkdir -p $(BUILDDIR)

.PHONY: test_dir
test_dir:
	mkdir -p $(TESTDIR)/$(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(MAKEFILE_LIST)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE) $(TESTDIR)/$(BUILDDIR)/*.o $(TESTDIR)/$(BUILDDIR)/*.out

.PHONY: run
run: $(BUILDDIR)/$(EXECUTABLE)
	$(RUN) --oversubscribe -np 8 $(BUILDDIR)/$(EXECUTABLE)

# Run all tests
.PHONY: test
test: test_dir dir $(TEST_EXECUTABLES)
	$(RUN) --oversubscribe -np 8 $(subst $(space),$(semicolon),$(TEST_EXECUTABLES)) 

$(TEST_EXECUTABLES): $(TESTDIR)/$(BUILDDIR)/%.out: $(TESTDIR)/$(BUILDDIR)/%.o $(BUILDDIR)/%.o $(BUILDDIR)/$(COMMON_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TESTDIR)/$(BUILDDIR)/%.o: $(TESTDIR)/%.c $(DEPS) $(MAKEFILE_LIST)
	$(CC) -c -O2 $< -o $@ $(CFLAGS)

.PHONY: generate_file
generate_file: scripts/generate_file.py $(MAKEFILE_LIST)
	python3 -m venv venv
	( \
       . venv/bin/activate; \
       pip install -r $(PIP_REQUIREMENTS); \
		$(PYTHON) scripts/generate_file.py $(N) --min $(MIN) --max $(MAX) --input $(FILENAME); \
    )