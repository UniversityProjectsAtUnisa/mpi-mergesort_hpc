# Course: High Performance Computing 2020/2021
# 
# Lecturer: Francesco Moscato    fmoscato@unisa.it
# 
# Group: 
# De Stefano Alessandro   0622701470  a.destefano56@studenti.unisa.it
# Della Rocca Marco   0622701573  m.dellarocca22@studenti.unisa.it
# 
# OMP implementation of mergesort algorithm 
# Copyright (C) 2021 Alessandro De Stefano (EarendilTiwele) Marco Della Rocca (marco741)
# 
# This file is part of OMP Mergesort implementation.
# 
# OMP Mergesort implementation is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# OMP Mergesort implementation is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with OMP Mergesort implementation.  If not, see <http: //www.gnu.org/licenses/>.


# release is default, for debugging : make BUILD=debug

IDIR = include
SRCDIR = src
BUILDDIR = build
EXECUTABLE = main.out

CC = mpicc
RUN = mpirun
CFLAGS = -w -I$(IDIR)
LDFLAGS = -lm

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEPS = $(wildcard $(IDIR)/*.h)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(MAKEFILE_LIST)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: run
run: $(BUILDDIR)/$(EXECUTABLE)
	$(RUN) -np 8 $(BUILDDIR)/$(EXECUTABLE)
