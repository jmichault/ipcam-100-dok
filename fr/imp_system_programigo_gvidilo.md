

# IMP (Ingenic Media Platform) (voir imp_system.h)

## concepts de base 
la programmation du T20/T21 repose sur les concepts suivants :
 1. Périphérique (=Device)  
    Le périphérique complète une fonction. Exemples :
     *  Framesource : termine la sortie des données vidéo.
     *  Encoder : complète la fonction d'encodage vidéo ou d'encodage d'image.
 2. Groupe  
    Le groupe est la plus petite unité d'entrée de données. Un appareil peut avoir plusieurs groupes et chaque groupe ne peut recevoir qu'un seul canal d'entrée de données. Le groupe peut avoir plusieurs sorties.  
    Le groupe est également un conteneur pour des "fonctions" spécifiques. Voir l'explication dans la section canal pour plus de détails.
 3. Sortie  
    La sortie est la plus petite unité de sortie de données pour un groupe. Un groupe peut avoir plusieurs sorties et chaque sortie ne peut produire qu'un seul canal de données.
 4. Cellule  
    La cellule fait référence à une collection contenant des informations sur le périphérique, le groupe et la sortie. Il est présenté dans la structure de données de IMPCell.
    La cellule est principalement utilisée pour Bind (@ref bind). Selon la définition de Device, Group et Output, Output est le nœud pour la sortie de données et Group est le nœud pour l'entrée de données.
    Dans Bind, l'index de cellule du noeud de sortie de données est à la sortie Output, et l'index de cellule du noeud d'entrée de données est au groupe d'entrée (de sorte que l'entrée de données Cell, Output est une valeur sans signification).
 5. Canal  
    Le canal fait généralement référence à une unité avec une seule fonction. Le canal se voit attribuer une fonction spécifique lors de sa création (instanciation).  
    Par exemple:  
     -  Pour l'encodeur, un canal complète la fonction d'encodage H264 ou d'encodage JPEG. La fonction d'encodage spécifique (type, paramètre) est spécifiée lors de la création du canal
     -  Pour IVS, un canal complète la fonction d'un algorithme spécifique et les paramètres de type d'algorithme spécifiques sont spécifiés lors de la création du canal
     -  Pour l'OSD, il existe une région similaire à Channel, une région est une zone superposée spécifique, qui peut être PIC (image), COVER (occlusion), etc.
     -  Pour FrameSource, un canal produit une image originale et le canal de FrameSource est en fait un groupe
     
     Le canal, en tant qu'unité fonctionnelle, doit généralement être enregistré dans le groupe (sauf FrameSource) pour recevoir des données. Une fois que le canal est enregistré dans le groupe, il obtiendra les données saisies par le groupe.

    Le nombre de canaux qui peuvent être enregistrés par le groupe de différents appareils est également différent.

## Liaison de modules (Bind)

Une fois que deux groupes sont connectés par Bind, les données du groupe source seront automatiquement envoyées au groupe de destination.  
Puisque le groupe est la plus petite unité d'entrée de données et que la sortie est la plus petite unité de sortie de données, le deviceID, groupID et outputID du srcCell dans les deux paramètres de IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) sont valides.  

Alors que dstCell n'est valide que pour deviceID et groupID, outputID n'a pas de sens en tant qu'entrée de données.

Exemple 1 : 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* un groupe qui génère une liaison de FrameSource à Encoder est réalisé.
* Deux canaux sont enregistrés dans Encoder Group, donc Encoder Group a deux sorties H264 et JPEG.

Exemple 2 :
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
C'est une application typique Bind : flux de code à deux canaux.
 * FrameSource a deux sorties, à savoir le flux principal Channel0 (1280x720) et le flux esclave Channel1 (640x360).
   *   Flux principal: Channel0 Bind OSD Group.0 de FrameSource, OSD Group.0 Bind Encoder Group.0. Parmi eux: 
       * OSD Group.0 a enregistré deux régions, qui sont utilisées pour afficher respectivement les informations d'horodatage et de chaîne de caractères
       * Encoder Group.0 a enregistré deux canaux, qui sont respectivement l'encodage H264 et l'encodage JPEG. Parmi eux, si la taille de l'image du canal de codage JPEG n'est pas égale au paramètre d'entrée (Channel0 de FrameSource), alors elle sera mise à l'échelle (logiciel à T10) pour atteindre l'objectif de capturer à n'importe quelle résolution.
       
Notes :
* on recommande que toutes les opérations de liaison soient effectuées lors de l'initialisation du système.
* Les opérations Bind et UnBind ne peuvent pas être appelées dynamiquement une fois le _FrameSource_ activé. UnBind ne peut être effectué qu'après avoir désactivé le _FrameSource_.

## Les fonctions

### int IMP\_System\_Init (void )
Initialisation du système IMP.
renvoie 0 si succès.
Après cet appel d'API, la structure de données de base sera initialisée, mais l'unité matérielle ne sera pas initialisée.
attention : Cette fonction doit être appelée pour l'initialisation avant toute autre opération.
### int IMP_System_Exit (void)

Après avoir appelé cette fonction, toute la mémoire et les _handles_ d'IMP seront libérées, et l'unité matérielle sera fermée. 
Note : Après avoir appelé cette API, si vous voulez utiliser à nouveau IMP, vous devez réinitialisez le système IMP.

### int64_t IMP_System_GetTimeStamp (void)

Obtenez l'horodatage du système IMP en microsecondes.  
Retour : temps en microsecondes.

### int IMP_System_RebaseTimeStamp (bases int64_t)
Définissez l'horodatage du système IMP en microsecondes.  
Retour : 0 si succès.

### uint32_t IMP_System_ReadReg32 (uint32_t u32Addr)

Lire la valeur d'un registre 32 bits.  

### void IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Ecrire la valeur dans le registre 32 bits.

Note : Veuillez appeler cette API avec précaution et vérifier la signification du registre, sinon cela peut provoquer des erreurs système.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Obtenir le numéro de version du système IMP.

### const char * IMP_System_GetCPUInfo (void)
Obtenir des informations sur le modèle de CPU.  
Note : La valeur de retour est une chaîne de type de modèle de CPU, par exemple, pour T10 , il y a "T10" et "T10-Lite".

### int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)

Liaison entre cellule source et cellule de destination.

Note 1 : Selon les concepts de périphérique, Groupe et sortie, chaque périphérique peut avoir plusieurs groupes, et chaque groupe peut avoir plusieurs sorties, Group est utilisé comme interface d'entrée de Device, et Output est utilisé comme interface de sortie de Device. Par conséquent, la liaison connecte en fait une certaine sortie du Device de sortie à un certain Group du Device d'entrée.

Note 2 : Après une liaison réussie, les données générées par srcCell (Sortie) seront automatiquement transférées vers la Cellule de destination (Groupe).

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Dissocier les cellules source et destination. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Récupère les informations de la cellule source liées à la cellule de destination.




