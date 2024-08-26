from fontTools.ttLib import TTFont
from fontTools.subset import Subsetter, Options


def trim_font(input_font_path, output_font_path, characters):
    # 打开字体文件
    font = TTFont(input_font_path)

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

    # 保存裁剪后的字体
    font.save(output_font_path)


# 输入文件路径
input_font_path = r"../../resource/font/NotoColorEmojiRaw.ttf"

# 输出文件路径
output_font_path = r"../../resource/font/NotoColorEmoji.ttf"

with open("emoji_map.txt",'r',encoding='utf-8') as f:
    # 需要保留的Emoji字符
    characters = str(f.read())

# 裁剪字体
trim_font(input_font_path, output_font_path, characters)
