//
// Created by 回忆 on 24-6-10.
//
#include "HYGUI/Window.h"
#include "PrivateDefinition.h"
#ifdef _HOST_APPLE_

#include <Cocoa/Cocoa.h>
#endif

namespace HYGUI {

HYWindowHandel HYWindowCreate(HYWindowHandel parent, const HYString &title, int x, int y, int width, int height) {
  NSRect frame = NSMakeRect(x, y, width, height);

  // 获取主屏幕来计算默认居中位置
  NSScreen *mainScreen = [NSScreen mainScreen];
  NSRect screenFrame = [mainScreen frame];
  if (x == WINDOWCREATEPOINT_USEDEFAULT) {
    frame.origin.x = (screenFrame.size.width - width) / 2;
  }
  if (y == WINDOWCREATEPOINT_USEDEFAULT) {
    frame.origin.y = (screenFrame.size.height - height) / 2;
  }

  // 创建NSWindow实例
  NSWindow *nsWindow = [[NSWindow alloc] initWithContentRect:frame
                                                   styleMask:NSWindowStyleMaskTitled
                                                             | NSWindowStyleMaskClosable
                                                             | NSWindowStyleMaskMiniaturizable
                                                             | NSWindowStyleMaskResizable
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
  nsWindow.title = [NSString stringWithUTF8String:title.toStdStringView().data()];
  nsWindow.backgroundColor = [NSColor colorWithCalibratedWhite:1.0 alpha:1.0]; // 默认背景色全白，透明度1.0

  auto window = new HYWindow;
  window->Handle = (__bridge void *) (nsWindow);
  window->Width = width;
  window->Height = height;
  window->X = frame.origin.x;
  window->Y = frame.origin.y;
  window->ClientRect = {0, 0, width, height};

  // macOS没有全局的窗口列表管理方式，你可能需要在你的应用内部维护这个表
  g_app.WindowsTable.insert(window);

  return window;
}

void HYWindowDestroy(HYWindowHandel wnd) {
  if (!wnd) {
    return;
  }

  auto nsWindow = (__bridge NSWindow *) wnd->Handle;
  [nsWindow close];

  // 清理资源
  if (wnd->Surface) {
    wnd->Surface->unref();
  }
  //释放DC
  if (wnd->WindowCanvasTarget) {
    //DeleteDC((HDC) wnd->WindowCanvasTarget);
  }
  if (wnd->WindowLayeredCanvas) {
    //DeleteDC((HDC) wnd->WindowLayeredCanvas);
  }
  if (wnd->CustomBmp) {
    //DeleteObject((HBITMAP) wnd->CustomBmp);
  }
  delete wnd;

  if (g_app.WindowsTable.find(wnd) != g_app.WindowsTable.end()) {
    g_app.WindowsTable.erase(wnd);
  }
}

bool HYWindowShow(HYWindowHandel wnd) {
  NSWindow *nsWindow = (__bridge NSWindow *) (wnd->Handle);
  if (nsWindow) {
    [nsWindow makeKeyAndOrderFront:nil];
    return true;
  }
  return false;
}

uint32_t
HYWindowMessageLoop(HYWindowHandel
                    wnd) {
  while (true) {
    sleep(1000);
  }
  return 0;
}

}
