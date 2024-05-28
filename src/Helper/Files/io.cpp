//
// Created by 19254 on 24-5-28.
//
#include <HYGUI/Helper/Files.h>
#include <filesystem>

namespace HYGUI {

bool HY_ReadFile(const wchar_t *path, std::vector<char> *result) {
  std::filesystem::path p(path);
  if (!std::filesystem::exists(p)) {
    return false;
  }
  std::ifstream file(path, std::ios::binary);
  if (!file.is_open()) {
    return false;
  }
  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);
  result->resize(size);
  file.read(result->data(), size);
  file.close();
  return true;
};

}