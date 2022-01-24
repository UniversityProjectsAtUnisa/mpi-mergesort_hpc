# Contest MPI

Docs status:\
[![Netlify Status](https://api.netlify.com/api/v1/badges/48091397-01e7-4783-ad50-3003d7ced228/deploy-status)](https://contestmpi.netlify.app/)

## General Instructions

To build the executable both for tests and source code run\
`make`

To clean the .o files in the build directories run\
`make clean`

To build and execute test cases run\
`make test [NUM_PROCESSES=NUM_PROCESSES]`

To generate measures (TAKES A LOT OF TIME! Our measures are already included so you should skip this step) run\
`make measures`

To generate a file with random numbers run\
`make generate_file [N=N[:10000]] [MAX=MAX[:2147483647]] [MIN=MIN[:-MAX]] [FILENAME=path/to/inputfile[:input/in.txt]]`

To build and execute the source code run\
`make run [NUM_PROCESSES=NUM_PROCESSES] [FILENAME=path/to/inputfile[:input/in.txt]]`

To build and execute *SILENTLY* the source code run\
`make -s run [NUM_PROCESSES=NUM_PROCESSES] [FILENAME=path/to/inputfile[:input/in.txt]]`

To generate a file with random numbers and execute a single run of the mergesort run\
`make generate_file run [N=N[:10000]] [MAX=MAX[:2147483647]] [MIN=MIN[:-MAX]] [FILENAME=path/to/inputfile[:input/in.txt]]`

To execute one of these commands (all dir test_dir clean run test) only for serial or parallel version add "serial" or "parallel" respectively after make.
Example:
`make -s serial run [NUM_PROCESSES=NUM_PROCESSES] [FILENAME=path/to/inputfile[:input/in.txt]]`

## Notes

Results can be found in the `measures` directory, divided by problem size and gcc optimization option.

The speedup curves are generated taking the relative serial execution as reference.