//
// Created by 19254 on 24-5-31.
//

#ifndef HYGUI_LOGS_H
#define HYGUI_LOGS_H

#include "fmt/format.h"
#include <iostream>
#include <chrono>

namespace HYGUI {

#ifdef _HOST_WINDOWS_
#define LOCALTIME(time_str)                                                          \
  auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
  std::tm tm_info = {0};                                                             \
  localtime_s(&tm_info, &now);                                                       \
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);

#else
#define LOCALTIME(time_str)    \
  auto now = time(nullptr);    \
  struct tm tm_info = {0};     \
  localtime_r(&now, &tm_info); \
  strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);

#endif

#define PrintInfo(fstr, ...)                                                           \
  do {                                                                                 \
    char time_str[32];                                                                 \
    LOCALTIME(time_str);                                                               \
    std::string lstr = "<{}> [{}:{}] ";                                            \
    std::string_view fPath = __FILE__;                                                 \
    fPath = fPath.substr(strlen(PRIOJECT_PATH), fPath.size() - strlen(PRIOJECT_PATH)); \
    std::cout << fmt::format(lstr + std::string(fstr), time_str, fPath, __LINE__, ##__VA_ARGS__)<< std::endl;  \
  } while (0)

#define PrintDebug(fstr, ...)                                                          \
  do {                                                                                 \
    char time_str[32];                                                                 \
    LOCALTIME(time_str);                                                               \
    std::string lstr = "<{}> [{}:{}] ";                                            \
    std::string_view fPath = __FILE__;                                                 \
    fPath = fPath.substr(strlen(PRIOJECT_PATH), fPath.size() - strlen(PRIOJECT_PATH)); \
    std::cout << fmt::format(lstr + std::string(fstr), time_str, fPath, __LINE__, ##__VA_ARGS__)<< std::endl; \
  } while (0)

#define PrintError(fstr, ...)                                                          \
  do {                                                                                 \
    char time_str[32];                                                                 \
    LOCALTIME(time_str);                                                               \
    std::string lstr = "<{}> [{}:{}] ";                                            \
    std::string_view fPath = __FILE__;                                                 \
    fPath = fPath.substr(strlen(PRIOJECT_PATH), fPath.size() - strlen(PRIOJECT_PATH)); \
    std::cerr << fmt::format(lstr + std::string(fstr), time_str, fPath, __LINE__, ##__VA_ARGS__)<< std::endl; \
  } while (0)



}
#endif //HYGUI_LOGS_H
