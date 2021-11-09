---
lang: it
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Guida alla programmazione   _IMP_'
---


La documentazione di Apis può essere vista qui:   
* [  versione originale in cinese  ](../../zh/includes.zh/html/)  


* [  English  ](../../en/includes.en/html/)  


* [  Versione francese Tradotto da Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( Vedi   _imp\_system.h_  \)

## concetti basilari
Il programma T20 / T21 si basa sui seguenti concetti:  
 1. Dispositivo   \( =  _Device_  \)    
 Il dispositivo completa la funzione. Esempi:  
       *    _Framesource_ : Completa l'uscita dei video clip.  
       *    _Encoder_ : Completa il codice video o la funzione del codice immagine.  
 2. Gruppo   \( =  _Group_  \)    
 Il gruppo è la più piccola unità di ingresso dati. Un dispositivo può avere più gruppi e ciascun gruppo può ricevere un solo canale di ingresso dati. Il gruppo può avere diversi risultati. .  
      Il gruppo è anche un contenitore per le funzioni specifiche   "  ". Vedere la spiegazione nella sezione del canale per maggiori dettagli.  
 3. Eligo   \( =  _Output_  \)    
 L'uscita è l'unità di uscita dei dati più piccola per gruppo.    
 Il canale è solitamente correlato a un'unica unità funzionale.    
 Ad esempio:   
     -  Per il codice, il canale completa la funzione   _H264_   o codice   _JPEG_. . 


     -  Per   _IVS_, un canale completa la funzione di un algoritmo specifico e gli specifici parametri tipici dell'algoritmo sono specificati durante la creazione del canale 


     -  Per  _OSD_, c'è una regione simile a   _Channel_, una regione è una specifica area superMetata che può essere un top   \( immagine  \) coperchio   \( occlusione  \), ecc. . 


     -  Per   _FrameSource_, un canale produce un'immagine originale e il canale   _FrameSource_   è in realtà un gruppo  


    
       Il canale, come unità funzionale, di solito viene conservato nel gruppo   \( tranne   _FrameSource_  \) Ricevi dati. . 

    Anche il numero di canali che possono essere registrati dal gruppo di vari dispositivi è diverso.

## Link del modulo   \(  _Bind_  \)

Dopo due gruppi sono collegati da   _Bind_, i dati dal gruppo sorgente invieranno automaticamente alla destinazione.    
 Poiché il gruppo è l'unità di ingresso dei dati più piccola e l'uscita è la più piccola unità di uscita dei dati,   _deviceID_,   _groupID_   e   _outputID_    _srcCell_   nei due parametri di   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   sono validi. .   

Mentre   _dstCell_   è valido solo per   _deviceID_   e   _groupID_,   _outputID_   non ha senso come l'ingresso dei dati. . 

Esempio 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Risultato:    
 *  Un gruppo genera un gruppo che genera un collegamento da framesource all'encoder. .

* Due canali sono registrati nel gruppo encoder, quindi il Gruppo Encoder ha due prodotti:   _H264_   e   _JPEG_. . 



Esempio 2:
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
Applica è un'applicazione tipica   _Bind_ : codice a due canali. . 

Note:  
  *   Si consiglia di effettuare tutte le operazioni di collegamento durante l'inizializzazione del sistema. . 

## Funzioni

### _int IMP\_System\_Init \(void \)_.
Inizio del sistema   _IMP_. . 
### Inizio del sistema _int IMP\_System\_Exit \(void\)_. \_.

Dopo aver chiamato questa funzione, verrà rilasciata tutte le memoria e   _handles_   _IMP_   e l'unità hardware sarà chiusa. . 

### Dopo aver chiamato questa funzione, verrà rilasciata tutte le memoria e _int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_ e l'unità hardware sarà chiusa.  \(.

Ottieni il campo Tempi del sistema   _IMP_   in microsecondi.    
 ritorno: tempo in microecondi. .

### Ottieni il campo Tempi del sistema _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ in microsecondi. \_ ritorno: tempo in microecondi.  \(.
Definire il sistema Timestamp   _IMP_   in microsecondi.    
 ritorno: 0 se ha successo. .

### Definire il sistema Timestamp _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ in microsecondi. \_ ritorno: 0 se ha successo. \_.

Leggi il valore di un registro a 32 bit.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regadddr, valore UINT32  _t\)_
Scrivi il valore nel registro a 32 bit. . 

Nota: chiama attentamente questa API e controlla il significato del registro, altrimenti potrebbe causare errori di sistema.

### _int IMP_  Sistema  _GetVersion \(IMPVersion * pstVersion\)_

Ottieni il sistema del sistema   _IMP_. . 

### _const char * IMP_  Sistema  _GetCPUInfo \(void\)_
Ottieni informazioni sul modello di CPU.  
Nota: il valore restituito è una stringa del modello di CPU, ad esempio, per T10 sono presenti "T10"e "T10-Lite".

### _int IMP_  Sistema   \(

Collegamento tra cella di origine e destinazione.

Nota 1: in base ai concetti di dispositivo, gruppo e output, ogni dispositivo può avere diversi gruppi e ogni gruppo può avere diverse uscite, il gruppo viene utilizzato come interfaccia di input del dispositivo e l'output viene utilizzato come interfaccia del prodotto del dispositivo. Pertanto il collegamento collega effettivamente una certa uscita del dispositivo di output a un certo Gruppo del dispositivo di input.

Nota 2: Dopo un collegamento di successo, i dati generati da   _srcCell_   (  Eligo  )   verranno trasferiti automaticamente alla destinazione   (  Gruppo  ). . 

### _int IMP_  Sistema   \(
Separa le origini e le destinazioni. 

### _int IMP_  Sistema   \(

Recupera le informazioni dalla cella di origine relativa alla destinazione.

