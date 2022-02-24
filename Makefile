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

NUM_PROCESSES := 2
FILENAME := input/in.txt
O := 0
N := 10000
MAX := 2147483647
MIN := -$(MAX)
PIP_REQUIREMENTS = requirements.txt

TOPTARGETS := all dir test_dir clean run test 

SUBDIRS := serial parallel

.PHONY: $(TOPTARGETS)
$(TOPTARGETS): $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	if [ "$(filter $(MAKECMDGOALS), $(SUBDIRS))" = "" ] || [ "$(filter $(MAKECMDGOALS), $@)" != "" ]; then \
		$(MAKE) -C $@ $(filter-out $(SUBDIRS),$(MAKECMDGOALS)) BUILD=$(BUILD) FILENAME=$(addprefix ../, $(FILENAME)); \
	fi

.PHONY: generate_file
generate_file: scripts/generate_file.py $(MAKEFILE_LIST)
	python3 -m venv venv
	( \
       . venv/bin/activate; \
       pip install -r $(PIP_REQUIREMENTS); \
		$(PYTHON) scripts/generate_file.py $(N) --min $(MIN) --max $(MAX) --input $(FILENAME); \
    )

.PHONY: measures
measures: $(MAKEFILE_LIST)
	python3 -m venv venv
	( \
       . venv/bin/activate; \
       pip install -r $(PIP_REQUIREMENTS); \
	$(PYTHON) scripts/generate_measures.py; \
	$(PYTHON) scripts/generate_graphs.py; \
	$(PYTHON) scripts/generate_tables.py; \
    )