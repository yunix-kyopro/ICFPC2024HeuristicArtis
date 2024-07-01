# Solutions for lambdaman

## Overview

In Lightning Round, we developed TSP solver using simulated annealing. See `lightning_sa/`.

We developed the transpiler from javascript to ICFP Language and use it to solve complex problems. Javascript solution files are stored in `out_js/`.

You can find some other tools to help solving problems.

- In Lightning Round, we used string compression tools. It compresses `URDL` strings to base-94 integers with decoder program written in ICFP Language. See `scropts/string_compressor.py`.
- We developed the simulator for debugging. See `simulator/`.
- We also developed parameter search programs to find optimal parameters for solutions. See `param_search/`.

## JS to ICFP Language transpiler

Here is the JS to ICFP Language transpiler in `out_js/`. You can write lambda expressions easily and they are transpiled into ICFP Language.

If you want to evaluate lambda, execute `node <javascript_file>` and you will see evaluation result. If you want to transpile a JS code into ICFP Language, execute `node <javascript_file> --submit` and you will see transpiled ICFP Language code and its length.
