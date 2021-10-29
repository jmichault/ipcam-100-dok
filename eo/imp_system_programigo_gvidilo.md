---
lang: eo
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: IMP-Programado-Gvidilo
---


La dokumentado de APIs povas esti vidata ĉi tie:  
* [originala versio en la ĉina](../../zh/includes.zh/html/)

* [Angla versio](../../en/includes.en/html/)

* (° 1 ° 1 ° franca versio Tradukita per google](../../fr/includes.fr/html/)



# IMP (Ingenic Media Platform) (vidu imp_system.h)

## bazaj konceptoj
Programado T20 / T21 baziĝas sur jenaj konceptoj:
1. Periferia (= Aparato)  
    La ekstercentra kompletigas funkcion. Ekzemploj:
     *  Frama fonto: finas la eliron de videodatenoj.
     *  Kodilo: kompletigas la videokodan aŭ bildan kodan funkcion.
2. Grupo  
    La grupo estas la plej malgranda datum-eniga unuo. Aparato povas havi plurajn grupojn kaj ĉiu grupo povas ricevi nur unu datuman enigan kanalon. La grupo povas havi plurajn rezultojn.  
    La grupo ankaŭ estas ujo por specifaj "funkcioj". Vidu la klarigon en la kanala sekcio por pliaj detaloj.
3. Eliro  
    La eligo estas la plej malgranda unuo de datuma eligo por grupo. Grupo povas havi plurajn elirojn kaj ĉiu eligo povas produkti nur unu datuman kanalon.
4. Ĉelo  
    La ĉelo rilatas al kolekto enhavanta informojn pri la aparato, la grupo kaj la eligo. Ĝi estas prezentita en la datuma strukturo de IMPCell.
La ĉelo estas ĉefe uzata por Bind (@ref bind). Laŭ la difino de Aparato, Grupo kaj Eligo, Eligo estas la nodo por datuma eligo kaj Grupo estas la nodo por datuma enigo.
En Bind, la ĉela indekso de la datuma eliga nodo estas ĉe la Eliga eligo, kaj la ĉela indekso de la datuma eniga nodo estas ĉe la eniga grupo (de tiel ke la Ĉelo, Eliga datuma eniro estas sensenca valoro).
5. Kanalo  
    La kanalo ĝenerale rilatas al unuo kun ununura funkcio. La kanalo ricevas specifan funkcion kiam ĝi estas kreita (instantiation).  
    Ekzemple:  
     -  Por la kodilo, unu kanalo kompletigas la kodon H264 aŭ kodan funkcion JPEG. La specifa kodiga funkcio (tipo, parametro) estas specifita kiam oni kreas la kanalon

     -  Por IVS, kanalo kompletigas la funkcion de specifa algoritmo kaj specifaj algoritmaj tipparametroj estas specifitaj dum kreado de la kanalo

     -  Por OSD, ekzistas regiono simila al Kanalo, regiono estas specifa supermetita areo, kiu povas esti PIC (bildo), KOVRILO (fermado), ktp.

     -  Por FrameSource, kanalo produktas originalan bildon kaj la FrameSource-kanalo fakte estas grupo

     
     La kanalo, kiel funkcia unuo, devas ĝenerale esti registrita en la grupo (krom FrameSource) por ricevi datumojn. Post kiam la kanalo estas registrita en la grupo, ĝi ricevos la datumojn enigitajn de la grupo.

    La nombro de kanaloj, kiuj povas esti registritaj de la grupo de diversaj aparatoj, estas ankaŭ malsama.

## Moduloj ligantaj (Bind)

Post kiam du grupoj estas konektitaj de Bind, la datumoj de la fonta grupo aŭtomate estos senditaj al la celloka grupo.  
Ĉar la grupo estas la plej malgranda eniga unuo de datumoj kaj la eligo estas la plej malgranda unuo de datuma eligo, la aparatoID, groupID kaj outputID de srcCell en ambaŭ parametroj de IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) validas.  

Dum dstCell validas nur por deviceID kaj groupID, outputID ne havas sencon kiel datuma eniro.

Ekzemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* realiĝas grupo, kiu generas ligon de FrameSource al Encoder.

* Du kanaloj estas registritaj en Encoder Group, do Encoder Group havas du elirojn H264 kaj JPEG.


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
Ĉi tio estas tipa programo Bind: du-kanala koda fluo.
 * FrameSource havas du elirojn, nome la ĉefa rivereto Channel0 (1280x720) kaj la sklava rivereto Channel1 (640x360).
   *   Ĉefa rivereto: Channel0 Bind OSD Group.0 de FrameSource, OSD Group.0 Bind Encoder Group.0. Inter ili: 
       * OSD-Grupo.0 registris du regionojn, kiuj estas uzataj por montri informojn pri tempostampo kaj signoŝnuro respektive
       * Kodigila Grupo .0 registris du kanalojn. , kiuj estas kodado H264 kaj kodado JPEG respektive. Inter ili, se la bilda grandeco de la koda kanalo JPEG ne egalas al la eniga parametro (Kanalo0 de FrameSource), tiam ĝi estos skalita (programaro ĉe T10) ) atingi la celon kapti ĉe iu ajn rezolucio.
       
Notoj:
* oni rekomendas, ke ĉiuj ligaj operacioj estu faritaj dum sistemo-inicialigo.
* Operacioj Bind kaj UnBind ne povas esti nomataj dinamike post kiam _FrameSource_ estas aktivigita. UnBind fariĝas nur post malaktivigo _FrameSource_.

## Funkcioj

### int IMP\_Sistemo\_Init (malplena )
Inicialigo de la IMP-sistemo.
redonas 0 se ĝi sukcesas.
Post ĉi tiu API-alvoko, la baza datuma strukturo estos pravalorizita, sed la aparataro ne estos pravalorizita.
atento: Ĉi tiu funkcio devas esti alvokita por komencigo antaŭ iu ajn alia operacio.
### int IMP_System_Elirejo (malplena)

Post vokado de ĉi tiu funkcio, ĉiu memoro kaj IMP _handles_ estos liberigitaj, kaj la aparataro estos fermita. 
Noto: Post voki ĉi tiun API, se vi volas uzi IMP denove, vi devas reagordi la IMP-sistemon.

### int64_t IMP_Sistemo_GetTimeStamp (void)

Akiru la IMP-sisteman tempostampon en mikrosekundoj.  
Reveno: tempo en mikrosekundoj.

### int IMP_System_RebaseTimeStamp (bazoj int64_t)
Agordu la tempan markon de la sistemo IMP en mikrosekundoj.  
Reveno: 0 se sukcesas.

### uint32_t IMP_Sistemo_ReadReg32 (uint32_t u32Addr)

Legu la valoron de 32-bita registro.  

### malplena IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Skribu la valoron al la 32-bita registro.

Noto: Bonvolu telefoni al ĉi tiu API zorge kaj kontroli la signifon de la registro, alie ĝi povas kaŭzi sistemajn erarojn.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Akiru la versian numeron de la IMP-sistemo.

### const char * IMP_System_GetCPUInfo (malplena)
Akiru informojn pri la CPU-modelo.  
Noto: La revenvaloro estas ĉeno de CPU-modelo, ekzemple, por T10 ekzistas "T10"kaj "T10-Lite".

### int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)

Ligo inter fonta ĉelo kaj celloko.

Noto 1: Laŭ la konceptoj de Aparato, Grupo kaj Eligo, ĉiu aparato povas havi plurajn grupojn, kaj ĉiu grupo povas havi plurajn elirojn, Grupo estas uzata kiel Aparata eniga interfaco, kaj Eliro estas uzata kiel Aparata produkta interfaco. Tial la ligo fakte konektas certan eliron de la eliga aparato al certa Grupo de la eniga aparato.

Noto 2: Post sukcesa ligilo, la datumoj generitaj de srcCell (Eliro) estos aŭtomate transdonitaj al la celloka Ĉela (Grupo).

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Malgrupigu la fontajn kaj cellokojn. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Rekuperas informojn de la fonta ĉelo rilate al la celloko.




