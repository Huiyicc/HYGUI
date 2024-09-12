import shutil

import unicodedata
from fontTools.ttLib import TTFont, newTable
from fontTools.subset import Subsetter, Options
from fontTools.merge import Merger
import os
import emoji


def split_emoji_string(s):
    # 使用 emoji 库的 demojize 方法将 emoji 替换为对应的文本表示
    demojized = emoji.demojize(s)

    # 初始化一个空列表来存储分离的字符
    result = []

    # 遍历每个字符
    i = 0
    while i < len(demojized):
        if demojized[i] == ':' and i + 1 < len(demojized):  # 检查是否是 emoji 的文本表示
            end = demojized.find(':', i + 1)
            if end != -1:
                # 提取 emoji 的文本表示
                emoji_text = demojized[i:end + 1]
                # 使用 emojize 将文本表示转换回 emoji
                result.append(emoji.emojize(emoji_text))
                i = end + 1
            else:
                result.append(demojized[i])
                i += 1
        else:
            result.append(demojized[i])
            i += 1

    return result


def is_char_in_font(font, char):
    # 读取字体文件

    # 标准化字符
    normalized_char = unicodedata.normalize('NFC', char)

    # 将字符转换为 UTF-32 编码的字节序列
    utf32_bytes = normalized_char.encode('utf-32')

    # 从 UTF-32 编码的字节序列中提取码点
    code_points = [int.from_bytes(utf32_bytes[i:i + 4], 'little') for i in range(4, len(utf32_bytes), 4)]

    # 获取字体中的 cmap 表
    cmap = font['cmap']

    # 遍历 cmap 表中的所有子表
    for table in cmap.tables:
        # 检查子表是否包含所有码点
        if all(code_point in table.cmap for code_point in code_points):
            return True

    return False


def trim_font(input_font_path, output_font_path, characters):
    # 打开字体文件
    font = TTFont(input_font_path)
    sps = split_emoji_string(characters)
    sp_str = ''
    for c in sps:
        if is_char_in_font(font, c):
            sp_str += c

    # 配置裁剪选项
    options = Options()
    options.glyph_names = True
    options.layout_features = "*"
    options.hinting = True

    # 创建子集化器
    subsetter = Subsetter(options=options)

    # 将字符添加到子集中
    subsetter.populate(text=characters)

    # 裁剪字体
    subsetter.subset(font)

    # # 保存裁剪后的字体
    # font.save(output_font_path)
    return font


if __name__ == "__main__":
    font_list = [
        # 字形缩放维度等需要一致,普通字符和特殊符号字体不要混合
        {
            "fonts": ["../../resource/font/EmojiFontRaw.ttf"],
            "map": "comprehensive_symbols.txt",
            "out": "../../resource/font/MergeEmojiFont.ttf",
        },
        {
            "fonts": [
                # "../../resource/font/UtilsFontRaw.ttf",
                "../../resource/font/SourceHanSans-VF.ttf",
            ],
            "map": "comprehensive_symbols.txt",
            "out": "../../resource/font/MergeUtilsFont.ttf",
        },
    ]

    for index in range(len(font_list)):
        with open(font_list[index]["map"], 'r', encoding='utf-8') as f:
            font_list[index]['text'] = f.read()

    for findex in range(len(font_list)):
        n = 0
        subset_fonts = []
        obj = font_list[findex]
        for font in obj["fonts"]:
            if os.path.exists(font):
                fount = trim_font(font, obj["out"], obj['text'])
                fount.save(f'_temp_{n}.ttf')
                subset_fonts.append(f'_temp_{n}.ttf')
            else:
                print(f"Font file {font} not found!")
            n += 1

        if len(subset_fonts) == 1:
            shutil.copy2(subset_fonts[0], obj['out'])
            os.remove(subset_fonts[0])
        else:
            merger = Merger()
            new_font = merger.merge(subset_fonts)
            new_font.save(obj['out'])
        for font in subset_fonts:
            os.remove(font)
        # out_ttf = TTFont(subset_fonts[0])
        # glyphs = out_ttf.getGlyphSet()
        # for findex in range(1,len(subset_fonts)):
        #     add_glyphs = TTFont(subset_fonts[findex])
        #     for glyph_name in add_glyphs.keys():
        #         if glyph_name not in glyphs:
        #             glyph = add_glyphs[glyph_name]
        #             glyphs[glyph_name] = glyph
        # out_ttf.save(output_font_path)

# from fontTools.ttLib import TTFont
# from fontTools.subset import Subsetter, Options
#
#
# def trim_font(input_font_path, output_font_path, characters):
#     # 打开字体文件
#
#     font = TTFont(input_font_path)
#     sps = split_emoji_string(characters)
#     sp_str = ''
#     for c in sps:
#         if is_char_in_font(font, c):
#             sp_str += c
#
#     # 配置裁剪选项
#     options = Options()
#     options.glyph_names = True
#     options.layout_features = "*"
#     options.hinting = True
#
#     # 创建子集化器
#     subsetter = Subsetter(options=options)
#
#     # 将字符添加到子集中
#     subsetter.populate(text=sp_str)
#
#     # 裁剪字体
#     subsetter.subset(font)
#
#     # 保存裁剪后的字体
#     font.save(output_font_path)
#
#
# # 输入文件路径
# input_font_path = r"../../resource/font/EmojiFontRaw.ttf"
#
# # 输出文件路径
# output_font_path = r"../../resource/font/MergeEmojiFont.ttf"
#
# with open("comprehensive_symbols.txt",'r',encoding='utf-8') as f:
#     # 需要保留的Emoji字符
#     characters = str(f.read())
#
# # 裁剪字体
# trim_font(input_font_path, output_font_path, characters)
