

#include <cmath>
#include <cstdint>
#include <functional>
#include <memory>
#include <print>
#include <string_view>
#include <unordered_map>
#include <utility>

#define STR(char_ptr) std::string(char_ptr)

void copy_elision() {
  std::function<std::unique_ptr<int>()> factory = []() {
    return std::make_unique<int>(10);
  };

  // This widget will never be moved/copied
  auto widget = factory();

  auto moves_widget = std::move(widget);
  //   auto copy_widget = widget; // explilictly deleted
}

void const_support() {
  // All methods and function in stdlib if they can be constexpr, they will be
}

void const_lambdas() {
  // Can be used in constexpr contextes aka. comp time
  constexpr auto lamb = []() {};
}

void string_views() {
  const std::string hello = "hello";
  std::string_view hello_view = hello;
  std::println("Hello strings location = {:X}",
               reinterpret_cast<std::uintptr_t>(hello.data()));
  std::println("Hello string view location = {:X}",
               reinterpret_cast<std::uintptr_t>(hello_view.data()));

  std::println("Both strings {} allocated in same location",
               hello.data() == hello_view.data() ? "ARE" : "ARE NOT");
}

void template_deduction() {
  std::array words = {"All",   "These", "Words", "Are",   "In",    "The",
                      "Array", "With",  "No",    "Types", "Typed", "Out!"};
  for (const auto &word : words) {
    std::print("{} ", word);
  }
  std::println();
}

template <typename... T> auto add(const T &...para) { return (para + ...); }

constexpr void fold_expression() {
  std::println(
      "All of these were done in comptime using one template function!:");
  std::println("Add with int -> add(1, 2, 4, 5, 6, 7, 8) = {}",
               add(1, 2, 4, 5, 6, 7, 8));
  std::println("Add with floats -> add(0.0,4.0,8.0,12.0,16.0) = {}",
               add(0.0, 4.0, 8.0, 12.0, 16.0));
  std::println("Add with strings -> add(\"hello \",\"comp\",\"time!\")  = {}",
               add(STR("hello "), STR("comp"), STR("time!")));
}

void structured_binding() {
  std::pair<size_t, float> web{1, 0.0};

  auto [int_, float_] = web;
  std::println("Left type of the pair '{}' - Right type of the pair '{}'",
               typeid(int_).name(), typeid(float_).name());
}

void if_init_express() {
  std::pair<size_t, float> web{1, 0.0};
  if (int loop_count = -10; loop_count < 0) {
    std::println("Loop count is smaller than 0!");
  }
}

int main() {

  copy_elision();
  const_support();
  const_lambdas();
  string_views();
  template_deduction();
  fold_expression();
  structured_binding();
  if_init_express();

  return 0;
}