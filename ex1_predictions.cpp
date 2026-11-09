#include <filesystem>
#include <iostream>

int main() {
    using std::filesystem::path;
    std::cout << "a: " << (path("repo") / ".minigit" / "HEAD").generic_string() << '\n';
    std::cout << "b: " << (path("repo") / "/HEAD").generic_string() << '\n';
    std::cout << "c: " << path("docs/notes.txt").filename().string() << '\n';
    std::cout << "d: " << path("docs/notes.txt").parent_path().string() << '\n';
    std::cout << "e: " << path("notes.txt").parent_path().empty() << '\n';
    std::cout << "f: " << path("notes.txt").extension().string() << '\n';
}
