//
// Created by 回忆 on 24-6-10.
//
#import "HYGUI/Mouse.h"
#import <Cocoa/Cocoa.h>

namespace HYGUI {

HYPoint HYMouseGetPosition() {
  NSPoint mouseLocation = NSEvent.mouseLocation;
  return {static_cast<int>(mouseLocation.x), static_cast<int>(mouseLocation.y)};
}

}