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
