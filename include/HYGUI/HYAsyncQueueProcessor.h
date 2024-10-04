//
// Created by 19254 on 24-5-25.
//

#ifndef HYGUI_ASYNCQUEUEPROCESSOR_H
#define HYGUI_ASYNCQUEUEPROCESSOR_H

#include <boost/lockfree/queue.hpp>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <coroutine>

namespace HYGUI {

/**
 * @brief 异步队列处理器
 */
template<typename TYPE>
class HYAsyncQueueProcessor {
public:
  typedef std::function<int(HYAsyncQueueProcessor<TYPE> *, TYPE &)> AsyncQueueProcessCallback;

private:
  std::shared_ptr<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>> m_queue = nullptr;
  std::jthread m_thread;
  std::mutex m_queue_mutex;
  std::condition_variable m_data_available_cv;
  AsyncQueueProcessCallback m_process;
  bool m_running = false;

public:
  /**
   * @brief 构造函数
   * @param size 队列初始大小
   */
  explicit HYAsyncQueueProcessor(size_t size) {
    m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(size);
  };

  /**
   * @brief 构造函数
   * 队列初始大小默认25
   */
  explicit HYAsyncQueueProcessor() {
    m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(25);
  };

  /**
   * @brief 构造函数
   * @param size 队列大小
   * @param processCallback 处理回调
   */
  explicit HYAsyncQueueProcessor(size_t size, const AsyncQueueProcessCallback &processCallback)
      : m_process(processCallback) {
    m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(size);
  };

  /**
   * @brief 析构函数
   */
  ~HYAsyncQueueProcessor() {
    Stop();
  };

  /**
   * @brief 启动队列
   */
  void Start() {
    Start(nullptr);
  };

  /**
   * @brief 启动队列
   * @param processCallback 处理回调
   */
  void Start(const AsyncQueueProcessCallback &processCallback) {
    m_running = true;
    if (processCallback != nullptr) {
      m_process = processCallback;
    }
    m_thread = std::jthread([this]() {
      while (m_running) {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        m_data_available_cv.wait(lock, [&] {
          return !m_queue->empty();
        });

        TYPE data;
        while (m_queue->pop(data)) {
          // 处理数据
          if (m_process) {
            m_process(this, data);
          }
        }
      }
    });
  };

  /**
   * @brief 停止队列
   */
  void Stop() {
    std::lock_guard<std::mutex> lock(m_queue_mutex);
    m_running = false;
    m_data_available_cv.notify_all();
//    if (m_thread.joinable()) {
//      m_thread.join();
//    }
  };

  /**
   * @brief 投递数据
   * @param data 数据
   */
  void Push(const TYPE &data) {
    {
      std::lock_guard<std::mutex> lock(m_queue_mutex);
      if (m_running) {
        m_queue->push(data);
      }
    }
    if (m_running) {
      m_data_available_cv.notify_one();
    }
  };
  void Push(const TYPE &&data) {
    {

      std::lock_guard<std::mutex> lock(m_queue_mutex);
      if (m_running) {
        m_queue->push(data);
      }
    }
    if (m_running) {
      m_data_available_cv.notify_one();
    }
  };

  /**
   * @brief 是否为空
   */
  bool Empty() {
    return m_queue->empty();
  };

  /**
   * @brief 获取队列大小
   */
  size_t Size() {
    return m_queue->size();
  };

  /**
   * @brief 清空队列
   */
  void Clear() {
    TYPE data;
    while (m_queue->pop(data)) {
    }
  };

  /**
   * @brief 设置处理回调
   * @param processCallback 处理回调
   */
  void SetProcessCallback(const AsyncQueueProcessCallback &processCallback) {
    m_process = processCallback;
  };

  /**
   * @brief 设置处理回调
   * @param processCallback 处理回调
   */
  void SetProcessCallback(const AsyncQueueProcessCallback &&processCallback) {
    m_process = std::move(processCallback);
  };

  /**
   * @brief 是否正在运行
   */
  bool IsRunning() {
    return m_running;
  };
};

}// namespace HYGUI

#endif // HYGUI_ASYNCQUEUEPROCESSOR_H
