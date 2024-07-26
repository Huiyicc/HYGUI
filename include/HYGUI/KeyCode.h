//
// Created by 19254 on 24-7-17.
//

#ifndef HYGUI_KEYCODE_H
#define HYGUI_KEYCODE_H

#include <cstdint>

namespace HYGUI {

/**
 * @brief 键盘虚拟按键代码
 * 具体值参见 HY_KEY_
 * */
typedef uint32_t HYKeyCode;

/**
 * @brief 未知键
 */
constexpr const HYKeyCode HY_KEY_UNKNOWN = 0x00000000u; /* 0 */

/**
 * @brief 回车键
 */
constexpr const HYKeyCode HY_KEY_RETURN = 0x0000000du; /* '\r' */

/**
 * @brief 退出键
 */
constexpr const HYKeyCode HY_KEY_ESCAPE = 0x0000001bu; /* '\x1B' */

/**
 * @brief 退格键
 */
constexpr const HYKeyCode HY_KEY_BACKSPACE = 0x00000008u; /* '\b' */

/**
 * @brief 制表键
 */
constexpr const HYKeyCode HY_KEY_TAB = 0x00000009u; /* '\t' */

/**
 * @brief 空格键
 */
constexpr const HYKeyCode HY_KEY_SPACE = 0x00000020u; /* ' ' */

/**
 * @brief 感叹号键
 */
constexpr const HYKeyCode HY_KEY_EXCLAIM = 0x00000021u; /* '!' */

/**
 * @brief 双引号键
 */
constexpr const HYKeyCode HY_KEY_DBLAPOSTROPHE = 0x00000022u; /* '"' */

/**
 * @brief 井号键
 */
constexpr const HYKeyCode HY_KEY_HASH = 0x00000023u; /* '#' */

/**
 * @brief 美元符号键
 */
constexpr const HYKeyCode HY_KEY_DOLLAR = 0x00000024u; /* '$' */

/**
 * @brief 百分号键
 */
constexpr const HYKeyCode HY_KEY_PERCENT = 0x00000025u; /* '%' */

/**
 * @brief 和符号键
 */
constexpr const HYKeyCode HY_KEY_AMPERSAND = 0x00000026u; /* '&' */

/**
 * @brief 单引号键
 */
constexpr const HYKeyCode HY_KEY_APOSTROPHE = 0x00000027u; /* '\'' */

/**
 * @brief 左括号键
 */
constexpr const HYKeyCode HY_KEY_LEFTPAREN = 0x00000028u; /* '(' */

/**
 * @brief 右括号键
 */
constexpr const HYKeyCode HY_KEY_RIGHTPAREN = 0x00000029u; /* ')' */

/**
 * @brief 星号键
 */
constexpr const HYKeyCode HY_KEY_ASTERISK = 0x0000002au; /* '*' */

/**
 * @brief 加号键
 */
constexpr const HYKeyCode HY_KEY_PLUS = 0x0000002bu; /* '+' */

/**
 * @brief 逗号键
 */
constexpr const HYKeyCode HY_KEY_COMMA = 0x0000002cu; /* ',' */

/**
 * @brief 减号键
 */
constexpr const HYKeyCode HY_KEY_MINUS = 0x0000002du; /* '-' */

/**
 * @brief 句号键
 */
constexpr const HYKeyCode HY_KEY_PERIOD = 0x0000002eu; /* '.' */

/**
 * @brief 斜杠键
 */
constexpr const HYKeyCode HY_KEY_SLASH = 0x0000002fu; /* '/' */

/**
 * @brief 数字键 0
 */
constexpr const HYKeyCode HY_KEY_0 = 0x00000030u; /* '0' */

/**
 * @brief 数字键 1
 */
constexpr const HYKeyCode HY_KEY_1 = 0x00000031u; /* '1' */

/**
 * @brief 数字键 2
 */
constexpr const HYKeyCode HY_KEY_2 = 0x00000032u; /* '2' */

/**
 * @brief 数字键 3
 */
constexpr const HYKeyCode HY_KEY_3 = 0x00000033u; /* '3' */

/**
 * @brief 数字键 4
 */
constexpr const HYKeyCode HY_KEY_4 = 0x00000034u; /* '4' */

/**
 * @brief 数字键 5
 */
constexpr const HYKeyCode HY_KEY_5 = 0x00000035u; /* '5' */

/**
 * @brief 数字键 6
 */
constexpr const HYKeyCode HY_KEY_6 = 0x00000036u; /* '6' */

/**
 * @brief 数字键 7
 */
constexpr const HYKeyCode HY_KEY_7 = 0x00000037u; /* '7' */

/**
 * @brief 数字键 8
 */
constexpr const HYKeyCode HY_KEY_8 = 0x00000038u; /* '8' */

/**
 * @brief 数字键 9
 */
constexpr const HYKeyCode HY_KEY_9 = 0x00000039u; /* '9' */

/**
 * @brief 冒号键
 */
constexpr const HYKeyCode HY_KEY_COLON = 0x0000003au; /* ':' */

/**
 * @brief 分号键
 */
constexpr const HYKeyCode HY_KEY_SEMICOLON = 0x0000003bu; /* ';' */

/**
 * @brief 小于号键
 */
constexpr const HYKeyCode HY_KEY_LESS = 0x0000003cu; /* '<' */

/**
 * @brief 等号键
 */
constexpr const HYKeyCode HY_KEY_EQUALS = 0x0000003du; /* '=' */

/**
 * @brief 大于号键
 */
constexpr const HYKeyCode HY_KEY_GREATER = 0x0000003eu; /* '>' */

/**
 * @brief 问号键
 */
constexpr const HYKeyCode HY_KEY_QUESTION = 0x0000003fu; /* '?' */

/**
 * @brief @符号键
 */
constexpr const HYKeyCode HY_KEY_AT = 0x00000040u; /* '@' */

/**
 * @brief 左方括号键
 */
constexpr const HYKeyCode HY_KEY_LEFTBRACKET = 0x0000005bu; /* '[' */

/**
 * @brief 反斜杠键
 */
constexpr const HYKeyCode HY_KEY_BACKSLASH = 0x0000005cu; /* '\\' */

/**
 * @brief 右方括号键
 */
constexpr const HYKeyCode HY_KEY_RIGHTBRACKET = 0x0000005du; /* ']' */

/**
 * @brief 脱字符号键
 */
constexpr const HYKeyCode HY_KEY_CARET = 0x0000005eu; /* '^' */

/**
 * @brief 下划线键
 */
constexpr const HYKeyCode HY_KEY_UNDERSCORE = 0x0000005fu; /* '_' */

/**
 * @brief 重音符号键
 */
constexpr const HYKeyCode HY_KEY_GRAVE = 0x00000060u; /* '`' */

/**
 * @brief 键 a
 */
constexpr const HYKeyCode HY_KEY_A = 0x00000061u; /* 'a' */

/**
 * @brief 键 b
 */
constexpr const HYKeyCode HY_KEY_B = 0x00000062u; /* 'b' */

/**
 * @brief 键 c
 */
constexpr const HYKeyCode HY_KEY_C = 0x00000063u; /* 'c' */

/**
 * @brief 键 d
 */
constexpr const HYKeyCode HY_KEY_D = 0x00000064u; /* 'd' */

/**
 * @brief 键 e
 */
constexpr const HYKeyCode HY_KEY_E = 0x00000065u; /* 'e' */

/**
 * @brief 键 f
 */
constexpr const HYKeyCode HY_KEY_F = 0x00000066u; /* 'f' */

/**
 * @brief 键 g
 */
constexpr const HYKeyCode HY_KEY_G = 0x00000067u; /* 'g' */

/**
 * @brief 键 h
 */
constexpr const HYKeyCode HY_KEY_H = 0x00000068u; /* 'h' */

/**
 * @brief 键 i
 */
constexpr const HYKeyCode HY_KEY_I = 0x00000069u; /* 'i' */

/**
 * @brief 键 j
 */
constexpr const HYKeyCode HY_KEY_J = 0x0000006au; /* 'j' */

/**
 * @brief 键 k
 */
constexpr const HYKeyCode HY_KEY_K = 0x0000006bu; /* 'k' */

/**
 * @brief 键 l
 */
constexpr const HYKeyCode HY_KEY_L = 0x0000006cu; /* 'l' */

/**
 * @brief 键 m
 */
constexpr const HYKeyCode HY_KEY_M = 0x0000006du; /* 'm' */

/**
 * @brief 键 n
 */
constexpr const HYKeyCode HY_KEY_N = 0x0000006eu; /* 'n' */

/**
 * @brief 键 o
 */
constexpr const HYKeyCode HY_KEY_O = 0x0000006fu; /* 'o' */

/**
 * @brief 键 p
 */
constexpr const HYKeyCode HY_KEY_P = 0x00000070u; /* 'p' */

/**
 * @brief 键 q
 */
constexpr const HYKeyCode HY_KEY_Q = 0x00000071u; /* 'q' */

/**
 * @brief 键 r
 */
constexpr const HYKeyCode HY_KEY_R = 0x00000072u; /* 'r' */

/**
 * @brief 键 s
 */
constexpr const HYKeyCode HY_KEY_S = 0x00000073u; /* 's' */

/**
 * @brief 键 t
 */
constexpr const HYKeyCode HY_KEY_T = 0x00000074u; /* 't' */

/**
 * @brief 键 u
 */
constexpr const HYKeyCode HY_KEY_U = 0x00000075u; /* 'u' */

/**
 * @brief 键 v
 */
constexpr const HYKeyCode HY_KEY_V = 0x00000076u; /* 'v' */

/**
 * @brief 键 w
 */
constexpr const HYKeyCode HY_KEY_W = 0x00000077u; /* 'w' */

/**
 * @brief 键 x
 */
constexpr const HYKeyCode HY_KEY_X = 0x00000078u; /* 'x' */

/**
 * @brief 键 y
 */
constexpr const HYKeyCode HY_KEY_Y = 0x00000079u; /* 'y' */

/**
 * @brief 键 z
 */
constexpr const HYKeyCode HY_KEY_Z = 0x0000007au; /* 'z' */

/**
 * @brief 左花括号键
 */
constexpr const HYKeyCode HY_KEY_LEFTBRACE = 0x0000007bu; /* '{' */

/**
 * @brief 竖线键
 */
constexpr const HYKeyCode HY_KEY_PIPE = 0x0000007cu; /* '|' */

/**
 * @brief 右花括号键
 */
constexpr const HYKeyCode HY_KEY_RIGHTBRACE = 0x0000007du; /* '}' */

/**
 * @brief 波浪号键
 */
constexpr const HYKeyCode HY_KEY_TILDE = 0x0000007eu; /* '~' */

/**
 * @brief 删除键
 */
constexpr const HYKeyCode HY_KEY_DELETE = 0x0000007fu; /* '\x7F' */

/**
 * @brief 加减号键
 */
constexpr const HYKeyCode HY_KEY_PLUSMINUS = 0x000000b1u; /* '±' */

/**
 * @brief 大写锁定键
 */
constexpr const HYKeyCode HY_KEY_CAPSLOCK = 0x40000039u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_CAPSLOCK) */

/**
 * @brief F1 功能键
 */
constexpr const HYKeyCode HY_KEY_F1 = 0x4000003au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F1) */

/**
 * @brief F2 功能键
 */
constexpr const HYKeyCode HY_KEY_F2 = 0x4000003bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F2) */

/**
 * @brief F3 功能键
 */
constexpr const HYKeyCode HY_KEY_F3 = 0x4000003cu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F3) */

/**
 * @brief F4 功能键
 */
constexpr const HYKeyCode HY_KEY_F4 = 0x4000003du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F4) */

/**
 * @brief F5 功能键
 */
constexpr const HYKeyCode HY_KEY_F5 = 0x4000003eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F5) */

/**
 * @brief F6 功能键
 */
constexpr const HYKeyCode HY_KEY_F6 = 0x4000003fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F6) */

/**
 * @brief F7 功能键
 */
constexpr const HYKeyCode HY_KEY_F7 = 0x40000040u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F7) */

/**
 * @brief F8 功能键
 */
constexpr const HYKeyCode HY_KEY_F8 = 0x40000041u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F8) */

/**
 * @brief F9 功能键
 */
constexpr const HYKeyCode HY_KEY_F9 = 0x40000042u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F9) */

/**
 * @brief F10 功能键
 */
constexpr const HYKeyCode HY_KEY_F10 = 0x40000043u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F10) */

/**
 * @brief F11 功能键
 */
constexpr const HYKeyCode HY_KEY_F11 = 0x40000044u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F11) */

/**
 * @brief F12 功能键
 */
constexpr const HYKeyCode HY_KEY_F12 = 0x40000045u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F12) */

/**
 * @brief 打印屏幕键
 */
constexpr const HYKeyCode HY_KEY_PRINTSCREEN = 0x40000046u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PRINTSCREEN) */

/**
 * @brief 滚动锁定键
 */
constexpr const HYKeyCode HY_KEY_SCROLLLOCK = 0x40000047u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_SCROLLLOCK) */

/**
 * @brief 暂停键
 */
constexpr const HYKeyCode HY_KEY_PAUSE = 0x40000048u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PAUSE) */

/**
 * @brief 插入键
 */
constexpr const HYKeyCode HY_KEY_INSERT = 0x40000049u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_INSERT) */

/**
 * @brief 主页键
 */
constexpr const HYKeyCode HY_KEY_HOME = 0x4000004au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_HOME) */

/**
 * @brief 上翻页键
 */
constexpr const HYKeyCode HY_KEY_PAGEUP = 0x4000004bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PAGEUP) */

/**
 * @brief 结束键
 */
constexpr const HYKeyCode HY_KEY_END = 0x4000004du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_END) */

/**
 * @brief 下翻页键
 */
constexpr const HYKeyCode HY_KEY_PAGEDOWN = 0x4000004eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PAGEDOWN) */

/**
 * @brief 向右键
 */
constexpr const HYKeyCode HY_KEY_RIGHT = 0x4000004fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_RIGHT) */

/**
 * @brief 向左键
 */
constexpr const HYKeyCode HY_KEY_LEFT = 0x40000050u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_LEFT) */

/**
 * @brief 向下键
 */
constexpr const HYKeyCode HY_KEY_DOWN = 0x40000051u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_DOWN) */

/**
 * @brief 向上键
 */
constexpr const HYKeyCode HY_KEY_UP = 0x40000052u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_UP) */

/**
 * @brief 数字锁定清除键
 */
constexpr const HYKeyCode HY_KEY_NUMLOCKCLEAR = 0x40000053u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_NUMLOCKCLEAR) */

/**
 * @brief 小键盘除号键
 */
constexpr const HYKeyCode HY_KEY_KP_DIVIDE = 0x40000054u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_DIVIDE) */

/**
 * @brief 小键盘乘号键
 */
constexpr const HYKeyCode HY_KEY_KP_MULTIPLY = 0x40000055u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_MULTIPLY) */

/**
 * @brief 小键盘减号键
 */
constexpr const HYKeyCode HY_KEY_KP_MINUS = 0x40000056u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_MINUS) */

/**
 * @brief 小键盘加号键
 */
constexpr const HYKeyCode HY_KEY_KP_PLUS = 0x40000057u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_PLUS) */

/**
 * @brief 小键盘回车键
 */
constexpr const HYKeyCode HY_KEY_KP_ENTER = 0x40000058u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_ENTER) */

/**
 * @brief 小键盘数字键 1
 */
constexpr const HYKeyCode HY_KEY_KP_1 = 0x40000059u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_1) */

/**
 * @brief 小键盘数字键 2
 */
constexpr const HYKeyCode HY_KEY_KP_2 = 0x4000005au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_2) */

/**
 * @brief 小键盘数字键 3
 */
constexpr const HYKeyCode HY_KEY_KP_3 = 0x4000005bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_3) */

/**
 * @brief 小键盘数字键 4
 */
constexpr const HYKeyCode HY_KEY_KP_4 = 0x4000005cu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_4) */

/**
 * @brief 小键盘数字键 5
 */
constexpr const HYKeyCode HY_KEY_KP_5 = 0x4000005du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_5) */

/**
 * @brief 小键盘数字键 6
 */
constexpr const HYKeyCode HY_KEY_KP_6 = 0x4000005eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_6) */

/**
 * @brief 小键盘数字键 7
 */
constexpr const HYKeyCode HY_KEY_KP_7 = 0x4000005fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_7) */

/**
 * @brief 小键盘数字键 8
 */
constexpr const HYKeyCode HY_KEY_KP_8 = 0x40000060u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_8) */

/**
 * @brief 小键盘数字键 9
 */
constexpr const HYKeyCode HY_KEY_KP_9 = 0x40000061u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_9) */

/**
 * @brief 小键盘数字键 0
 */
constexpr const HYKeyCode HY_KEY_KP_0 = 0x40000062u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_0) */

/**
 * @brief 小键盘小数点键
 */
constexpr const HYKeyCode HY_KEY_KP_PERIOD = 0x40000063u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_PERIOD) */

/**
 * @brief 应用程序键
 */
constexpr const HYKeyCode HY_KEY_APPLICATION = 0x40000065u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_APPLICATION) */

/**
 * @brief 电源键
 */
constexpr const HYKeyCode HY_KEY_POWER = 0x40000066u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_POWER) */

/**
 * @brief 小键盘等号键
 */
constexpr const HYKeyCode HY_KEY_KP_EQUALS = 0x40000067u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_EQUALS) */

/**
 * @brief F13 功能键
 */
constexpr const HYKeyCode HY_KEY_F13 = 0x40000068u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F13) */

/**
 * @brief F14 功能键
 */
constexpr const HYKeyCode HY_KEY_F14 = 0x40000069u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F14) */

/**
 * @brief F15 功能键
 */
constexpr const HYKeyCode HY_KEY_F15 = 0x4000006au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F15) */

/**
 * @brief F16 功能键
 */
constexpr const HYKeyCode HY_KEY_F16 = 0x4000006bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F16) */

/**
 * @brief F17 功能键
 */
constexpr const HYKeyCode HY_KEY_F17 = 0x4000006cu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F17) */

/**
 * @brief F18 功能键
 */
constexpr const HYKeyCode HY_KEY_F18 = 0x4000006du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F18) */

/**
 * @brief F19 功能键
 */
constexpr const HYKeyCode HY_KEY_F19 = 0x4000006eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F19) */

/**
 * @brief F20 功能键
 */
constexpr const HYKeyCode HY_KEY_F20 = 0x4000006fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F20) */

/**
 * @brief F21 功能键
 */
constexpr const HYKeyCode HY_KEY_F21 = 0x40000070u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F21) */

/**
 * @brief F22 功能键
 */
constexpr const HYKeyCode HY_KEY_F22 = 0x40000071u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F22) */

/**
 * @brief F23 功能键
 */
constexpr const HYKeyCode HY_KEY_F23 = 0x40000072u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F23) */

/**
 * @brief F24 功能键
 */
constexpr const HYKeyCode HY_KEY_F24 = 0x40000073u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_F24) */

/**
 * @brief 执行键
 */
constexpr const HYKeyCode HY_KEY_EXECUTE = 0x40000074u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_EXECUTE) */

/**
 * @brief 帮助键
 */
constexpr const HYKeyCode HY_KEY_HELP = 0x40000075u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_HELP) */

/**
 * @brief 菜单键
 */
constexpr const HYKeyCode HY_KEY_MENU = 0x40000076u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_MENU) */

/**
 * @brief 选择键
 */
constexpr const HYKeyCode HY_KEY_SELECT = 0x40000077u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_SELECT) */

/**
 * @brief 停止键
 */
constexpr const HYKeyCode HY_KEY_STOP = 0x40000078u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_STOP) */

/**
 * @brief 再次键
 */
constexpr const HYKeyCode HY_KEY_AGAIN = 0x40000079u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_AGAIN) */

/**
 * @brief 撤销键
 */
constexpr const HYKeyCode HY_KEY_UNDO = 0x4000007au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_UNDO) */

/**
 * @brief 剪切键
 */
constexpr const HYKeyCode HY_KEY_CUT = 0x4000007bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_CUT) */

/**
 * @brief 复制键
 */
constexpr const HYKeyCode HY_KEY_COPY = 0x4000007cu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_COPY) */

/**
 * @brief 粘贴键
 */
constexpr const HYKeyCode HY_KEY_PASTE = 0x4000007du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PASTE) */

/**
 * @brief 查找键
 */
constexpr const HYKeyCode HY_KEY_FIND = 0x4000007eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_FIND) */

/**
 * @brief 静音键
 */
constexpr const HYKeyCode HY_KEY_MUTE = 0x4000007fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_MUTE) */

/**
 * @brief 音量增加键
 */
constexpr const HYKeyCode HY_KEY_VOLUMEUP = 0x40000080u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_VOLUMEUP) */

/**
 * @brief 音量减少键
 */
constexpr const HYKeyCode HY_KEY_VOLUMEDOWN = 0x40000081u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_VOLUMEDOWN) */

/**
 * @brief 小键盘逗号键
 */
constexpr const HYKeyCode HY_KEY_KP_COMMA = 0x40000085u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_COMMA) */

/**
 * @brief 小键盘等号AS400键
 */
constexpr const HYKeyCode HY_KEY_KP_EQUALSAS400 = 0x40000086u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_KP_EQUALSAS400) */

/**
 * @brief 替代擦除键
 */
constexpr const HYKeyCode HY_KEY_ALTERASE = 0x40000099u; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_ALTERASE) */

/**
 * @brief 系统请求键
 */
constexpr const HYKeyCode HY_KEY_SYSREQ = 0x4000009au; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_SYSREQ) */

/**
 * @brief 取消键
 */
constexpr const HYKeyCode HY_KEY_CANCEL = 0x4000009bu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_CANCEL) */

/**
 * @brief 清除键
 */
constexpr const HYKeyCode HY_KEY_CLEAR = 0x4000009cu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_CLEAR) */

/**
 * @brief 上一页键
 */
constexpr const HYKeyCode HY_KEY_PRIOR = 0x4000009du; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_PRIOR) */

/**
 * @brief 返回键 2
 */
constexpr const HYKeyCode HY_KEY_RETURN2 = 0x4000009eu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_RETURN2) */

/**
 * @brief 分隔符键
 */
constexpr const HYKeyCode HY_KEY_SEPARATOR = 0x4000009fu; /* HY_SCANCODE_TO_KEYCODE(HY_SCANCODE_SEPARATOR) */

/**
 * @brief OUT 键
 */
constexpr const HYKeyCode HY_KEY_OUT = 0x400000a0u;

/**
 * @brief OPER 键
 */
constexpr const HYKeyCode HY_KEY_OPER = 0x400000a1u;

/**
 * @brief Clear Again 键
 */
constexpr const HYKeyCode HY_KEY_CLEARAGAIN = 0x400000a2u;

/**
 * @brief CRSEL 键
 */
constexpr const HYKeyCode HY_KEY_CRSEL = 0x400000a3u;

/**
 * @brief EXSEL 键
 */
constexpr const HYKeyCode HY_KEY_EXSEL = 0x400000a4u;

/**
 * @brief 数字小键盘 00 键
 */
constexpr const HYKeyCode HY_KEY_KP_00 = 0x400000b0u;

/**
 * @brief 数字小键盘 000 键
 */
constexpr const HYKeyCode HY_KEY_KP_000 = 0x400000b1u;

/**
 * @brief 千分位分隔符 键
 */
constexpr const HYKeyCode HY_KEY_THOUSANDSSEPARATOR = 0x400000b2u;

/**
 * @brief 小数点分隔符 键
 */
constexpr const HYKeyCode HY_KEY_DECIMALSEPARATOR = 0x400000b3u;

/**
 * @brief 货币单位 键
 */
constexpr const HYKeyCode HY_KEY_CURRENCYUNIT = 0x400000b4u;

/**
 * @brief 货币子单位 键
 */
constexpr const HYKeyCode HY_KEY_CURRENCYSUBUNIT = 0x400000b5u;

/**
 * @brief 数字小键盘 左圆括号 键
 */
constexpr const HYKeyCode HY_KEY_KP_LEFTPAREN = 0x400000b6u;

/**
 * @brief 数字小键盘 右圆括号 键
 */
constexpr const HYKeyCode HY_KEY_KP_RIGHTPAREN = 0x400000b7u;

/**
 * @brief 数字小键盘 左大括号 键
 */
constexpr const HYKeyCode HY_KEY_KP_LEFTBRACE = 0x400000b8u;

/**
 * @brief 数字小键盘 右大括号 键
 */
constexpr const HYKeyCode HY_KEY_KP_RIGHTBRACE = 0x400000b9u;

/**
 * @brief 数字小键盘 Tab 键
 */
constexpr const HYKeyCode HY_KEY_KP_TAB = 0x400000bau;

/**
 * @brief 数字小键盘 退格 键
 */
constexpr const HYKeyCode HY_KEY_KP_BACKSPACE = 0x400000bbu;

/**
 * @brief 数字小键盘 A 键
 */
constexpr const HYKeyCode HY_KEY_KP_A = 0x400000bcu;

/**
 * @brief 数字小键盘 B 键
 */
constexpr const HYKeyCode HY_KEY_KP_B = 0x400000bdu;

/**
 * @brief 数字小键盘 C 键
 */
constexpr const HYKeyCode HY_KEY_KP_C = 0x400000beu;

/**
 * @brief 数字小键盘 D 键
 */
constexpr const HYKeyCode HY_KEY_KP_D = 0x400000bfu;

/**
 * @brief 数字小键盘 E 键
 */
constexpr const HYKeyCode HY_KEY_KP_E = 0x400000c0u;

/**
 * @brief 数字小键盘 F 键
 */
constexpr const HYKeyCode HY_KEY_KP_F = 0x400000c1u;

/**
 * @brief 数字小键盘 XOR 键
 */
constexpr const HYKeyCode HY_KEY_KP_XOR = 0x400000c2u;

/**
 * @brief 数字小键盘 Power 键
 */
constexpr const HYKeyCode HY_KEY_KP_POWER = 0x400000c3u;

/**
 * @brief 数字小键盘 Percent 键
 */
constexpr const HYKeyCode HY_KEY_KP_PERCENT = 0x400000c4u;

/**
 * @brief 数字小键盘 Less 键
 */
constexpr const HYKeyCode HY_KEY_KP_LESS = 0x400000c5u;

/**
 * @brief 数字小键盘 Greater 键
 */
constexpr const HYKeyCode HY_KEY_KP_GREATER = 0x400000c6u;

/**
 * @brief 数字小键盘 Ampersand 键
 */
constexpr const HYKeyCode HY_KEY_KP_AMPERSAND = 0x400000c7u;

/**
 * @brief 数字小键盘 双 Ampersand 键
 */
constexpr const HYKeyCode HY_KEY_KP_DBLAMPERSAND = 0x400000c8u;

/**
 * @brief 数字小键盘 Vertical Bar 键
 */
constexpr const HYKeyCode HY_KEY_KP_VERTICALBAR = 0x400000c9u;

/**
 * @brief 数字小键盘 双 Vertical Bar 键
 */
constexpr const HYKeyCode HY_KEY_KP_DBLVERTICALBAR = 0x400000cau;

/**
 * @brief 数字小键盘 Colon 键
 */
constexpr const HYKeyCode HY_KEY_KP_COLON = 0x400000cbu;

/**
 * @brief 数字小键盘 Hash 键
 */
constexpr const HYKeyCode HY_KEY_KP_HASH = 0x400000ccu;

/**
 * @brief 数字小键盘 Space 键
 */
constexpr const HYKeyCode HY_KEY_KP_SPACE = 0x400000cdu;

/**
 * @brief 数字小键盘 At 键
 */
constexpr const HYKeyCode HY_KEY_KP_AT = 0x400000ceu;

/**
 * @brief 数字小键盘 Exclam 键
 */
constexpr const HYKeyCode HY_KEY_KP_EXCLAM = 0x400000cfu;

/**
 * @brief 数字小键盘 内存存储 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMSTORE = 0x400000d0u;

/**
 * @brief 数字小键盘 内存回调 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMRECALL = 0x400000d1u;

/**
 * @brief 数字小键盘 内存清除 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMCLEAR = 0x400000d2u;

/**
 * @brief 数字小键盘 内存加法 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMADD = 0x400000d3u;

/**
 * @brief 数字小键盘 内存减法 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMSUBTRACT = 0x400000d4u;

/**
 * @brief 数字小键盘 内存乘法 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMMULTIPLY = 0x400000d5u;

/**
 * @brief 数字小键盘 内存除法 键
 */
constexpr const HYKeyCode HY_KEY_KP_MEMDIVIDE = 0x400000d6u;

/**
 * @brief 数字小键盘 正负号 键
 */
constexpr const HYKeyCode HY_KEY_KP_PLUSMINUS = 0x400000d7u;

/**
 * @brief 数字小键盘 清除 键
 */
constexpr const HYKeyCode HY_KEY_KP_CLEAR = 0x400000d8u;

/**
 * @brief 数字小键盘 清除条目 键
 */
constexpr const HYKeyCode HY_KEY_KP_CLEARENTRY = 0x400000d9u;

/**
 * @brief 数字小键盘 Binary 键
 */
constexpr const HYKeyCode HY_KEY_KP_BINARY = 0x400000dau;

/**
 * @brief 数字小键盘 Octal 键
 */
constexpr const HYKeyCode HY_KEY_KP_OCTAL = 0x400000dbu;

/**
 * @brief 数字小键盘 Decimal 键
 */
constexpr const HYKeyCode HY_KEY_KP_DECIMAL = 0x400000dcu;

/**
 * @brief 数字小键盘 Hexadecimal 键
 */
constexpr const HYKeyCode HY_KEY_KP_HEXADECIMAL = 0x400000ddu;

/**
 * @brief 左 Control 键
 */
constexpr const HYKeyCode HY_KEY_LCTRL = 0x400000e0u;

/**
 * @brief 左 Shift 键
 */
constexpr const HYKeyCode HY_KEY_LSHIFT = 0x400000e1u;

/**
 * @brief 左 Alt 键
 */
constexpr const HYKeyCode HY_KEY_LALT = 0x400000e2u;

/**
 * @brief 左 GUI 键
 */
constexpr const HYKeyCode HY_KEY_LGUI = 0x400000e3u;

/**
 * @brief 右 Control 键
 */
constexpr const HYKeyCode HY_KEY_RCTRL = 0x400000e4u;

/**
 * @brief 右 Shift 键
 */
constexpr const HYKeyCode HY_KEY_RSHIFT = 0x400000e5u;

/**
 * @brief 右 Alt 键
 */
constexpr const HYKeyCode HY_KEY_RALT = 0x400000e6u;

/**
 * @brief 右 GUI 键
 */
constexpr const HYKeyCode HY_KEY_RGUI = 0x400000e7u;

/**
 * @brief Mode 键
 */
constexpr const HYKeyCode HY_KEY_MODE = 0x40000101u;

/**
 * @brief Sleep 键
 */
constexpr const HYKeyCode HY_KEY_SLEEP = 0x40000102u;

/**
 * @brief Wake 键
 */
constexpr const HYKeyCode HY_KEY_WAKE = 0x40000103u;

/**
 * @brief Channel Increment 键
 */
constexpr const HYKeyCode HY_KEY_CHANNEL_INCREMENT = 0x40000104u;

/**
 * @brief Channel Decrement 键
 */
constexpr const HYKeyCode HY_KEY_CHANNEL_DECREMENT = 0x40000105u;

/**
 * @brief Media Play 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_PLAY = 0x40000106u;

/**
 * @brief Media Pause 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_PAUSE = 0x40000107u;

/**
 * @brief Media Record 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_RECORD = 0x40000108u;

/**
 * @brief Media Fast Forward 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_FAST_FORWARD = 0x40000109u;

/**
 * @brief Media Rewind 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_REWIND = 0x4000010au;

/**
 * @brief Media Next Track 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_NEXT_TRACK = 0x4000010bu;

/**
 * @brief Media Previous Track 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_PREVIOUS_TRACK = 0x4000010cu;

/**
 * @brief Media Stop 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_STOP = 0x4000010du;

/**
 * @brief Media Eject 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_EJECT = 0x4000010eu;

/**
 * @brief Media Play/Pause 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_PLAY_PAUSE = 0x4000010fu;

/**
 * @brief Media Select 键
 */
constexpr const HYKeyCode HY_KEY_MEDIA_SELECT = 0x40000110u;

/**
 * @brief AC New 键
 */
constexpr const HYKeyCode HY_KEY_AC_NEW = 0x40000111u;

/**
 * @brief AC Open 键
 */
constexpr const HYKeyCode HY_KEY_AC_OPEN = 0x40000112u;

/**
 * @brief AC Close 键
 */
constexpr const HYKeyCode HY_KEY_AC_CLOSE = 0x40000113u;

/**
 * @brief AC Exit 键
 */
constexpr const HYKeyCode HY_KEY_AC_EXIT = 0x40000114u;

/**
 * @brief AC Save 键
 */
constexpr const HYKeyCode HY_KEY_AC_SAVE = 0x40000115u;

/**
 * @brief AC Print 键
 */
constexpr const HYKeyCode HY_KEY_AC_PRINT = 0x40000116u;

/**
 * @brief AC Properties 键
 */
constexpr const HYKeyCode HY_KEY_AC_PROPERTIES = 0x40000117u;

/**
 * @brief AC Search 键
 */
constexpr const HYKeyCode HY_KEY_AC_SEARCH = 0x40000118u;

/**
 * @brief AC Home 键
 */
constexpr const HYKeyCode HY_KEY_AC_HOME = 0x40000119u;

/**
 * @brief AC Back 键
 */
constexpr const HYKeyCode HY_KEY_AC_BACK = 0x4000011au;

/**
 * @brief AC Forward 键
 */
constexpr const HYKeyCode HY_KEY_AC_FORWARD = 0x4000011bu;

/**
 * @brief AC Stop 键
 */
constexpr const HYKeyCode HY_KEY_AC_STOP = 0x4000011cu;

/**
 * @brief AC Refresh 键
 */
constexpr const HYKeyCode HY_KEY_AC_REFRESH = 0x4000011du;

/**
 * @brief AC Bookmarks 键
 */
constexpr const HYKeyCode HY_KEY_AC_BOOKMARKS = 0x4000011eu;

/**
 * @brief Soft Left 键
 */
constexpr const HYKeyCode HY_KEY_SOFTLEFT = 0x4000011fu;

/**
 * @brief Soft Right 键
 */
constexpr const HYKeyCode HY_KEY_SOFTRIGHT = 0x40000120u;

/**
 * @brief Call 键
 */
constexpr const HYKeyCode HY_KEY_CALL = 0x40000121u;

/**
 * @brief End Call 键
 */
constexpr const HYKeyCode HY_KEY_ENDCALL = 0x40000122u;

// -----------------------

/**
 * 直接copy SDL ;P
 * */
typedef enum HYScancode: uint32_t {
  HY_SCANCODE_UNKNOWN = 0,

  /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
  /* @{ */

  HY_SCANCODE_A = 4,
  HY_SCANCODE_B = 5,
  HY_SCANCODE_C = 6,
  HY_SCANCODE_D = 7,
  HY_SCANCODE_E = 8,
  HY_SCANCODE_F = 9,
  HY_SCANCODE_G = 10,
  HY_SCANCODE_H = 11,
  HY_SCANCODE_I = 12,
  HY_SCANCODE_J = 13,
  HY_SCANCODE_K = 14,
  HY_SCANCODE_L = 15,
  HY_SCANCODE_M = 16,
  HY_SCANCODE_N = 17,
  HY_SCANCODE_O = 18,
  HY_SCANCODE_P = 19,
  HY_SCANCODE_Q = 20,
  HY_SCANCODE_R = 21,
  HY_SCANCODE_S = 22,
  HY_SCANCODE_T = 23,
  HY_SCANCODE_U = 24,
  HY_SCANCODE_V = 25,
  HY_SCANCODE_W = 26,
  HY_SCANCODE_X = 27,
  HY_SCANCODE_Y = 28,
  HY_SCANCODE_Z = 29,

  HY_SCANCODE_1 = 30,
  HY_SCANCODE_2 = 31,
  HY_SCANCODE_3 = 32,
  HY_SCANCODE_4 = 33,
  HY_SCANCODE_5 = 34,
  HY_SCANCODE_6 = 35,
  HY_SCANCODE_7 = 36,
  HY_SCANCODE_8 = 37,
  HY_SCANCODE_9 = 38,
  HY_SCANCODE_0 = 39,

  HY_SCANCODE_RETURN = 40,
  HY_SCANCODE_ESCAPE = 41,
  HY_SCANCODE_BACKSPACE = 42,
  HY_SCANCODE_TAB = 43,
  HY_SCANCODE_SPACE = 44,

  HY_SCANCODE_MINUS = 45,
  HY_SCANCODE_EQUALS = 46,
  HY_SCANCODE_LEFTBRACKET = 47,
  HY_SCANCODE_RIGHTBRACKET = 48,
  HY_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
  HY_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate HY_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
  HY_SCANCODE_SEMICOLON = 51,
  HY_SCANCODE_APOSTROPHE = 52,
  HY_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
  HY_SCANCODE_COMMA = 54,
  HY_SCANCODE_PERIOD = 55,
  HY_SCANCODE_SLASH = 56,

  HY_SCANCODE_CAPSLOCK = 57,

  HY_SCANCODE_F1 = 58,
  HY_SCANCODE_F2 = 59,
  HY_SCANCODE_F3 = 60,
  HY_SCANCODE_F4 = 61,
  HY_SCANCODE_F5 = 62,
  HY_SCANCODE_F6 = 63,
  HY_SCANCODE_F7 = 64,
  HY_SCANCODE_F8 = 65,
  HY_SCANCODE_F9 = 66,
  HY_SCANCODE_F10 = 67,
  HY_SCANCODE_F11 = 68,
  HY_SCANCODE_F12 = 69,

  HY_SCANCODE_PRINTSCREEN = 70,
  HY_SCANCODE_SCROLLLOCK = 71,
  HY_SCANCODE_PAUSE = 72,
  HY_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
  HY_SCANCODE_HOME = 74,
  HY_SCANCODE_PAGEUP = 75,
  HY_SCANCODE_DELETE = 76,
  HY_SCANCODE_END = 77,
  HY_SCANCODE_PAGEDOWN = 78,
  HY_SCANCODE_RIGHT = 79,
  HY_SCANCODE_LEFT = 80,
  HY_SCANCODE_DOWN = 81,
  HY_SCANCODE_UP = 82,

  HY_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
  HY_SCANCODE_KP_DIVIDE = 84,
  HY_SCANCODE_KP_MULTIPLY = 85,
  HY_SCANCODE_KP_MINUS = 86,
  HY_SCANCODE_KP_PLUS = 87,
  HY_SCANCODE_KP_ENTER = 88,
  HY_SCANCODE_KP_1 = 89,
  HY_SCANCODE_KP_2 = 90,
  HY_SCANCODE_KP_3 = 91,
  HY_SCANCODE_KP_4 = 92,
  HY_SCANCODE_KP_5 = 93,
  HY_SCANCODE_KP_6 = 94,
  HY_SCANCODE_KP_7 = 95,
  HY_SCANCODE_KP_8 = 96,
  HY_SCANCODE_KP_9 = 97,
  HY_SCANCODE_KP_0 = 98,
  HY_SCANCODE_KP_PERIOD = 99,

  HY_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
  HY_SCANCODE_APPLICATION = 101,    /**< windows contextual menu, compose */
  HY_SCANCODE_POWER = 102,          /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
  HY_SCANCODE_KP_EQUALS = 103,
  HY_SCANCODE_F13 = 104,
  HY_SCANCODE_F14 = 105,
  HY_SCANCODE_F15 = 106,
  HY_SCANCODE_F16 = 107,
  HY_SCANCODE_F17 = 108,
  HY_SCANCODE_F18 = 109,
  HY_SCANCODE_F19 = 110,
  HY_SCANCODE_F20 = 111,
  HY_SCANCODE_F21 = 112,
  HY_SCANCODE_F22 = 113,
  HY_SCANCODE_F23 = 114,
  HY_SCANCODE_F24 = 115,
  HY_SCANCODE_EXECUTE = 116,
  HY_SCANCODE_HELP = 117, /**< AL Integrated Help Center */
  HY_SCANCODE_MENU = 118, /**< Menu (show menu) */
  HY_SCANCODE_SELECT = 119,
  HY_SCANCODE_STOP = 120,  /**< AC Stop */
  HY_SCANCODE_AGAIN = 121, /**< AC Redo/Repeat */
  HY_SCANCODE_UNDO = 122,  /**< AC Undo */
  HY_SCANCODE_CUT = 123,   /**< AC Cut */
  HY_SCANCODE_COPY = 124,  /**< AC Copy */
  HY_SCANCODE_PASTE = 125, /**< AC Paste */
  HY_SCANCODE_FIND = 126,  /**< AC Find */
  HY_SCANCODE_MUTE = 127,
  HY_SCANCODE_VOLUMEUP = 128,
  HY_SCANCODE_VOLUMEDOWN = 129,
  /* not sure whether there's a reason to enable these */
  /*     HY_SCANCODE_LOCKINGCAPSLOCK = 130,  */
  /*     HY_SCANCODE_LOCKINGNUMLOCK = 131, */
  /*     HY_SCANCODE_LOCKINGSCROLLLOCK = 132, */
  HY_SCANCODE_KP_COMMA = 133,
  HY_SCANCODE_KP_EQUALSAS400 = 134,

  HY_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
  HY_SCANCODE_INTERNATIONAL2 = 136,
  HY_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
  HY_SCANCODE_INTERNATIONAL4 = 138,
  HY_SCANCODE_INTERNATIONAL5 = 139,
  HY_SCANCODE_INTERNATIONAL6 = 140,
  HY_SCANCODE_INTERNATIONAL7 = 141,
  HY_SCANCODE_INTERNATIONAL8 = 142,
  HY_SCANCODE_INTERNATIONAL9 = 143,
  HY_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
  HY_SCANCODE_LANG2 = 145, /**< Hanja conversion */
  HY_SCANCODE_LANG3 = 146, /**< Katakana */
  HY_SCANCODE_LANG4 = 147, /**< Hiragana */
  HY_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
  HY_SCANCODE_LANG6 = 149, /**< reserved */
  HY_SCANCODE_LANG7 = 150, /**< reserved */
  HY_SCANCODE_LANG8 = 151, /**< reserved */
  HY_SCANCODE_LANG9 = 152, /**< reserved */

  HY_SCANCODE_ALTERASE = 153, /**< Erase-Eaze */
  HY_SCANCODE_SYSREQ = 154,
  HY_SCANCODE_CANCEL = 155, /**< AC Cancel */
  HY_SCANCODE_CLEAR = 156,
  HY_SCANCODE_PRIOR = 157,
  HY_SCANCODE_RETURN2 = 158,
  HY_SCANCODE_SEPARATOR = 159,
  HY_SCANCODE_OUT = 160,
  HY_SCANCODE_OPER = 161,
  HY_SCANCODE_CLEARAGAIN = 162,
  HY_SCANCODE_CRSEL = 163,
  HY_SCANCODE_EXSEL = 164,

  HY_SCANCODE_KP_00 = 176,
  HY_SCANCODE_KP_000 = 177,
  HY_SCANCODE_THOUSANDSSEPARATOR = 178,
  HY_SCANCODE_DECIMALSEPARATOR = 179,
  HY_SCANCODE_CURRENCYUNIT = 180,
  HY_SCANCODE_CURRENCYSUBUNIT = 181,
  HY_SCANCODE_KP_LEFTPAREN = 182,
  HY_SCANCODE_KP_RIGHTPAREN = 183,
  HY_SCANCODE_KP_LEFTBRACE = 184,
  HY_SCANCODE_KP_RIGHTBRACE = 185,
  HY_SCANCODE_KP_TAB = 186,
  HY_SCANCODE_KP_BACKSPACE = 187,
  HY_SCANCODE_KP_A = 188,
  HY_SCANCODE_KP_B = 189,
  HY_SCANCODE_KP_C = 190,
  HY_SCANCODE_KP_D = 191,
  HY_SCANCODE_KP_E = 192,
  HY_SCANCODE_KP_F = 193,
  HY_SCANCODE_KP_XOR = 194,
  HY_SCANCODE_KP_POWER = 195,
  HY_SCANCODE_KP_PERCENT = 196,
  HY_SCANCODE_KP_LESS = 197,
  HY_SCANCODE_KP_GREATER = 198,
  HY_SCANCODE_KP_AMPERSAND = 199,
  HY_SCANCODE_KP_DBLAMPERSAND = 200,
  HY_SCANCODE_KP_VERTICALBAR = 201,
  HY_SCANCODE_KP_DBLVERTICALBAR = 202,
  HY_SCANCODE_KP_COLON = 203,
  HY_SCANCODE_KP_HASH = 204,
  HY_SCANCODE_KP_SPACE = 205,
  HY_SCANCODE_KP_AT = 206,
  HY_SCANCODE_KP_EXCLAM = 207,
  HY_SCANCODE_KP_MEMSTORE = 208,
  HY_SCANCODE_KP_MEMRECALL = 209,
  HY_SCANCODE_KP_MEMCLEAR = 210,
  HY_SCANCODE_KP_MEMADD = 211,
  HY_SCANCODE_KP_MEMSUBTRACT = 212,
  HY_SCANCODE_KP_MEMMULTIPLY = 213,
  HY_SCANCODE_KP_MEMDIVIDE = 214,
  HY_SCANCODE_KP_PLUSMINUS = 215,
  HY_SCANCODE_KP_CLEAR = 216,
  HY_SCANCODE_KP_CLEARENTRY = 217,
  HY_SCANCODE_KP_BINARY = 218,
  HY_SCANCODE_KP_OCTAL = 219,
  HY_SCANCODE_KP_DECIMAL = 220,
  HY_SCANCODE_KP_HEXADECIMAL = 221,

  HY_SCANCODE_LCTRL = 224,
  HY_SCANCODE_LSHIFT = 225,
  HY_SCANCODE_LALT = 226, /**< alt, option */
  HY_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
  HY_SCANCODE_RCTRL = 228,
  HY_SCANCODE_RSHIFT = 229,
  HY_SCANCODE_RALT = 230, /**< alt gr, option */
  HY_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

  HY_SCANCODE_MODE = 257, /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special SDL_KMOD_MODE for it I'm adding it here
                                 */

  /* @} */ /* Usage page 0x07 */

  /**
     *  \name Usage page 0x0C
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     *
     *  There are way more keys in the spec than we can represent in the
     *  current scancode range, so pick the ones that commonly come up in
     *  real world usage.
     */
  /* @{ */

  HY_SCANCODE_SLEEP = 258, /**< Sleep */
  HY_SCANCODE_WAKE = 259,  /**< Wake */

  HY_SCANCODE_CHANNEL_INCREMENT = 260, /**< Channel Increment */
  HY_SCANCODE_CHANNEL_DECREMENT = 261, /**< Channel Decrement */

  HY_SCANCODE_MEDIA_PLAY = 262,           /**< Play */
  HY_SCANCODE_MEDIA_PAUSE = 263,          /**< Pause */
  HY_SCANCODE_MEDIA_RECORD = 264,         /**< Record */
  HY_SCANCODE_MEDIA_FAST_FORWARD = 265,   /**< Fast Forward */
  HY_SCANCODE_MEDIA_REWIND = 266,         /**< Rewind */
  HY_SCANCODE_MEDIA_NEXT_TRACK = 267,     /**< Next Track */
  HY_SCANCODE_MEDIA_PREVIOUS_TRACK = 268, /**< Previous Track */
  HY_SCANCODE_MEDIA_STOP = 269,           /**< Stop */
  HY_SCANCODE_MEDIA_EJECT = 270,          /**< Eject */
  HY_SCANCODE_MEDIA_PLAY_PAUSE = 271,     /**< Play / Pause */
  HY_SCANCODE_MEDIA_SELECT = 272,         /* Media Select */

  HY_SCANCODE_AC_NEW = 273,        /**< AC New */
  HY_SCANCODE_AC_OPEN = 274,       /**< AC Open */
  HY_SCANCODE_AC_CLOSE = 275,      /**< AC Close */
  HY_SCANCODE_AC_EXIT = 276,       /**< AC Exit */
  HY_SCANCODE_AC_SAVE = 277,       /**< AC Save */
  HY_SCANCODE_AC_PRINT = 278,      /**< AC Print */
  HY_SCANCODE_AC_PROPERTIES = 279, /**< AC Properties */

  HY_SCANCODE_AC_SEARCH = 280,    /**< AC Search */
  HY_SCANCODE_AC_HOME = 281,      /**< AC Home */
  HY_SCANCODE_AC_BACK = 282,      /**< AC Back */
  HY_SCANCODE_AC_FORWARD = 283,   /**< AC Forward */
  HY_SCANCODE_AC_STOP = 284,      /**< AC Stop */
  HY_SCANCODE_AC_REFRESH = 285,   /**< AC Refresh */
  HY_SCANCODE_AC_BOOKMARKS = 286, /**< AC Bookmarks */

  /* @} */ /* Usage page 0x0C */


  /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
  /* @{ */

  HY_SCANCODE_SOFTLEFT = 287,  /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
  HY_SCANCODE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
  HY_SCANCODE_CALL = 289,      /**< Used for accepting phone calls. */
  HY_SCANCODE_ENDCALL = 290,   /**< Used for rejecting phone calls. */

  /* @} */ /* Mobile keys */

  /* Add any other keys here. */

  HY_SCANCODE_RESERVED = 400, /**< 400-500 reserved for dynamic keycodes */

  HY_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */

} HYScancode;

// -----------------------

/**
 * @brief 键位修饰
 * 具体值参见 常量定义HY_KMOD_
 * */
typedef uint16_t HYKeymod;

/**
 * @brief 无
 * */
constexpr const HYKeymod HY_KMOD_NONE = 0x0000u;

/**
 * @brief 左Shift键
 * */
constexpr const HYKeymod HY_KMOD_LSHIFT = 0x0001u;

/**
 * @brief 右Shift键
 * */
constexpr const HYKeymod HY_KMOD_RSHIFT = 0x0002u;

/**
 * @brief 左Ctrl键
 * */
constexpr const HYKeymod HY_KMOD_LCTRL = 0x0040u;

/**
 * @brief 右Ctrl键
 * */
constexpr const HYKeymod HY_KMOD_RCTRL = 0x0080u;

/**
 * @brief 左Alt键
 * */
constexpr const HYKeymod HY_KMOD_LALT = 0x0100u;

/**
 * @brief 右Alt键
 * */
constexpr const HYKeymod HY_KMOD_RALT = 0x0200u;

/**
 * @brief 左GUI键
 * */
constexpr const HYKeymod HY_KMOD_LGUI = 0x0400u;

/**
 * @brief 右GUI键
 * */
constexpr const HYKeymod HY_KMOD_RGUI = 0x0800u;

/**
 * @brief Num Lock键
 * */
constexpr const HYKeymod HY_KMOD_NUM = 0x1000u;

/**
 * @brief Caps Lock键
 * */
constexpr const HYKeymod HY_KMOD_CAPS = 0x2000u;

/**
 * @brief 模式键
 * */
constexpr const HYKeymod HY_KMOD_MODE = 0x4000u;

/**
 * @brief 滚动锁定键
 * */
constexpr const HYKeymod HY_KMOD_SCROLL = 0x8000u;

/**
 * @brief Ctrl键
 * */
constexpr const HYKeymod HY_KMOD_CTRL = (HY_KMOD_LCTRL | HY_KMOD_RCTRL);

/**
 * @brief Shift键
 * */
constexpr const HYKeymod HY_KMOD_SHIFT = (HY_KMOD_LSHIFT | HY_KMOD_RSHIFT);

/**
 * @brief Alt键
 * */
constexpr const HYKeymod HY_KMOD_ALT = (HY_KMOD_LALT | HY_KMOD_RALT);

/**
 * @brief GUI键
 * */
constexpr const HYKeymod HY_KMOD_GUI = (HY_KMOD_LGUI | HY_KMOD_RGUI);

}// namespace HYGUI

#endif//HYGUI_KEYCODE_H
