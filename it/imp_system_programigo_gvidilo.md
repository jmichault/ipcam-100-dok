

# IMP (Ingenic Media Platform) (vedi imp_system.h)

## concetti basilari
La programmazione di T20 / T21 si basa sui seguenti concetti:
1. Periferica (= Dispositivo)  
    La periferica completa una funzione. Esempi:
     *  Sorgente fotogramma: termina l'uscita dei dati video.
     *  Encoder: completa la funzione di codifica video o codifica immagine.
2. Gruppo  
    Il gruppo è la più piccola unità di input dati. Un dispositivo può avere diversi gruppi e ogni gruppo può ricevere un solo canale di input dati. Il gruppo può avere diversi risultati.  
    Il gruppo è anche contenitore per specifiche "funzioni". Vedere la spiegazione nella sezione del canale per maggiori dettagli.
3. Uscita  
    L'output è la più piccola unità di dati in uscita per gruppo. Un gruppo può avere più uscite e ciascuna uscita può produrre un solo canale dati.
4. Cella  
    La cella si riferisce a una raccolta contenente informazioni sul dispositivo, sul gruppo e sull'output. È presentato nella struttura dati IMPCell.
La cella viene utilizzata principalmente per Bind (@ref bind). Secondo la definizione di dispositivo, gruppo e output, Output è il nodo per l'output dei dati e Group è il nodo per l'input dei dati.
In Bind, l'indice della cella del nodo di output dei dati si trova nell'output di output e l'indice della cella del nodo di input dei dati si trova nel gruppo di input (in modo che la cella, input dei dati di output sia un valore senza senso).
5. Canale  
    Il canale si riferisce generalmente ad una unità con una sola funzione. Il canale riceve una funzione specifica quando viene creata (istanziazione).  
    Ad esempio:  
     -  Per l'encoder, un canale completa il codice H264 o la funzione di codifica JPEG. Il tipo di funzione di codifica specifica (, il parametro) viene specificato durante la creazione del canale


     -  Per IVS, un canale completa la funzione di un algoritmo specifico e vengono specificati parametri di tipo algoritmico specifici durante la creazione del canale


     -  Per OSD, esiste una regione simile a Canale, la regione è un'area di sovrapposizione specifica, che può essere immagine PIC (), chiusura COPERCHIO ()e così via .


     -  Per FrameSource, un canale produce un'immagine originale e il canale FrameSource è in realtà un gruppo


     
     Il canale, come unità funzionale, deve essere generalmente registrato nel gruppo (oltre a FrameSource) per ricevere i dati. Dopo che il canale è stato registrato nel gruppo, riceverà i dati inseriti dal gruppo.

    Anche il numero di canali che possono essere registrati dal gruppo di vari dispositivi è diverso.

## Moduli di rilegatura (Legatura)

Una volta che due gruppi sono collegati da Bind, i dati dal gruppo di origine verranno automaticamente inviati al gruppo di destinazione.  
Poiché il gruppo è l'unità di input dati più piccola e l'output è l'unità di output dati più piccola, deviceID, groupID e outputID di srcCell in entrambi i parametri di IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) valido.  

Sebbene dstCell sia valido solo per deviceID e groupID, outputID non ha senso come immissione di dati.

Esempio 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* viene generato un gruppo che genera un collegamento da FrameSource a Encoder.


* Due canali sono registrati in Encoder Group, quindi Encoder Group ha due uscite H264 e JPEG.



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
Questo è un tipico programma Bind: un flusso di codice a due canali.
 * FrameSource ha due uscite, ovvero lo stream principale Channel0 (1280x720) e lo stream slave Channel1 (640x360).
   *   Flusso principale: FrameSource's Channel0 Bind OSD Group.0, OSD Group.0 Bind Encoder Group.0. Tra questi: 
       * OSD Group.0 ha registrato due regioni che vengono utilizzate rispettivamente per visualizzare timestamp e informazioni sulla stringa
       * Encoder Group .0 ha registrato due canali. , che sono rispettivamente la codifica H264 e la codifica JPEG. Tra questi, se la dimensione dell'immagine del canale di codifica JPEG non corrisponde al parametro di input (di FrameSource Channel0), verrà scalata (software a T10) ) raggiungono l'obiettivo di catturare a qualsiasi risoluzione.
       
Note:
* si consiglia di eseguire tutte le operazioni di collegamento durante l'inizializzazione del sistema.
* Le operazioni Bind e UnBind non possono essere chiamate dinamicamente dopo l'attivazione di _FrameSource_ . UnBind viene eseguito solo dopo la disattivazione _FrameSource_.

## Funzioni

### int IMP\_Sistema\_Iniz (vuoto )
Inizializzazione del sistema IMP.
restituisce 0 in caso di successo.
Dopo questa chiamata API, la struttura dei dati di base verrà inizializzata, ma l'hardware non verrà inizializzato.
Attenzione: questa funzione deve essere richiamata per l'avvio prima di qualsiasi altra operazione.
### int IMP_System_Uscita (vuoto)

Dopo aver chiamato questa funzione, tutta la memoria e l'IMP _handles_ verranno rilasciati e l'hardware verrà spento. 
Nota: dopo aver chiamato questa API, se vuoi usare di nuovo IMP, devi resettare il sistema IMP.

### int64_t IMP_Sistema_GetTimeStamp (void)

Ottieni il timestamp del sistema IMP in microsecondi.  
Ritorno: tempo in microsecondi.

### int IMP_System_RebaseTimeStamp (basi int64_t)
Imposta il timestamp del sistema IMP in microsecondi.  
Ritorno: 0 in caso di successo.

### uint32_t IMP_Sistema_ReadReg32 (uint32_t u32Addr)

Leggi il valore di un registro a 32 bit.  

### vuoto IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Scrive il valore nel registro a 32 bit.

Nota: chiama attentamente questa API e controlla il significato del registro, altrimenti potrebbe causare errori di sistema.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Ottieni il numero di versione del sistema IMP.

### const char * IMP_System_GetCPUInfo (vuoto)
Ottieni informazioni sul modello di CPU.  
Nota: il valore restituito è una stringa del modello di CPU, ad esempio, per T10 sono presenti "T10"e "T10-Lite".

### int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)

Collegamento tra cella di origine e destinazione.

Nota 1: in base ai concetti di dispositivo, gruppo e output, ogni dispositivo può avere diversi gruppi e ogni gruppo può avere diverse uscite, il gruppo viene utilizzato come interfaccia di input del dispositivo e l'output viene utilizzato come interfaccia del prodotto del dispositivo. Pertanto il collegamento collega effettivamente una certa uscita del dispositivo di output a un certo Gruppo del dispositivo di input.

Nota 2: dopo un collegamento riuscito, i dati generati da srcCell (Output) verranno automaticamente trasmessi al gruppo di celle di destinazione ().

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Separa le origini e le destinazioni. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Recupera le informazioni dalla cella di origine relativa alla destinazione.




