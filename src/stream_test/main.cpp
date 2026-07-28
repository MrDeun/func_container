#include "../templates/streams.hpp"
#include <algorithm>
#include <fmt/core.h>
#include <iterator>
#include <print>
#include <vector>

template <typename T> size_t get_vector_allocation(const std::vector<T> &vec) {
  return sizeof(decltype(vec.back())) * vec.capacity();
}

int get_sequence_number() {
  static int counter = 0;
  return counter++;
}

int main(int argc, char **argv) {
  std::vector<int> foo(100);
  std::generate(std::begin(foo), std::end(foo), get_sequence_number);
  fmt::println("Allocated memory: {} bytes", get_vector_allocation(foo));
  auto res = stream(std::move(foo))
                 .for_each([](int x) {
                   // std::print("{} ", x);
                 })
                 .map([](int x) { return x + 1; })
                 .filter([](int x) { return x % 5 == 0; })
                 .to_vector();
  fmt::println("");
  stream(res).for_each([](int x) { fmt::print("{} ", x); }).discard();
  fmt::println("\n");
  fmt::println("Allocated memory: {} bytes",
               get_vector_allocation(foo) + get_vector_allocation(res));
  stream(foo).discard();
  fmt::println("Allocated memory: {} bytes",
               get_vector_allocation(foo) + get_vector_allocation(res));
  return 0;
}
