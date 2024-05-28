//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_FILES_H
#define HYGUI_FILES_H

#include <filesystem>
#include <fstream>
#include <istream>

namespace HYGUI {

bool HY_ReadFile(const wchar_t *path, std::vector<char> *result);

}

#endif //HYGUI_FILES_H
