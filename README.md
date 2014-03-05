# Sudoku Solvers

This is a collection of Sudoku solvers written in various languages.  Right now, there is only a C version and a Python version, but I intend to keep adding to it.  I plan to do the next one in a functional language, probably Common Lisp.  Who knows if it'll happen.  We'll see.

About Sudoku: Solving a Sudoku puzzle *can* be an NP-Complete problem.  That is, it is possible to construct an unsolved puzzle that has one unique solution, but the only way to find the solution is brute force.  These would be the "hard" or "evil" puzzles you might find on the Internet.  But even though Sudoku is NP-Complete, a typical 9x9 puzzle is small enough that a brute force algorithm takes half a second or less.

## Compiling and Running

I've provided a sample board, `sampleboard.txt` to demonstrate my solvers.  You can either enter a board at the command line, as per the same format in sampleboard.txt, or you can pass a board saved to a file to the solver with the `<` operator.  If you use the sample board, you should see output like this:
```
+===+===+===+===+===+===+===+===+===+
| 9 : 1 :   | 3 :   : 5 |   : 2 :   |
+---+---+---+---+---+---+---+---+---+
|   :   :   | 9 : 1 : 7 |   :   :   |
+---+---+---+---+---+---+---+---+---+
|   : 7 : 3 | 8 :   :   |   :   : 6 |
+===+===+===+===+===+===+===+===+===+
|   : 5 : 6 |   :   : 8 |   : 7 :   |
+---+---+---+---+---+---+---+---+---+
| 8 :   :   |   : 5 :   |   :   : 1 |
+---+---+---+---+---+---+---+---+---+
|   : 9 :   | 4 :   :   | 6 : 8 :   |
+===+===+===+===+===+===+===+===+===+
| 7 :   :   |   :   : 9 | 8 : 5 :   |
+---+---+---+---+---+---+---+---+---+
|   :   :   | 7 : 4 : 1 |   :   :   |
+---+---+---+---+---+---+---+---+---+
|   : 4 :   | 5 :   : 6 |   : 1 : 3 |
+===+===+===+===+===+===+===+===+===+
+===+===+===+===+===+===+===+===+===+
| 9 : 1 : 8 | 3 : 6 : 5 | 4 : 2 : 7 |
+---+---+---+---+---+---+---+---+---+
| 6 : 2 : 4 | 9 : 1 : 7 | 5 : 3 : 8 |
+---+---+---+---+---+---+---+---+---+
| 5 : 7 : 3 | 8 : 2 : 4 | 1 : 9 : 6 |
+===+===+===+===+===+===+===+===+===+
| 4 : 5 : 6 | 1 : 9 : 8 | 3 : 7 : 2 |
+---+---+---+---+---+---+---+---+---+
| 8 : 3 : 7 | 6 : 5 : 2 | 9 : 4 : 1 |
+---+---+---+---+---+---+---+---+---+
| 1 : 9 : 2 | 4 : 7 : 3 | 6 : 8 : 5 |
+===+===+===+===+===+===+===+===+===+
| 7 : 6 : 1 | 2 : 3 : 9 | 8 : 5 : 4 |
+---+---+---+---+---+---+---+---+---+
| 3 : 8 : 5 | 7 : 4 : 1 | 2 : 6 : 9 |
+---+---+---+---+---+---+---+---+---+
| 2 : 4 : 9 | 5 : 8 : 6 | 7 : 1 : 3 |
+===+===+===+===+===+===+===+===+===+```

More specific compiling and running instructions below.

### Python - SuperSudoku.py
Simply run `python SuperSudoku.py` or `python SuperSudoku.py < sampleboard.txt`.  Easy cheesey. `SuperSudoku.py` also has some functions to generate hard/evil/NP-Complete Sudoku puzzles, so check that out.

### C - Sudoku.c
First, compile with `gcc Sudoku.c`.  Then run the output file: `./a.out` or `./a.out < sampleboard.txt` for the sample board.
