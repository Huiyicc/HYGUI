//
// Created by 19254 on 24-5-28.
//
#include <PrivateDefinition.h>
#include <HYGUI/HYGUI.h>
#include <HYGUI/Image.h>

namespace HYGUI {

HIMAGE HY_ImageLoadFromMemory(void *lpData, size_t dwLen, int uType, int nIndex) {
  #ifdef _HOST_WINDOWS_
  LPVOID ret = 0;
  if (!IsBadReadPtr(lpData, dwLen))
  {
    LPVOID hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwLen);
    if (hMem)
    {
      LPVOID lpMem = GlobalLock(hMem);
      if (lpMem)
      {
        RtlMoveMemory(lpMem, lpData, dwLen);
        GlobalUnlock(hMem);
        if (uType == IMAGE_ICON || uType == IMAGE_CURSOR)
        {
          if (nIndex == 0)
            nIndex = 1;
          WORD s = ((ICONDIR *)lpData)->idCount;
          if (s >= nIndex)
          {
            short type = ((ICONDIR *)lpData)->idType;
            BOOL bIcon = (type == IMAGE_ICON);
            LPVOID offset = (LPVOID)((size_t)lpData + 6 + (nIndex - 1) * sizeof(ICONDIRENTRY));
            LPVOID tmp = lpMem;
            if (!bIcon)
            {
              __set_short(lpMem, 0, ((ICONDIRENTRY *)offset)->wBitCount);
              tmp = (LPVOID)((size_t)tmp + 4);
            }
            RtlMoveMemory(tmp, (LPVOID)((size_t)lpData + ((ICONDIRENTRY *)offset)->dwImageOffset), ((ICONDIRENTRY *)offset)->dwBytesInRes);
            CHAR b1 = ((ICONDIRENTRY *)offset)->bWidth;
            CHAR b2 = ((ICONDIRENTRY *)offset)->bHeight;
            HICON hicon = CreateIconFromResourceEx((PBYTE)lpMem, ((ICONDIRENTRY *)offset)->dwBytesInRes, bIcon, 196608, b1, b2, 0);
            ret = CopyImage(hicon, uType, 0, 0, 4);
          }
        }
        else
        {
          LPSTREAM lpStream;
          if (CreateStreamOnHGlobal(hMem, FALSE, &lpStream))
          {
            LPVOID lpObj = nullptr;
            if (OleLoadPicture(lpStream, dwLen, TRUE, IID_IPicture, &lpObj) == 0)
            {
              intptr_t hImg = 0;
              ((IPicture *)lpObj)->get_Handle((OLE_HANDLE*)&hImg);
              SHORT objType = 0;
              ((IPicture *)lpObj)->get_Type(&objType);
              if (objType == uType)
              {
                ret = CopyImage((HANDLE)hImg, uType, 0, 0, 4);
              }
              ((IPicture *)lpObj)->Release();
            }
            lpStream->Release();
          }
        }
      }
      GlobalFree(hMem);
    }
  }
  return ret;
  #else
  #error "Unsupported platform"
  #endif
  return nullptr;
};

}