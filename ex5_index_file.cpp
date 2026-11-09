// Exercise 5: add a new path function by following an existing one.
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int failures = 0;
void check(bool condition, const std::string& message) {
    std::cout << (condition ? "  PASS  " : "  FAIL  ") << message << '\n';
    if (!condition) ++failures;
}

// Given (from HW8).
fs::path metadataDirectory(const fs::path& root) {
    return root / ".minigit";
}

// Keep the metadata-directory name in one place.
fs::path indexFile(const fs::path& root) {
    return metadataDirectory(root) / "index.txt";
}

int main() {
    const fs::path root = "course/repo";
    check(indexFile(root) == root / ".minigit" / "index.txt", "index file for course/repo");
    check(indexFile(root).filename() == "index.txt", "file name is index.txt");
    check(indexFile(root).parent_path() == metadataDirectory(root), "index file is inside .minigit");

    const fs::path nestedRoot = fs::path("course") / "team" / "repo";
    check(indexFile(nestedRoot) == nestedRoot / ".minigit" / "index.txt",
          "index file for a nested repository root");

    return failures == 0 ? 0 : 1;
}
