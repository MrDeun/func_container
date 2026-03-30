#include "foo.h"
#include <algorithm>
#include <print>
#include <string>
#include <vector>

int get_sequence_number() {
  static int counter = 0;
  return counter++;
}

int main(int argc, char **argv) {
  std::vector<int> foo;
  foo.resize(500);
  std::generate(foo.begin(), foo.end(), get_sequence_number);
  std::vector<int> copy_foo = foo;
  auto res = stream(std::move(foo))
                 .forEach([](int x) { std::print("{}\t", x); })
                 .map([](int x) { return x + 1; })
                 .filter([](int x) { return x % 2 == 0; })
                 .toVector();
  std::println();
  for (size_t i = 0; i < res.size(); i++) {
    std::string moved_vector_status = "";
    try {
      moved_vector_status = std::to_string(foo.at(i));
    } catch (std::exception err) {
      moved_vector_status = "No value";
    }
    std::println("New Vector[{0}] = {1}\t Moved Vector[{0}] = {2}\tCopied "
                 "Vector[{0}] = {3}",
                 i, res.at(i), moved_vector_status, copy_foo.at(i));
  }
  return 0;
}
