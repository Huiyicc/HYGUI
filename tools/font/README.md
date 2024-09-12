# 使用方案

当前目录下运行

```shell
pip install emoji
pip install fontTools
python dump_glyph.py
python simpfont.py
```
构建项目
将以下两个文件
```shell
src/resource/emoji_font_resource.h
src/resource/utils_font_resource.h
```
复制到`interior/include`内
重新构建项目