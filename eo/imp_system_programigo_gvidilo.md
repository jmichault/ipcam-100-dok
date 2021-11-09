---
lang: eo
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Programado gvidas  _IMP_'
---


La dokumentado de APIs povas esti vidata ĉi tie:  
* [ originala versio en la ĉina ](../../zh/includes.zh/html/) 

* [ angla ](../../en/includes.en/html/) 

* [ franca versio tradukita de Google ](../../fr/includes.fr/html/) 



# _IMP_  \( _Ingenic Media Platform_ \)  \( Vidu  _imp\_system.h_ \)

## bazaj konceptoj
La programado T20 / T21 baziĝas sur la sekvaj konceptoj: 
 1. Aparato  \( = _Device_ \)   
     La aparato kompletigas funkcion. Ekzemploj: 
      *   _Framesource_ : kompletigu la eligon de videodatenoj. 
      *   _Encoder_ : kompletigu la videokodigon aŭ bildkodigan funkcion. 
 2. Grupo  \( = _Group_ \)   
    La grupo estas la plej malgranda datum-eniga unuo. Aparato povas havi plurajn grupojn kaj ĉiu grupo povas ricevi nur unu datuman enigan kanalon. La grupo povas havi plurajn rezultojn.  
     La grupo ankaŭ estas ujo por specifaj  " funkcioj ". Vidu la klarigon en la kanala sekcio por pliaj detaloj. 
 3. Eligo  \( = _Output_ \)   
     La eligo estas la plej malgranda datuma eliga unuo por grupo.   
     La kanalo kutime rilatas al unu sola funkcia unuo.   
    Ekzemple:  
     -  Por la kodilo, kanalo kompletigas la  _H264_  aŭ koda funkcio  _JPEG_. 

     -  Por  _IVS_, kanalo kompletigas la funkcion de specifa algoritmo kaj la specifaj algoritmaj tipaj parametroj estas specifitaj dum kreado de la  kanalo

     -  Por _OSD_, estas regiono simila al  _Channel_, regiono estas specifa supermetita areo, kiu povas esti pinto  \( bildo \) kovrilo  \( okludo \), ktp. 

     -  Por  _FrameSource_, kanalo produktas originalan bildon kaj la kanalon  _FrameSource_  estas fakte grupo 

    
      La kanalo, kiel funkcia unuo, kutime estu konservita en la grupo  \( krom  _FrameSource_ \) ricevi datumojn. 

    La nombro de kanaloj, kiuj povas esti registritaj de la grupo de diversaj aparatoj, estas ankaŭ malsama.

## Modulo-ligilo  \( _Bind_ \)

Post kiam du grupoj estas ligitaj per  _Bind_, datumoj de la fonta grupo aŭtomate sendos al la celloko.   
Ekde la grupo estas la plej malgranda datuma eniga unuo kaj la eligo estas la plej malgranda datuma eliga unuo, la  _deviceID_,  _groupID_  kaj  _outputID_   _srcCell_  en la du parametroj de  _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_  estas validaj.   

Dum  _dstCell_  estas nur valida por  _deviceID_  kaj  _groupID_,  _outputID_  ne havas sencon kiel enirejo de datumoj. 

Ekzemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Rezulto:   
* realiĝas grupo, kiu generas ligon de FrameSource al Encoder.

* Du kanaloj estas registritaj en Encoder Group, do Encoder Group havas du produktojn:  _H264_  kaj  _JPEG_. 


Ekzemplo 2:
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
Apliki estas tipa apliko  _Bind_ : du-kanala kodo. 

Notoj: 
 *  Estas rekomendite, ke ĉiuj ligaj operacioj estas faritaj kiam inicializado de la sistemo. 

## Funkcioj

### _int IMP\_System\_Init \(void \)_
Komenco de la sistemo  _IMP_. 
### _int IMP\_System\_Exit \(void\)_

Post voki ĉi tiun funkcion, la tuta memoro kaj  _handles_  _IMP_  estos publikigitaj, kaj la aparataro-unuo estos fermita. 

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_

Akiru la tempokampon de la sistemo  _IMP_  en mikrosekundoj.   
Reveno: tempo en mikrosekundoj.

### _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_
Difini la sistemon Timestamp  _IMP_  en mikrosekundoj.   
Reveno: 0 se sukcesas.

### _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_

Legu la valoron de 32-bita registro.  

### _void IMP\_System\_WriteReg32 \(uint32_ t regaddr, valoro uint32 _t\)_
Skribu la valoron en la 32-bita registro. 

Noto: Bonvolu telefoni al ĉi tiu API zorge kaj kontroli la signifon de la registro, alie ĝi povas kaŭzi sistemajn erarojn.

### _int IMP_ System _GetVersion \(IMPVersion * pstVersion\)_

Akiru la numeron de la sistemo  _IMP_. 

### _const char * IMP_ sistemo _GetCPUInfo \(void\)_
Akiru informojn pri la CPU-modelo.  
Noto: La revenvaloro estas ĉeno de CPU-modelo, ekzemple, por T10 ekzistas "T10"kaj "T10-Lite".

### _int IMP_ sistemo  \(

Ligo inter fonta ĉelo kaj celloko.

Noto 1: Laŭ la konceptoj de Aparato, Grupo kaj Eligo, ĉiu aparato povas havi plurajn grupojn, kaj ĉiu grupo povas havi plurajn elirojn, Grupo estas uzata kiel Aparata eniga interfaco, kaj Eliro estas uzata kiel Aparata produkta interfaco. Tial la ligo fakte konektas certan eliron de la eliga aparato al certa Grupo de la eniga aparato.

Noto 2: Post sukcesa ligo, la datumoj generitaj de  _srcCell_  ( eligo )  estos aŭtomate transdonitaj al la celloko  ( Grupo ). 

### _int IMP_ sistemo  \(
Malgrupigu la fontajn kaj cellokojn. 

### _int IMP_ sistemo  \(

Rekuperas informojn de la fonta ĉelo rilate al la celloko.

