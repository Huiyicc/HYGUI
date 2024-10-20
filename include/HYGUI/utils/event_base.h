//
// Created by 19254 on 24-10-20.
//

#ifndef HYGUI_EVENT_BASE_H
#define HYGUI_EVENT_BASE_H

#include <functional>

namespace HYGUI {

template<typename T>
struct has_void_return;

template<typename Ret, typename... Args>
struct has_void_return<std::function<Ret(Args...)>> {
  static constexpr bool value = std::is_void_v<Ret>;
};

template<typename CALLTYPE, typename CALLTYPEPTR>
class HYEventRegistry {
public:
  void connect(const CALLTYPEPTR &callFunc) {
    callbacks.emplace_back(callFunc);
  }
  void connect(const CALLTYPE &callFunc) {
    callbacks.emplace_back(callFunc);
  }

  HYEventRegistry& operator+=(const CALLTYPE &callFunc) {
    connect(callFunc);
    return *this;
  }
  HYEventRegistry& operator+=(const CALLTYPEPTR &callFunc) {
    connect(callFunc);
    return *this;
  }

  HYEventRegistry& operator=(const CALLTYPE &callFunc) {
    callbacks.clear();
    callbacks.emplace_back(callFunc);
    return *this;
  }
  HYEventRegistry& operator=(const CALLTYPEPTR &callFunc) {
    callbacks.clear();
    callbacks.emplace_back(callFunc);
    return *this;
  }

#ifdef _HYGUI_MODULE_
public:
#else
private:
#endif

  template<typename... Args>
  int operator()(Args &&...args) {
    for (auto &cb: callbacks) {
      if constexpr (has_void_return<decltype(priv)>::value) {
        // 无返回值
        cb(std::forward<Args>(args)...);
      } else {
        // 有返回值
        auto result = cb(std::forward<Args>(args)...);
        if (result != 0) {
          return result;
        }
      }
    }
    return 0;
  }

private:
  bool return_type_has_void() {
    // 萃取返回值类型
    return has_void_return<decltype(priv)>::value;
  }
  CALLTYPE priv;
  std::vector<CALLTYPE> callbacks;
};

}

#endif//HYGUI_EVENT_BASE_H
