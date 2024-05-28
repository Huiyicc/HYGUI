//
// Created by 19254 on 24-5-28.
//

#ifndef HYGUI_HYGUI_H
#define HYGUI_HYGUI_H

#ifdef _HOST_WINDOWS_
#include <windows.h>
#else
#error "Unsupported platform"
#endif

#include <HYGUI/Helper/Data.h>
#include <HYGUI/Helper/Encode.h>
#include <HYGUI/Helper/Memory.h>
#include <HYGUI/Helper/Files.h>
#include <HYGUI/Helper/Thread.h>
#include <HYGUI/Application.h>
#include <HYGUI/Image.h>
#include <HYGUI/Window.h>

#include <cstdint>

namespace HYGUI {

typedef struct ICONDIRENTRY
{
  uint8_t bWidth;         // Width, in pixels, of the image
  uint8_t bHeight;        // Height, in pixels, of the image
  uint8_t bColorCount;    // Number of colors in image (0 if >=8bpp)
  uint8_t bReserved;      // Reserved ( must be 0)
  uint16_t wPlanes;        // Color Planes
  uint16_t wBitCount;      // Bits per pixel
  uint32_t dwBytesInRes;  // How many bytes in this resource?
  uint32_t dwImageOffset; // Where in the file is this image?
} ICONDIRENTRY, *LPICONDIRENTRY;

typedef struct ICONDIR
{
  uint16_t idReserved;           // Reserved (must be 0)
  uint16_t idType;               // Resource Type (1 for icons)
  uint16_t idCount;              // How many images?
  ICONDIRENTRY idEntries[1]; // An entry for each image (idCount of 'em)
} ICONDIR, *LPICONDIR;

}

#endif //HYGUI_HYGUI_H
