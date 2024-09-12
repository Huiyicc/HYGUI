# 定义要遍历的Unicode范围
ranges = [
    (0x2600, 0x26FF),  # Miscellaneous Symbols
    (0x24B6, 0x24E9),  # Enclosed Alphanumerics (带圈字母)
    (0x2460, 0x24FF),  # Enclosed Alphanumerics (带圈数字和字母)
    (0x2300, 0x23FF),  # Miscellaneous Technical
    (0x1F300, 0x1F5FF), # Miscellaneous Symbols and Pictographs
    (0x1F600, 0x1F64F), # Emoticons
    (0x1F680, 0x1F6FF), # Transport and Map Symbols
    (0x1F700, 0x1F77F), # Alchemical Symbols
    (0x1F780, 0x1F7FF), # Geometric Shapes Extended
    (0x1F800, 0x1F8FF), # Supplemental Arrows-C
    (0x1F900, 0x1F9FF), # Supplemental Symbols and Pictographs
    (0x1FA00, 0x1FA6F), # Chess Symbols
    (0x1FA70, 0x1FAFF), # Symbols and Pictographs Extended-A
    (0x1D4D0, 0x1D503), # Mathematical Script Capital Letters
    (0x1D504, 0x1D537), # Mathematical Script Small Letters
    (0x1D538, 0x1D56B), # Mathematical Double-Struck Capital Letters
    (0x1D56C, 0x1D59F), # Mathematical Double-Struck Small Letters
    (0x1D5A0, 0x1D5D3), # Mathematical Bold Fraktur Letters
    (0x1D5D4, 0x1D607), # Mathematical Sans-Serif Bold Letters
    (0x1D608, 0x1D63B), # Mathematical Sans-Serif Italic Letters
    (0x1D63C, 0x1D66F), # Mathematical Sans-Serif Bold Italic Letters
    (0x1D670, 0x1D6A3), # Mathematical Monospace Letters
    (0x2700, 0x27BF),  # Dingbats
    (0x2A00, 0x2AFF),  # Supplemental Mathematical Operators
    (0x2B00, 0x2BFF),  # Miscellaneous Symbols and Arrows
    (0x2E00, 0x2E7F),  # Supplemental Punctuation
    (0x25A0, 0x25FF),  # Geometric Shapes
    (0x2500, 0x257F),  # Box Drawing
    (0x2580, 0x259F),  # Block Elements
    (0x1FAF0, 0x1FAFF), # Miscellaneous Symbols and Pictographs Extended
    (0x1F6E0, 0x1F6FF), # Transport and Map Symbols Extended
]

# 用于存储拼接的字形码
with open('emoji_map.txt','r',encoding='utf-8') as f:
    glyph_codes = f.read()

# 遍历所有定义的范围
for start, end in ranges:
    for code in range(start, end + 1):
        try:
            glyph = chr(code)
            glyph_codes += glyph
        except:
            # 某些码点可能无效或未定义，跳过这些码点
            continue

# 将拼接的字形码写入本地文件
with open("comprehensive_symbols.txt", "w", encoding="utf-8") as file:
    file.write(glyph_codes)

print("各种特殊符号已写入 comprehensive_symbols.txt 文件")
