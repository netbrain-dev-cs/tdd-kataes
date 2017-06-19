# TddKatas
测试驱动开发实践，katas for test drive development

#soundex 练习
百度百科：http://baike.baidu.com/link?url=K1FzBIVBMwFF_S_T3PaJ0ijDe0JuwusFsVh0TIQZ4a16CdlyMUbpf6trEwOo6nYYDwG_GqucPcp13pUaNXPTra
维基百科：https://zh.wikipedia.org/wiki/Soundex

Soundex[编辑]
维基百科，自由的百科全书
Soundex是一种语音算法，利用英文字的读音计算近似值，值由四个字符构成，第一个字符为英文字母，后三个为数字。在拼音文字中有时会有会念但不能拼出正确字的情形，可用Soundex做类似模糊匹配的效果。例如Knuth和Kant二个字符串，它们的Soundex值都是“K530”。其在电脑大师高德纳名著《计算机程序设计艺术》都有详细的介绍。
算法简要说明[编辑]
将英文字按以下规则替换（除第一个字符外）：
   a e h i o u w y -> 0
   b f p v -> 1
   c g j k q s x z -> 2
   d t -> 3
   l -> 4
   m n -> 5
   r -> 6
去除0，对于重复的字符只保留一个
返回前4个字符，不足4位以0补足
以Knuth和Kant为例：
   Knuth -> K5030 -> K53 -> K530
   Kant  -> K053  -> K53 -> K530
外部链接[编辑]
The Soundex Indexing System (U.S. National Archives and Records Administration)
分类：语音学语音算法

# cpp
C++ code

# javascript

# java

# python