---
lang: zh
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 实心编程指南
---

# IMP_Audio (voir imp_音频.h)

音频模块，包括记录和回放，音频编解码器，音量和增益设置，回声消除，自动增益等功能。

## 介绍
* 声音功能包括5个模块：音频输入，音频输出，音频消除，音频编码和音频解码。


 * 其中，音频输入和音频输出具有设备和通道的概念。 MIC之一被视为设备，并且MIC可以具有多个通道输入。


 * 相同的SPK被视为繁殖设备，并且SPK也可以具有多个通道输出。


 * 音频API的农历版本每个设备仅支持一个频道。


 * 在音频输入界面中可以找到回声消除功能，具体说明会反映在功能说明中。


 * 音频编码：当前的音频API支持PT_G711A, PT_G711U和PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   格式的音频编码

   

 * 音频解码：当前的音频API支持PT_G711A, PT_G711U和PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   格式的音频解码

   

