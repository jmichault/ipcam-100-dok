---
lang: ja
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: IMPプログラミングガイド
---


APIのドキュメンテーションはここで見ることができます：（°1°1  
* [中国語](../../zh/includes.zh/html/)のオリジナルバージョン


* [英語版](../../en/includes.en/html/)


* （°1°1°1°1°1°1°フレンチバージョンGoogle](../../fr/includes.fr/html/)




# IMP (Ingenic Media Platform) (imp_system.h)を参照

## 基本概念
T20 / T21プログラミングは、次の概念に基づいています。
1。周辺機器 (=デバイス)  
    周辺機器が機能を完了します。例：
     *  フレームソース：ビデオデータの出力を終了します。
     *  エンコーダー：ビデオエンコードまたは画像エンコード機能を完了します。
2。グループ  
    グループは最小のデータ入力ユニットです。デバイスは複数のグループを持つことができ、各グループは1つのデータ入力チャネルのみを受信できます。グループはいくつかの結果を得ることができます。  
    このグループは、特定の "機能"のコンテナーでもあります。詳細については、チャネルセクションの説明を参照してください。
3。終了  
    出力は、グループごとのデータ出力の最小単位です。グループは複数の出力を持つことができ、各出力は1つのデータチャネルのみを生成できます。
4。セル  
    セルは、デバイス、グループ、および出力に関する情報を含むコレクションを指します。これは、IMPCellデータ構造で表示されます。
セルは主にバインド (@refバインド)に使用されます。デバイス、グループ、出力の定義によれば、出力はデータ出力のノードであり、グループはデータ入力のノードです。
バインドでは、データ出力ノードのセルインデックスは出力出力にあり、データ入力ノードのセルインデックスは入力グループ (にあるため、セル、出力データ入力は無意味な値)。
5。チャネル  
    チャネルは通常、単一の機能を備えたユニットを指します。チャネルは、作成時 (のインスタンス化)時に特定の機能を受け取ります。  
    例：  
     -  エンコーダの場合、1つのチャネルがH264コードまたはJPEGエンコーディング機能を補完します。チャネルの作成時に、特定のエンコード機能 (タイプ、パラメーター) が指定されます


     -  IVSの場合、チャネルは特定のアルゴリズムの機能を完了し、チャネルの作成時に特定のアルゴリズムタイプのパラメーターが指定されます


     -  OSDの場合、チャネルに類似した領域があり、領域は特定のオーバーレイ領域であり、PIC (画像)、カバー (クロージャー)などがあります。 。


     -  FrameSourceの場合、チャネルは元の画像を生成し、FrameSourceチャネルは実際にはグループです


     
     データを受信するには、機能単位としてのチャネルは、通常、FrameSource) に加えてグループ (に登録する必要があります。チャネルがグループに登録されると、グループによって入力されたデータを受信します。

    さまざまなデバイスのグループによって記録できるチャネルの数も異なります。

## バインディングモジュール (バインド)

2つのグループがバインドによって接続されると、ソースグループからのデータが宛先グループに自動的に送信されます。  
グループが最小のデータ入力ユニットであり、出力が最小のデータ出力ユニットであるため、IMP_System_バインド (IMPCell * の両方のパラメーターでのsrcCellのdeviceID、groupID、およびoutputID srcCell、IMPCell * dstCell) が有効です。  

dstCellはdeviceIDとgroupIDに対してのみ有効ですが、outputIDはデータ入力としては意味がありません。

例1： 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* FrameSourceからEncoderへのリンクを生成するグループが生成されます。


* エンコーダグループには2つのチャネルが記録されるため、エンコーダグループにはH264とJPEGの2つの出力があります。



例2：
```
// flux de données principal
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};
IMPCell osd_grp0 = {DEV_ID_OSD, 0, 0};
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0};
int ret = IMP_System_Bind(&fs_chn0, &osd_grp0);
if (ret < 0)
    printf("Bind FrameSource Channel0 and OSD Group0 failed\n");

int ret = IMP_System_Bind(&osd_grp0, &enc_grp0);
if (ret < 0)
    printf("Bind OSD Group0 and Encoder Group0 failed\n");

// flux de données lié 
IMPCell fs_chn1_output0 = {DEV_ID_FS, 1, 0};
IMPCell ivs_grp0 = {DEV_ID_IVS, 0, 0};
IMPCell osd_grp1 = {DEV_ID_OSD, 1, 0};
IMPCell enc_grp1 = {DEV_ID_ENC, 1, 0};

int ret = IMP_System_Bind(&fs_chn1_output0, &ivs_grp0);
if (ret < 0)
    printf("Bind FrameSource Channel1 and IVS Group0 failed\n");

int ret = IMP_System_Bind(&ivs_grp0, &osd_grp1);
if (ret < 0)
    printf("Bind IVS Group0 and OSD Group1 failed\n");

int ret = IMP_System_Bind(&osd_grp1, &enc_grp1);
if (ret < 0)
    printf("Bind OSD Group1 and Encoder Group1 failed\n");
```
これは典型的なバインドプログラムです：2チャンネルのコードストリーム。
 * FrameSourceには、メインストリームChannel0 (1280x720) とスレーブストリームChannel1 (640x360)の2つの出力があります。
   *   メインストリーム：FrameSourceのChannel0 Bind OSD Group.0、OSD Group.0 Bind EncoderGroup.0。その中で： 
       * OSD Group.0は、タイムスタンプと文字列情報をそれぞれ表示するために使用される2つの領域を記録しました
       * エンコーダーグループ.0は2つのチャネルを記録しました。 、それぞれH264エンコーディングとJPEGエンコーディングです。その中で、JPEGエンコーディングチャネルの画像サイズがFrameSource Channel0)の入力パラメータ (と一致しない場合、T10) でソフトウェアでスケーリング (されます) 任意の解像度でキャプチャするという目標を達成します。
       
注：
* すべてのリンク操作は、システムの初期化中に実行することをお勧めします。
*  _FrameSource_ がアクティブ化された後、バインドおよびバインド解除操作を動的に呼び出すことはできません。バインド解除は、非アクティブ化 _FrameSource_後にのみ実行されます。

## 機能

### int IMP\_システム\_初期化 (空 )
IMPシステムの初期化。
成功した​​場合は0を返します。
このAPI呼び出しの後、基本的なデータ構造は初期化されますが、ハードウェアは初期化されません。
注意：この関数は、他の操作の前に開始するために呼び出す必要があります。
### int IMP_System_出口 (空)

この関数を呼び出すと、すべてのメモリとIMP _handles_ が解放され、ハードウェアがシャットダウンされます。 
注：このAPIを呼び出した後、IMPを再度使用する場合は、IMPシステムをリセットする必要があります。

### int64_t IMP_システム_GetTimeStamp (void)

IMPシステムのタイムスタンプをマイクロ秒単位で取得します。  
戻り値：マイクロ秒単位の時間。

### int IMP_System_RebaseTimeStamp (bases int64_t)
IMPシステムのタイムスタンプをマイクロ秒単位で設定します。  
成功した場合は0を返します。

### uint32_t IMP_システム_ReadReg32 (uint32_t u32Addr)

32ビットレジスタの値を読み取ります。  

### ブランクIMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
値を32ビットレジスタに書き込みます。

注：このAPIを注意深く呼び出し、レジストリの意味を確認してください。そうしないと、システムエラーが発生する可能性があります。

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

IMPシステムのバージョン番号を取得します。

### const char * IMP_System_GetCPUInfo (空)
CPUモデルに関する情報を取得します。  
注：戻り値はCPUモデルの文字列です。たとえば、T10の場合、 "T10"および "T10-Lite"があります。

### int IMP_System_バインド (IMPCell * srcCell、IMPCell * dstCell)

ソースセルと宛先の間のリンク。

注1：デバイス、グループ、出力の概念によれば、各デバイスは複数のグループを持つことができ、各グループは複数の出力を持つことができ、グループはデバイス入力インターフェイスとして使用され、出力はデバイス製品インターフェイスとして使用されます。したがって、リンクは実際には、出力デバイスの特定の出力を入力デバイスの特定のグループに接続します。

注2：リンクが成功すると、srcCell (出力) によって生成されたデータは、宛先セル (グループ)に自動的に送信されます。

### int IMP_System_UnBind (IMPCell * srcCell、IMPCell * dstCell)
ソースと宛先のグループ化を解除します。 

### int IMP_System_GetBindbyDest (IMPCell * dstCell、IMPCell * srcCell)

宛先に関連するソースセルから情報を取得します。




