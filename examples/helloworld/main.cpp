//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>


int main() {
  std::vector<char> data;
  HYGUI::HY_ReadFile(L"res/cursor.cur", &data);
  auto hCursor = HYGUI::HY_ImageLoadFromMemory(data.data(), data.size(), IMAGE_CURSOR, 1);
  HYGUI::HY_ReadFile(L"res/Default.ext", &data);


  return 0;
}