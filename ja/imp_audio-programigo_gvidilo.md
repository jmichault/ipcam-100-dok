---
lang: ja
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: サウンドプログラミングガイド
---

# imp  _Audio \(voir imp_  audio.h  \)

録音と再生、オーディオコーデック、音量とゲインの設定、エコーキャンセレーション、自動ゲイン、その他の機能を含むオーディオモジュール。

## プレゼンテーション
* サウンド機能には、オーディオ入力、オーディオ出力、オーディオキャンセル、オーディオエンコーディング、オーディオデコーディングの5つのモジュールが含まれています。


 * その中で、オーディオ入力とオーディオ出力には、デバイスとチャネルの概念があります。 MICの1つはデバイスと見なされ、MICは複数のチャネル入力を持つことができます。


 * 同じSPKはブリーディングデバイスと見なされ、SPKは複数のチャネル出力を持つこともできます。


 * 月版のオーディオAPIは、デバイスごとに1つのチャネルのみをサポートします。


 * エコーキャンセルはオーディオ入力インターフェースにあり、特定の指示が機能の説明に反映されています。


 * オーディオエンコーディング：現在のオーディオAPIは、PT_G711A, PT_G711UおよびPT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   形式のオーディオエンコーディングをサポートしています。

   

 * オーディオデコード：現在のオーディオAPIは、PT_G711A, PT_G711UおよびPT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   形式のオーディオデコードをサポートしています

   

