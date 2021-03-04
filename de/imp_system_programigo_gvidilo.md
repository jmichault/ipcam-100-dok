

# IMP (Ingenic Media Platform) (siehe imp_system.h)

## grundlegendes Konzept
Die T20 / T21-Programmierung basiert auf folgenden Konzepten:
1. Peripheriegerät (= Gerät)  
    Das Peripheriegerät führt eine Funktion aus. Beispiele:
     *  Bildquelle: Beendet die Ausgabe von Videodaten.
     *  Encoder: Vervollständigt die Videokodierungs- oder Bildcodierungsfunktion.
2. Gruppe  
    Die Gruppe ist die kleinste Dateneingabeeinheit. Ein Gerät kann mehrere Gruppen haben und jede Gruppe kann nur einen Dateneingabekanal empfangen. Die Gruppe kann mehrere Ergebnisse haben.  
    Die Gruppe ist auch ein Behälter für bestimmte "Funktionen". Weitere Informationen finden Sie in der Erläuterung im Abschnitt "Kanal".
3. Ausfahrt  
    Die Ausgabe ist die kleinste Einheit der Datenausgabe pro Gruppe. Eine Gruppe kann mehrere Ausgänge haben und jeder Ausgang kann nur einen Datenkanal erzeugen.
4. Zelle  
    Die Zelle bezieht sich auf eine Sammlung, die Informationen über das Gerät, die Gruppe und die Ausgabe enthält. Es wird in der IMPCell-Datenstruktur dargestellt.
Die Zelle wird hauptsächlich zum Binden (@ref Binden)verwendet. Gemäß der Definition von Gerät, Gruppe und Ausgabe ist die Ausgabe der Knoten für die Datenausgabe und die Gruppe der Knoten für die Dateneingabe.
In Bind befindet sich der Zellenindex des Datenausgabeknotens am Ausgabeausgang, und der Zellenindex des Dateneingabeknotens befindet sich in der Eingabegruppe (, sodass sich die Dateneingabe Zelle, Ausgabe befindet ein unsinniger Wert).
5. Kanal  
    Der Kanal bezieht sich im Allgemeinen auf eine Einheit mit einer einzelnen Funktion. Der Kanal erhält eine bestimmte Funktion, wenn eine Instanziierung ()erstellt wird.  
    Zum Beispiel:  
     -  Für den Encoder ergänzt ein Kanal die H264-Code- oder JPEG-Codierungsfunktion. Der spezifische Codierungsfunktionstyp (, Parameter) wird beim Erstellen des Kanals angegeben.


     -  Bei IVS vervollständigt ein Kanal die Funktion eines bestimmten Algorithmus, und beim Erstellen des Kanals werden bestimmte algorithmische Typparameter angegeben.


     -  Für OSD gibt es einen Bereich ähnlich dem Kanal. Der Bereich ist ein spezifischer Überlagerungsbereich, der PIC-Bild (), ABDECKUNG (, Verschluss)usw. sein kann .


     -  Bei FrameSource erzeugt ein Kanal ein Originalbild und der FrameSource-Kanal ist tatsächlich eine Gruppe.


     
     Der Kanal als Funktionseinheit muss im Allgemeinen zusätzlich zu FrameSource) in der Gruppe (registriert sein, um Daten zu empfangen. Nachdem der Kanal in der Gruppe registriert wurde, empfängt er die von der Gruppe eingegebenen Daten.

    Die Anzahl der Kanäle, die von der Gruppe verschiedener Geräte aufgezeichnet werden können, ist ebenfalls unterschiedlich.

## Bindemodule (Binden)

Sobald zwei Gruppen durch Binden verbunden sind, werden die Daten aus der Quellgruppe automatisch an die Zielgruppe gesendet.  
Da die Gruppe die kleinste Dateneingabeeinheit und die Ausgabe die kleinste Datenausgabeeinheit ist, werden die Geräte-ID, die Gruppen-ID und die Ausgabe-ID von srcCell in beiden Parametern von IMP_System_Bind (IMPCell * angegeben. srcCell, IMPCell * dstCell) gültig.  

Während dstCell nur für Geräte-ID und Gruppen-ID gültig ist, ist die Ausgabe-ID als Dateneingabe nicht sinnvoll.

Beispiel 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* Es wird eine Gruppe generiert, die eine Verknüpfung von FrameSource zu Encoder generiert.


* In der Encoder Group werden zwei Kanäle aufgezeichnet, sodass die Encoder Group über zwei Ausgänge H264 und JPEG verfügt.



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
Dies ist ein typisches Bind-Programm: ein zweikanaliger Codestream.
 * FrameSource verfügt über zwei Ausgänge, nämlich den Hauptstrom Channel0 (1280x720) und den Slave-Stream Channel1 (640x360).
   *   Hauptstrom: Channel0 Bind OSD Group.0 von FrameSource, OSD Group.0 Bind Encoder Group.0. Darunter: 
       * OSD Group.0 zeichnete zwei Regionen auf, die zum Anzeigen von Zeitstempel- bzw. Zeichenfolgeninformationen verwendet werden.
       * Encoder Group .0 zeichnete zwei Kanäle auf. , die H264-Codierung bzw. JPEG-Codierung sind. Wenn die Bildgröße des JPEG-Codierungskanals nicht mit dem Eingabeparameter (von FrameSource Channel0)übereinstimmt, wird die Software bei T10) skaliert (.) erreichen das Ziel, bei jeder Auflösung zu erfassen.
       
Hinweise:
* Es wird empfohlen, alle Verbindungsvorgänge während der Systeminitialisierung auszuführen.
* Bind- und UnBind-Vorgänge können nach Aktivierung von _FrameSource_ nicht dynamisch aufgerufen werden. Das Aufheben der Bindung erfolgt erst nach Deaktivierung _FrameSource_.

## Funktionen

### int IMP\_System\_Init (leer )
Initialisierung des IMP-Systems.
gibt bei Erfolg 0 zurück.
Nach diesem API-Aufruf wird die grundlegende Datenstruktur initialisiert, die Hardware jedoch nicht.
Achtung: Diese Funktion muss vor jeder anderen Operation zur Initiierung aufgerufen werden.
### int IMP_System_Ausgang (leer)

Nach dem Aufruf dieser Funktion werden der gesamte Speicher und IMP _handles_ freigegeben und die Hardware heruntergefahren. 
Hinweis: Wenn Sie nach dem Aufrufen dieser API IMP erneut verwenden möchten, müssen Sie das IMP-System zurücksetzen.

### int64_t IMP_System_GetTimeStamp (void)

Holen Sie sich den Zeitstempel des IMP-Systems in Mikrosekunden.  
Rückgabe: Zeit in Mikrosekunden.

### int IMP_System_RebaseTimeStamp (Basen int64_t)
Stellen Sie den Zeitstempel des IMP-Systems in Mikrosekunden ein.  
Rückgabe: 0 bei Erfolg.

### uint32_t IMP_System_ReadReg32 (uint32_t u32Addr)

Lesen Sie den Wert eines 32-Bit-Registers.  

### leer IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Schreiben Sie den Wert in das 32-Bit-Register.

Hinweis: Rufen Sie diese API sorgfältig auf und überprüfen Sie die Bedeutung der Registrierung. Andernfalls kann es zu Systemfehlern kommen.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Rufen Sie die Versionsnummer des IMP-Systems ab.

### const char * IMP_System_GetCPUInfo (leer)
Informationen zum CPU-Modell abrufen.  
Hinweis: Der Rückgabewert ist eine Zeichenfolge des CPU-Modells. Für T10 gibt es beispielsweise "T10"und "T10-Lite".

### int IMP_System_Binden (IMPCell * srcCell, IMPCell * dstCell)

Verbindung zwischen Quellzelle und Ziel.

Hinweis 1: Gemäß den Konzepten von Gerät, Gruppe und Ausgabe kann jedes Gerät mehrere Gruppen und jede Gruppe mehrere Ausgänge haben. Die Gruppe wird als Geräteeingabeschnittstelle und die Ausgabe als Geräteproduktschnittstelle verwendet. Daher verbindet die Verbindung tatsächlich einen bestimmten Ausgang des Ausgabegeräts mit einer bestimmten Gruppe des Eingabegeräts.

Hinweis 2: Nach einer erfolgreichen Verknüpfung werden die von srcCell (Output) generierten Daten automatisch an die Zielzellengruppe ()übertragen.

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Gruppieren Sie die Quellen und Ziele auf. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Ruft Informationen aus der Quellzelle ab, die sich auf das Ziel beziehen.




