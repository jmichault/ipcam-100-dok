---
lang: de
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Programmierhandbuch   _IMP_'
---


APIs 'Dokumentation ist hier zu sehen:  
* [  Originalversion in Chinesisch  ](../../zh/includes.zh/html/)  


* [  Englisch  ](../../en/includes.en/html/)  


* [  Französische Version übersetzt von Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( siehe   _imp\_system.h_  \)

## grundlegendes Konzept
  
      Die Gruppe ist auch ein Container für bestimmte   " -Funktionen  ". Weitere Informationen finden Sie in der Erläuterung im Kanalbereich.  
 3. ELIGO   \( =  _Output_  \)    
 Der Ausgang ist die kleinste Datenausgabeeinheit pro Gruppe.    
 Der Kanal bezieht sich normalerweise auf eine einzige Funktionseinheit.    
 Zum Beispiel:   
     -   


     -  Für   _IVS_ schließt ein Kanal die Funktion eines bestimmten Algorithmus ab und der spezifische Algorithmus typische Parameter werden beim Erstellen des Kanals  angegeben


     -  Für  _OSD_ gibt es eine Region, die dem   _Channel_ ähnlich ist, ein Bereich ist ein spezifischer oberstetierter Bereich, der ein oberes   \( -V-Bild  \) ist   \( Okklusion  \) usw.  


     -   


    
       Der Kanal, als Funktionseinheit, normalerweise in der   \( -Gruppe aufbewahrt, außer   _FrameSource_  \) Empfangsdaten.  

    Die Anzahl der Kanäle, die von der Gruppe verschiedener Geräte aufgezeichnet werden können, ist ebenfalls unterschiedlich.

## Modulverbindung   \(  _Bind_  \)

Nachdem zwei Gruppen mit   _Bind_ verknüpft sind, senden Daten aus der Quellgruppe automatisch an das Ziel.    
 Da die Gruppe die kleinste Dateneingabeeinheit ist und der Ausgang die kleinste Datenausgabeinheit ist, ist der   _deviceID_,   _groupID_   und   _outputID_    _srcCell_   in den beiden Parametern von   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   gültig.    

 

Beispiel 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Ergebnis:    
 *  Eine Gruppe erzeugt eine Gruppe, die einen Link von FramesOurce zum Codierer erzeugt. 

*  



Beispiel 2:
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
 

 

## Funktionen

### _int IMP\_System\_Init \(void \)_
 
### _int IMP\_System\_Exit \(void\)_

 

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_

Holen Sie sich das Timing-Bereich des   _IMP_   -Systems in Mikrosekunden.    
 Rückkehr: Zeit in Mikrokunden. 

### Holen Sie sich das Timing-Bereich des _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ -Systems in Mikrosekunden. \_ Rückkehr: Zeit in Mikrokunden.  \(
Definieren Sie das Timestamp   _IMP_   -System in Mikrosekunden.    
 Rückgabe: 0, falls erfolgreich. 

### Definieren Sie das Timestamp _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ -System in Mikrosekunden. \_ Rückgabe: 0, falls erfolgreich. \_

Lesen Sie den Wert eines 32-Bit-Registers.  

### _void IMP\_System\_WriteReg32 \(uint32_  T REGADDR, Wert UINT32  _t\)_
 

Hinweis: Rufen Sie diese API sorgfältig auf und überprüfen Sie die Bedeutung der Registrierung. Andernfalls kann es zu Systemfehlern kommen.

### _int IMP_  System  _GetVersion \(IMPVersion * pstVersion\)_

 

### _const char * IMP_  System  _GetCPUInfo \(void\)_
Informationen zum CPU-Modell abrufen.  
Hinweis: Der Rückgabewert ist eine Zeichenfolge des CPU-Modells. Für T10 gibt es beispielsweise "T10"und "T10-Lite".

### _int IMP_  System   \(

Verbindung zwischen Quellzelle und Ziel.

Hinweis 1: Gemäß den Konzepten von Gerät, Gruppe und Ausgabe kann jedes Gerät mehrere Gruppen und jede Gruppe mehrere Ausgänge haben. Die Gruppe wird als Geräteeingabeschnittstelle und die Ausgabe als Geräteproduktschnittstelle verwendet. Daher verbindet die Verbindung tatsächlich einen bestimmten Ausgang des Ausgabegeräts mit einer bestimmten Gruppe des Eingabegeräts.

 

### _int IMP_  System   \(
Gruppieren Sie die Quellen und Ziele auf. 

### _int IMP_  System   \(

Ruft Informationen aus der Quellzelle ab, die sich auf das Ziel beziehen.

