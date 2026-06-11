
#include <print>
#include <string>
int main() {
  constexpr std::string_view title = "======== C++20 Feature Set =======";
  const std::string footer(title.size(), '=');

  std::println("{}\n", title);
  std::println("\n\n{}", footer);
}