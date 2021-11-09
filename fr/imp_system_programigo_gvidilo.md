---
lang: fr
lang-niv: fonto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Guide de programmation _IMP_'
---


La documentation des APIs peut être consultée ici :  
* [version originale en chinois](../../zh/includes.zh/html/)
* [version anglaise](../../en/includes.en/html/)
* [version française traduite par google](../../fr/includes.fr/html/)


# _IMP_ \(_Ingenic Media Platform_\) \(voir _imp\_system.h_\)

## concepts de base 
la programmation du T20/T21 repose sur les concepts suivants :
 1. Périphérique \(=_Device_\)  
    Le périphérique complète une fonction. Exemples :
     *  _Framesource_ : complète la sortie des données vidéo.
     *  _Encoder_ : complète la fonction d'encodage vidéo ou d'encodage d'image.
 2. Groupe \(=_Group_\)  
    Le groupe est la plus petite unité d'entrée de données. Un appareil peut avoir plusieurs groupes et chaque groupe ne peut recevoir qu'un seul canal d'entrée de données. Le groupe peut avoir plusieurs sorties.  
    Le groupe est également un conteneur pour des "fonctions" spécifiques. Voir l'explication dans la section canal pour plus de détails.
 3. Sortie \(=_Output_\)  
    La sortie est la plus petite unité de sortie de données pour un groupe. Un groupe peut avoir plusieurs sorties et chaque sortie ne peut produire qu'un seul canal de données.
 4. Cellule \(=_Cell_\) 
    La cellule fait référence à une collection contenant des informations sur le périphérique, le groupe et la sortie. Il est présenté dans la structure de données de _IMPCell_.
    La cellule est principalement utilisée pour _Bind \(@ref bind\)_. Selon la définition de _Device_, _Group_ et _Output_, _Output_ est le nœud pour la sortie de données et _Group_ est le nœud pour l'entrée de données.
    Dans _Bind_, l'index de cellule du noeud de sortie de données est à la sortie _Output_, et l'index de cellule du noeud d'entrée de données est au groupe d'entrée \(de sorte que l'entrée de données _Cell_, _Output_ est une valeur sans signification\).
 5. Canal \(=_Channel_\)  
    Le canal fait généralement référence à une unité avec une seule fonction. Le canal se voit attribuer une fonction spécifique lors de sa création \(instanciation\).  
    Par exemple:  
     -  Pour l'encodeur, un canal complète la fonction d'encodage _H264_ ou d'encodage _JPEG_. La fonction d'encodage spécifique \(type, paramètre\) est spécifiée lors de la création du canal
     -  Pour _IVS_, un canal complète la fonction d'un algorithme spécifique et les paramètres de type d'algorithme spécifiques sont spécifiés lors de la création du canal
     -  Pour l'_OSD_, il existe une région similaire à _Channel_, une région est une zone superposée spécifique, qui peut être PIC \(image\), COVER \(occlusion\), etc.
     -  Pour _FrameSource_, un canal produit une image originale et le canal de _FrameSource_ est en fait un groupe
    
     Le canal, en tant qu'unité fonctionnelle, doit généralement être enregistré dans le groupe \(sauf _FrameSource_\) pour recevoir des données. Une fois que le canal est enregistré dans le groupe, il obtiendra les données d'entrée du groupe.

    Le nombre de canaux qui peuvent être enregistrés par le groupe de différents appareils est également différent.

## Liaison de modules \(_Bind_\)

Une fois que deux groupes sont connectés par _Bind_, les données du groupe source seront automatiquement envoyées au groupe de destination.  
Puisque le groupe est la plus petite unité d'entrée de données et que la sortie est la plus petite unité de sortie de données, le _deviceID_, _groupID_ et _outputID_ du _srcCell_ dans les deux paramètres de _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_ sont valides.  

Alors que _dstCell_ n'est valide que pour _deviceID_ et _groupID_, _outputID_ n'a pas de sens en tant qu'entrée de données.

Exemple 1 : 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
résultat :  
* un groupe qui génère une liaison de FrameSource à Encoder est réalisé.
* Deux canaux sont enregistrés dans Encoder Group, donc Encoder Group a deux sorties : _H264_ et _JPEG_.

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
C'est une application typique _Bind_ : flux de code à deux canaux.
* FrameSource a deux sorties, à savoir le flux principal _Channel0 (1280x720)_ et le flux esclave _Channel1 (640x360)_.
*   Flux principal: Channel0 Bind OSD Group.0 de FrameSource, OSD Group.0 Bind Encoder Group.0. Parmi eux: 
* OSD Group.0 a enregistré deux régions, qui sont utilisées pour afficher respectivement les informations d'horodatage et de chaîne de caractères
* Encoder Group.0 a enregistré deux canaux, qui sont respectivement l'encodage H264 et l'encodage JPEG. Parmi eux, si la taille de l'image du canal de codage JPEG n'est pas égale au paramètre d'entrée (Channel0 de FrameSource), alors elle sera mise à l'échelle (logiciel à T10) pour atteindre l'objectif de capturer à n'importe quelle résolution.

Notes :
* on recommande que toutes les opérations de liaison soient effectuées lors de l'initialisation du système.
* Les opérations _Bind_ et _UnBind_ ne peuvent pas être appelées dynamiquement une fois le _FrameSource_ activé. _UnBind_ ne peut être effectué qu'après avoir désactivé le _FrameSource_.

## Les fonctions

### _int IMP\_System\_Init \(void \)_
Initialisation du système _IMP_.
renvoie 0 si succès.
Après cet appel d'API, la structure de données de base sera initialisée, mais l'unité matérielle ne sera pas initialisée.
attention : Cette fonction doit être appelée pour l'initialisation avant toute autre opération.
### _int IMP\_System\_Exit \(void\)_

Après avoir appelé cette fonction, toute la mémoire et les _handles_ d'_IMP_ seront libérées, et l'unité matérielle sera fermée. 
Note : Après avoir appelé cette API, si vous voulez utiliser à nouveau _IMP_, vous devez réinitialisez le système _IMP_.

### _int64\_t IMP\_System\_GetTimeStamp \(void\)_

Obtenez l'horodatage du système _IMP_ en microsecondes.  
Retour : temps en microsecondes.

### _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_
Définissez l'horodatage du système _IMP_ en microsecondes.  
Retour : 0 si succès.

### _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_

Lire la valeur d'un registre 32 bits.  

### _void IMP\_System\_WriteReg32 \(uint32_t regAddr, valeur uint32_t\)_
Écrire la valeur dans le registre 32 bits.

Note : Veuillez appeler cette API avec précaution et vérifier la signification du registre, sinon cela peut provoquer des erreurs système.

### _int IMP_System_GetVersion \(IMPVersion * pstVersion\)_

Obtenir le numéro de version du système _IMP_.

### _const char * IMP_System_GetCPUInfo \(void\)_
Obtenir des informations sur le modèle de CPU.  
Note : La valeur de retour est une chaîne de type de modèle de CPU, par exemple, pour T10 , il y a "T10" et "T10-Lite".

### _int IMP_System_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_

Liaison entre cellule source et cellule de destination.

Note 1 : Selon les concepts de périphérique, Groupe et sortie, chaque périphérique peut avoir plusieurs groupes, et chaque groupe peut avoir plusieurs sorties, Group est utilisé comme interface d'entrée de Device, et Output est utilisé comme interface de sortie de Device. Par conséquent, la liaison connecte en fait une certaine sortie du Device de sortie à un certain Group du Device d'entrée.

Note 2 : Après une liaison réussie, les données générées par _srcCell_ (Sortie) seront automatiquement transférées vers la Cellule de destination (Groupe).

### _int IMP_System_UnBind \(IMPCell * srcCell, IMPCell * dstCell\)_
Dissocier les cellules source et destination. 

### _int IMP_System_GetBindbyDest \(IMPCell * dstCell, IMPCell * srcCell\)_

Récupère les informations de la cellule source liées à la cellule de destination.

