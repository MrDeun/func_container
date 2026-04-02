#pragma once

#include <algorithm>
#include <exception>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

template <typename T> class stream {
private:
  std::vector<T> items;

public:
  stream() = delete;
  stream(std::vector<T> &&_items) : items(std::move(_items)) {
    _items.shrink_to_fit();
  }
  stream(const std::vector<T> &_items) : items(_items) {}
  stream &filter(std::function<bool(const T &b)> compare) {
    items.erase(std::remove_if(items.begin(), items.end(),
                               [&](const T &val) { return !compare(val); }),
                items.end());
    return *this;
  }
  stream &map(std::function<T(const T &b)> map_func) {
    for (auto &item : items) {
      item = map_func(item);
    }
    return *this;
  }
  stream &forEach(std::function<void(const T &b)> map_func) {
    for (auto &t : items) {
      map_func(t);
    }
    return *this;
  }
  std::optional<T> findFirst() const {
    try {
      return std::optional(items.at(0));
    } catch (std::exception e) {
      return std::nullopt;
    }
  }
  void discard() {
    items.resize(0);
    return;
  }
  std::vector<T> toVector() {
    items.shrink_to_fit();
    return std::move(items);
  }
  static stream<T> fromVector(const std::vector<T> &vec) {
    return stream<T>(vec);
  }
  static stream<T> fromVector(std::vector<T> &&vec) {
    return stream<T>(std::move(vec));
  }
};

template <typename T> stream(std::vector<T>) -> stream<T>;
