---
lang: ja
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'プログラミングガイド  _IMP_'
---


APIのドキュメンテーションがここで見ることができます：  
* [ 中国語 ](../../zh/includes.zh/html/)  


* [ 英語 ](../../en/includes.en/html/)  


* [ フランス語版Google  ](../../fr/includes.fr/html/)  




# _IMP_   \( \)   \(   _imp\_system.h_  \)を参照してください。

## 基本概念
T20 / T21プログラムは、次の概念に基づいています。 
 1.デバイス  \( =  _Device_  \)    
デバイスは機能を完了します。例： 
       *    _Framesource_ ：ビデオクリップの出力を完成させます。  
       *    _Encoder_ ：ビデオコードまたは画像コード機能を完成させます。  
 2.グループ  \( =  _Group_  \)    
グループは最小のデータ入力部です。デバイスは複数のグループを持つことができ、各グループは1つのデータ入力チャネルのみを受信できます。グループにはいくつかの結果があります。   
     群は、特異的  "機能 "の容器でもある。詳細については、チャネルセクションの説明を参照してください。  
 3. ELIGO   \( =  _Output_  \)    
出力はグループ当たりの最小のデータ出力部です。    
チャネルは通常、単一の機能ユニットに関連しています。    
例：  
     -  Codelの場合、チャネルは  _H264_  またはコード関数  _JPEG_を完成させます。  


     -    _IVS_の場合、チャネルは特定のアルゴリズムの関数を完成させ、特定のアルゴリズムの典型的なパラメータはチャネルの作成中に指定されます。


     -   _OSD_の場合、  _Channel_と同様の領域があり、領域は上位  \(画像 \)カバー  \(閉塞 \)などであり得る特定の超高速領域である。  


     -    _FrameSource_の場合、チャネルは元の画像を生成し、チャネル  _FrameSource_  は実際にはグループです。 


    
      は、機能単位として、通常、  _FrameSource_  \)の受信データを除く  \(群に保存されている。  

    さまざまなデバイスのグループによって記録できるチャネルの数も異なります。

## モジュールリンク  \(  _Bind_  \)

2つのグループが  _Bind_でリンクされた後、ソースグループからのデータは自動的に宛先に送信されます。    
グループは最小のデータ入力部であり、出力は最小のデータ出力部であるため、  _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_  の2つのパラメータの  _deviceID_、  _groupID_  、_srcCell_  は有効です。    

  _dstCell_  は  _deviceID_  の場合にのみ有効ですが、  _groupID_はデータの入り口のように意味がありません。  

例1： 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
結果：   
 * グループは、フレームソースからエンコーダへのリンクを生成するグループを生成します。 

* エンコーダグループには2つのチャンネルが登録されているため、エンコーダグループには2つの製品があります。  _H264_  と  _JPEG_。  



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
適用は典型的なアプリケーション  _Bind_ ：2チャンネルコードです。  

注： 
  *  システムの初期化時にすべてのリンク操作が行われることをお勧めします。  

## 機能

### _int IMP\_System\_Init \(void \)_
  _IMP_システムの始まり。  
### _int IMP\_System\_Exit \(void\)_システムの始まり。 \_

この機能を呼び出した後、すべてのメモリと  _handles_   _IMP_  が解放され、ハードウェアユニットは閉じます。  

### この機能を呼び出した後、すべてのメモリと_int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_が解放され、ハードウェアユニットは閉じます。  \(

  _IMP_  システムのタイミングフィールドをマイクロ秒単位で取得します。    
 return：micro秒の時間。 

### _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_システムのタイミングフィールドをマイクロ秒単位で取得します。 \_ return：micro秒の時間。  \(
タイムスタンプ  _IMP_  システムをマイクロ秒単位で定義します。    
 return：0が成功した場合。 

### タイムスタンプ_uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_システムをマイクロ秒単位で定義します。 \_ return：0が成功した場合。 \_

32ビットレジスタの値を読み取ります。  

### _void IMP\_System\_WriteReg32 \(uint32_  T REGADDR、値UINT32  _t\)_
32ビットレジスタに値を書き込みます。  

注：このAPIを注意深く呼び出し、レジストリの意味を確認してください。そうしないと、システムエラーが発生する可能性があります。

### _int IMP_ システム _GetVersion \(IMPVersion * pstVersion\)_

  _IMP_システムのシステムを取得します。  

### _const char * IMP_ システム _GetCPUInfo \(void\)_
CPUモデルに関する情報を取得します。  
注：戻り値はCPUモデルの文字列です。たとえば、T10の場合、 "T10"および "T10-Lite"があります。

### _int IMP_ システム  \(

ソースセルと宛先の間のリンク。

注1：デバイス、グループ、出力の概念によれば、各デバイスは複数のグループを持つことができ、各グループは複数の出力を持つことができ、グループはデバイス入力インターフェイスとして使用され、出力はデバイス製品インターフェイスとして使用されます。したがって、リンクは実際には、出力デバイスの特定の出力を入力デバイスの特定のグループに接続します。

注2：リンクが成功した後、  _srcCell_   (  ELIGO  )  で生成されたデータは自動的に宛先  ( グループ )に転送されます。  

### _int IMP_ システム  \(
ソースと宛先のグループ化を解除します。 

### _int IMP_ システム  \(

宛先に関連するソースセルから情報を取得します。

