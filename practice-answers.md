# HW9 practice answers

## Exercise 1 - Predict the output

Predictions recorded before running `ex1_predictions.cpp`:

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

The recorded predictions all matched this run. The important case is b:
a rooted right-hand path replaces the relative path on its left. This is why
`"HEAD"` and `"/HEAD"` are not interchangeable.


## Exercise 2 - Keep the newlines

`std::getline` removes the newline delimiter. Adding just `line` to `text`
therefore changes `"a\nb\n"` to `"ab"`. Adding a newline after every line would
also change a file that originally had no final newline. Read the characters
as they are instead:

```cpp
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

std::string readAll(const std::filesystem::path& file) {
    std::ifstream input(file, std::ios::binary);
    if (!input) {
        throw std::runtime_error("Cannot open file: " + file.string());
    }

    std::string text;
    char character;
    while (input.get(character)) {
        text += character;
    }
    if (input.bad() || !input.eof()) {
        throw std::runtime_error("Cannot read file: " + file.string());
    }
    return text;
}
```

Binary mode also prevents Windows newline translation, so the function keeps
all bytes, including spaces, blank lines, and the final newline if present.


## Exercise 3 - Fix the path joins

The first function turns the root into a string and manually adds a separator.
Use the path `/` operator to join path parts instead. The second function adds
`"/HEAD"`, which is rooted, so it loses the intended project-directory prefix.
Use the relative part `"HEAD"` and reuse `metadataDirectory`:

```cpp
std::filesystem::path metadataDirectory(const std::filesystem::path& root) {
    return root / ".minigit";
}

std::filesystem::path headFile(const std::filesystem::path& root) {
    return metadataDirectory(root) / "HEAD";
}
```

One detail: the first original expression is not guaranteed to fail on Windows,
because Windows paths can accept forward slashes. Using path joins is still
clearer and avoids building paths by hand. Compare path values in tests rather
than depending on how their separators print.


## Exercise 4 - Fill in the blanks

1. `!file.parent_path().empty()`
2. `create_directories`
3. `!output`
4. `static_cast<bool>(output)`

```cpp
bool save(const std::filesystem::path& file, const std::string& text) {
    if (!file.parent_path().empty()) {
        std::filesystem::create_directories(file.parent_path());
    }
    std::ofstream output(file);
    if (!output) {
        return false;
    }
    output << text;
    return static_cast<bool>(output);
}
```

A bare filename has no parent directory, so there is nothing to create.
`create_directories` creates all missing parents. `!output` checks whether
opening failed, and the final conversion checks the stream after writing.
This completes the supplied skeleton; a directory-creation error can still
throw, and a production writer should also check flushing/closing failures.


## Exercise 5 - Add indexFile

`indexFile` returns `metadataDirectory(root) / "index.txt"`. The extra check
uses `course/team/repo`, so the function is not tied to one root. All four
checks pass.


## Exercise 6 - Write the tests

The three checks cover a top-level file, a file inside `docs`, and preservation
of `filename()`. Expected paths are built with `/` and compared as path
values. A failed check increments `failures`, which makes the program return
1 so CTest sees the failure. All three checks pass.


## Exercise 7 - Define RepoLayout

The constructor uses `: root_(root)` to initialize the member. `root()` returns
a const reference to that stored path, `metadataDirectory()` appends
`.minigit`, and `headFile()` reuses it. The supplied class declaration stays
unchanged. Both objects keep their own roots, and all four checks pass.


## Exercise 8 - Throw and catch an error

`readOrThrow` opens the file in binary mode, reads the full buffer, and throws
`std::runtime_error` naming the file if opening or reading fails.
`readOrDefault` calls it in a `try` block, catches the error by const reference,
prints `Sorry: ` plus the message, and returns an empty string. All five
checks pass, including exact newlines and the missing-file case.
