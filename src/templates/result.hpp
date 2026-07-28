#pragma once
#include <functional>
#include <variant>
template <typename T, typename E> class Result {
private:
  std::variant<T, E> object;

public:
  [[nodiscard]] bool has_value() const noexcept {
    try {
      return std::holds_alternative<T>(object);
    } catch (...) {
      return false;
    }
  }

  T &value_or(const T &other) const noexcept {
    try {
      return std::get<T>(object);
    } catch (...) {
      return other;
    }
  }

  explicit operator bool() const noexcept { return has_value(); }

  Result() = delete;
  Result(const E &error) : object(error) {}
  Result(E &&error) : object(std::move(error)) {}
  Result(const T &value) : object(value) {}
  Result(T &&value) : object(std::move(value)) {}

  //   Result &operator=(const Error &error) = default;
  //   Result &operator=(Error &&error) = default;
  //   Result &operator=(const T &value) = default;
  //   Result &operator=(T &&value) = default;

  [[nodiscard]] T &value() const noexcept { return std::get<T>(object); }
  [[nodiscard]] E &error() const noexcept { return std::get<E>(object); };
};