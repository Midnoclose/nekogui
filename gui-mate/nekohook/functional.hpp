
#pragma once

// an extended std lib

#include <vector>
#include <algorithm>
#include <functional>

namespace cat {

// To handle calling of events
template<typename... args>
class FastEvent {
public:
  using FuncPtr = void(*)(args...);
private:
  std::vector<FuncPtr> func_pool;
  bool in_event = false;
  auto find(FuncPtr in) {
    return std::find(this->func_pool.begin(), this->func_pool.end(), in);
  }
public:
  inline bool GetInEvent(){ return in_event; }
  inline void Emit(args... a) {
    in_event = true;
    for (const auto& func : this->func_pool)
      func(a...);
    in_event = false;
  }
  void Listen(FuncPtr in) {
    auto find = this->find(in);
    if (find != this->func_pool.end())
      throw std::runtime_error("Listener already exists");
    this->func_pool.push_back(in);
  }
  void Remove(FuncPtr in) {
    auto find = this->find(in);
    if (find != this->func_pool.end())
      this->func_pool.erase(find);
    else
      throw std::runtime_error("Listener doesnt exist");
  }
};

template<typename... args>
class Event {
public:
  using Func = std::function<args...>;
private:
  std::vector<Func> func_pool;
  bool in_event = false;
  auto find(Func in) {
    return std::find(this->func_pool.begin(), this->func_pool.end(), in);
  }
public:
  inline bool GetInEvent(){ return in_event; }
  inline void Emit(args... a) {
    in_event = true;
    for (const auto& func : this->func_pool)
      func(a...);
    in_event = false;
  }
  void Listen(Func in) {
    auto find = this->find(in);
    if (find != this->func_pool.end())
      throw std::runtime_error("Listener already exists");
    this->func_pool.push_back(in);
  }
  void Remove(Func in) {
    auto find = this->find(in);
    if (find != this->func_pool.end())
      this->func_pool.erase(find);
    else
      throw std::runtime_error("Listener doesnt exist");
  }
};

}
