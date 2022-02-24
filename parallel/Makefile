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
# This file is part of MPI Mergesort implementation.
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

O := 0
NUM_PROCESSES := 2
FILENAME := input/in.txt

# Wildcard to commands recipe
space := #
space +=
semicolon := ;

IDIR = include
SRCDIR = src
BUILDDIR = build
TESTDIR = test
COMMONDIR = ../common
EXECUTABLE = main.out

CC = mpicc
RUN = mpirun
MPI = --oversubscribe -np $(NUM_PROCESSES)
CFLAGS = ${flags.${BUILD}} -I$(IDIR) -I$(COMMONDIR)/$(IDIR)
LDFLAGS = -lm

TESTS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(TESTDIR)/$(BUILDDIR)/%.o,$(TESTS))
TEST_EXECUTABLES = $(patsubst %.o,%.out,$(TEST_OBJECTS))
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
COMMON_SOURCES = $(wildcard $(COMMONDIR)/$(SRCDIR)/*.c)
COMMON_OBJECTS = $(patsubst $(COMMONDIR)/$(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(COMMON_SOURCES))
DEPS = $(wildcard $(IDIR)/*.h) $(wildcard $(COMMONDIR)/$(IDIR)/*.h)

.PHONY: all
all: dir $(BUILDDIR)/$(EXECUTABLE) $(TEST_EXECUTABLES)

.PHONY: dir
dir:
	mkdir -p $(BUILDDIR)

.PHONY: test_dir
test_dir:
	mkdir -p $(TESTDIR)/$(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS) $(COMMON_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(MAKEFILE_LIST) dir
	$(CC) -c -O$(O) $< -o $@ $(CFLAGS)

$(COMMON_OBJECTS): $(BUILDDIR)/%.o: $(COMMONDIR)/$(SRCDIR)/%.c $(DEPS) $(MAKEFILE_LIST) dir
	$(CC) -c -O$(O) $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE) $(TESTDIR)/$(BUILDDIR)/*.o $(TESTDIR)/$(BUILDDIR)/*.out

.PHONY: run
run: $(BUILDDIR)/$(EXECUTABLE)
	$(RUN) $(MPI) $(BUILDDIR)/$(EXECUTABLE) $(FILENAME)

# Run all tests
.PHONY: test
test: $(TEST_EXECUTABLES)
	$(RUN) $(MPI) $(subst $(space),$(semicolon),$(TEST_EXECUTABLES))

$(TEST_EXECUTABLES): $(TESTDIR)/$(BUILDDIR)/%.out: $(TESTDIR)/$(BUILDDIR)/%.o $(BUILDDIR)/%.o $(COMMON_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(TESTDIR)/$(BUILDDIR)/%.o: $(TESTDIR)/%.c $(DEPS) $(MAKEFILE_LIST) dir test_dir
	$(CC) -c -O2 $< -o $@ $(CFLAGS)