# HW9 practice answers

## Exercise 1 - Predict the output

Draft predictions recorded before running `ex1_predictions.cpp`:

| Line | Prediction |
| --- | --- |
| a | `repo/.minigit/HEAD` |
| b | `/HEAD` |
| c | `notes.txt` |
| d | `docs` |
| e | `1` |
| f | `.txt` |

These are predictions for Linux path rules. The verification program is run
separately from the four CMake exercises.

Actual output from the verification program on macOS (matching the expected
Linux results for these inputs):

```text
a: repo/.minigit/HEAD
b: /HEAD
c: notes.txt
d: docs
e: 1
f: .txt
```

The recorded draft predictions all matched this run. The important case is b:
a rooted right-hand path replaces the relative path on its left. This is why
`"HEAD"` and `"/HEAD"` are not interchangeable.
