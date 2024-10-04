//
// Created by 回忆 on 24-10-4.
//

#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <HYGUI/HYTypeDef.h>
#include <set>
#include <functional>

namespace HYGUI {

template<typename CALLFUNC, typename Enable = void>
class HYEventRegistry;

// 函数指针版本
template<typename Ret, typename... Args>
class HYEventRegistry<Ret(*)(Args...)> {
public:
  void connect(Ret(*callFunc)(Args...)) {
    callbacks.insert(callFunc);
  }

  void operator()(Args... args) {
    for (auto& cb : callbacks) {
      cb(args...);
    }
  }

private:
  std::set<Ret(*)(Args...)> callbacks;
};

// std::function 版本
template<typename Ret, typename... Args>
class HYEventRegistry<std::function<Ret(Args...)>> {
public:
  void connect(const std::function<Ret(Args...)>& callFunc) {
    callbacks.insert(callFunc);
  }

  void operator()(Args... args) {
    for (auto& cb : callbacks) {
      cb(args...);
    }
  }

private:
  std::set<std::function<Ret(Args...)>> callbacks;
};


class HYEventBase : public HYClassBase {
public:

};

}

#endif //EVENTBASE_H
