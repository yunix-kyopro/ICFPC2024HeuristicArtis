# Overview
The basic approach for Efficiency was:

- Transpile the program in the alien language to JavaScript.
- Execute the JavaScript if possible to obtain the solution.
- If execution is not possible, infer the required processing from the program and provide the answer.

For solving Sudoku and SAT problems, solvers were developed. For other problems, the processing content was inferred using LLM (Language Model) or manually read and answered.

Example of transpiler:
```
[ICPC]
B$ B$ L# L$ v# B. SB%,,/ S}Q/2,$_ IK

[JavaScript]
app(app(lambda(v2 =>lambda(v3 =>v2)),concat(string("Hello"), string(" World!"))),integer(42))
```
The transpiler can be used by ```python3 main.py``` in transpiler folder.


# Files
- transpiler: Code set for the transpiler.
- solver: Code set for the solvers.

# Lightning Round
All Efficiency problems were solved during the Lightning Round.
