// Exercise 6: the function is correct; you write the tests.
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int passes = 0;
int failures = 0;
void check(bool condition, const std::string& message) {
    std::cout << (condition ? "  PASS  " : "  FAIL  ") << message << '\n';
    if (condition) ++passes; else ++failures;
}

// Given and correct: where a staged copy of a project file is stored.
fs::path stageFile(const fs::path& root, const std::string& name) {
    return root / ".minigit" / "stage" / name;
}

int main() {
    const fs::path root = "course/repo";

    check(stageFile(root, "notes.txt") == root / ".minigit" / "stage" / "notes.txt",
          "a top-level file is stored in stage");
    check(stageFile(root, "docs/notes.txt") ==
              root / ".minigit" / "stage" / "docs" / "notes.txt",
          "a nested file keeps its sub-folder");
    check(stageFile(root, "docs/notes.txt").filename() == "notes.txt",
          "the staged path keeps the original filename");

    if (passes < 3) {
        std::cout << "  FAIL  write at least three passing checks (you have " << passes << ")\n";
        ++failures;
    }
    return failures == 0 ? 0 : 1;
}
