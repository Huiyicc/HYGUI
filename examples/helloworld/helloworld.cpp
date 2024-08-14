//
// Created by 19254 on 24-5-13.
//
#include <HYGUI/HYGUI.h>
#include <iostream>

using namespace HYGUI;

int main() {

#ifdef _WIN32
//  system("chcp 65001");
#endif

  HYInit(HYGlobalFlag::HYGlobalFlagGraphicDefault);
  auto wind = HYWindowCreate(nullptr, "Hello World");
  HYWindowSkinHook(wind, HYRGB{255, 255, 255}, 210);

  auto label = HYLabelCreate(wind, nullptr, "标签1\n\ncascas", 50, 50, 700, 500, true);
  HYLabelSetColorStyle(label, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopToBottom,
                       {HYARGB{255, 0, 255, 0}, HYARGB{255, 0, 0, 255}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 0, 0, 255}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label), "标签1 g");

  auto label1 = HYLabelCreate(wind, label, u8"标签2\n\n2132", -50, 160, 300, 250, true);
  HYLabelSetColorStyle(label1, HYGradientMode::HYGradientModeRadial,
                       HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
                       {HYARGB{255, 0, 0, 255}, HYARGB{255, 255, 0, 0}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 255, 0, 0}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label1), "标签2 b");

//  auto label11 = HYLabelCreate(wind, label1, u8"🥰🤗💕❤️🧐\n"
//                                             "忧从何来？国乎？家乎？民乎？非也，前途战。\n"
//                                             "年少终究一场梦，要拼，要闯，要奋斗。曾经岁月的迷茫，早已拔开，却在心中留下了伤疤。我感悟不到天地的悲凉，理解不了先贤的豁达，抒发不出心中的苦闷，只想拼一场，却找不到一条明朗的大道。\n"
//                                             "睡梦是美好的，梦醒时分却如坠深渊。要么醍醐灌顶，发愤图强；要么醉生梦死，声色犬马。我们的迷茫来自我们的无知，我们的忧愁来自展望未来，何以解忧？惟有明道。\n"
//                                             "古卷的书香，让我们得以承继先人的智慧，得以研究万物的事理，却也带来了疑惑，生与死？名与利？权与财？一个问题，无数答案。读书为了什么？不知道？只知为了以后不悔退？依旧有无数答案。何以解忧？惟有杜康。\n"
//                                             "大学之道，在明德，在亲民，在于至善。修身乎？齐家乎？八纲所为何乎？达三目也。{三体}中在外太空可食人尸，在地球上无异于违背天理伦常，可怪乎？或许，周边环境可以改变一切，或许所谓的忧愁换一个角度会有不同的看法。\n"
//                                             "人生像是一道题；有人像是一道选择题，因为已有人为他作好一切；有人稍次，像是一道填空题，只需在合适的时间、地点发挥自己的作用；而我们只能是一道问答题，不断地构好思路，或付诸实践，或以逸待劳，收获的或完美，或残缺，无人替自己负责。\n"
//                                             "不想在中年后悔少年，不想在少年浪费时间，何以解忧？惟有拼搏。\n"
//                                             "🥰🤗💕❤️🧐",
//                               10, 10, 200, 150, true);
  auto label11 = HYLabelCreate(wind, label1, u8"🧐",
                               10, 10, 200, 150, true);
  HYLabelSetColorStyle(label11, HYGradientMode::HYGradientModeLinear,
                       HYGradientDirection::HYGradientDirectionTopLeftToBottomRight,
                       {HYARGB{255, 255, 0, 0}, HYARGB{255, 0, 255, 0}},
                       HYARGB{255, 255, 255, 255},
                       HYARGB{255, 0, 0, 255}, 2);
  HYObjectSetName(reinterpret_cast<HYObjectHandle>(label11), "标签 r");

  HYWindowShow(wind);
  HYWindowMessageLoop();
  std::this_thread::sleep_for(std::chrono::seconds(3));
  HYExit();
  return 0;
}
