////
//// Created by 19254 on 24-5-25.
////
//
//#include "HYGUI/HYAsyncQueueProcessor.h"
//
//namespace HYGUI {
//
//template<typename TYPE>
//HYAsyncQueueProcessor<TYPE>::HYAsyncQueueProcessor() {
//  m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(25);
//}
//template<typename TYPE>
//HYAsyncQueueProcessor<TYPE>::HYAsyncQueueProcessor(size_t size) {
//  m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(size);
//};
//
//template<typename TYPE>
//HYAsyncQueueProcessor<TYPE>::HYAsyncQueueProcessor(size_t size, const AsyncQueueProcessCallback &processCallback)
//  : m_process(
//  processCallback) {
//  m_queue = std::make_shared<boost::lockfree::queue<TYPE, boost::lockfree::fixed_sized<false>>>(size);
//};
//
//template<typename TYPE>
//HYAsyncQueueProcessor<TYPE>::~HYAsyncQueueProcessor() {
//  Stop();
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::Start() {
//  Start(nullptr);
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::Start(const AsyncQueueProcessCallback &processCallback) {
//  m_running = true;
//  m_process = processCallback;
//  m_thread = std::thread([this]() {
//
//    while (m_running) {
//      std::unique_lock<std::mutex> lock(m_queue_mutex);
//      m_data_available_cv.wait(lock, [&] {
//        return !m_queue->empty();
//      });
//
//      TYPE data;
//      while (m_queue->pop(data)) {
//        // 处理数据
//        if (m_process) {
//          m_process(this, data);
//        }
//      }
//
//    }
//
//  });
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::Stop() {
//  m_running = false;
//  m_data_available_cv.notify_all();
//  m_thread.join();
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::Push(TYPE &data) {
//  {
//    std::lock_guard<std::mutex> lock(m_queue_mutex);
//    m_queue->push(data);
//  }
//  m_data_available_cv.notify_one();
//}
//
//template<typename TYPE>
//bool HYAsyncQueueProcessor<TYPE>::Empty() {
//  return m_queue->empty();
//}
//
//template<typename TYPE>
//size_t HYAsyncQueueProcessor<TYPE>::Size() {
//  return m_queue->size();
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::Clear() {
//  TYPE data;
//  while (m_queue->pop(data)) {
//  }
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::SetProcessCallback(const AsyncQueueProcessCallback &processCallback) {
//  m_process = processCallback;
//}
//
//template<typename TYPE>
//void HYAsyncQueueProcessor<TYPE>::SetProcessCallback(const AsyncQueueProcessCallback &&processCallback) {
//  m_process = std::move(processCallback);
//}
//
//template<typename TYPE>
//bool HYAsyncQueueProcessor<TYPE>::IsRunning() {
//  return m_running;
//}
//
//} // AC::Algorithm