---
lang: es
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Guía de programación   _IMP_'
---


La documentación de API se puede ver aquí:   
* [  versión original en chino  ](../../zh/includes.zh/html/)  


* [  Inglés  ](../../en/includes.en/html/)  


* [  Versión en francés Traducido por Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( Ver   _imp\_system.h_  \)

## conceptos básicos
El programa T20 / T21 se basa en los siguientes conceptos:  
 1. Dispositivo   \( =  _Device_  \)    
 El dispositivo completa la función. Ejemplos:  
       *    _Framesource_ : Complete la salida de los videoclips.  
       *    _Encoder_ : complete el código de video o la función del código de imagen.  
 2. Grupo   \( =  _Group_  \)    
 El grupo es la unidad de entrada de datos más pequeña. Un dispositivo puede tener varios grupos y cada grupo puede recibir solo un canal de entrada de datos. El grupo puede tener varios resultados.   
      El grupo también es un contenedor para funciones   " específicas  ". Vea la explicación en la sección del canal para más detalles.  
 3. ELIGO   \( =  _Output_  \)    
 La salida es la unidad de salida de datos más pequeña por grupo.    
 El canal generalmente está relacionado con una unidad funcional única.    
 Por ejemplo:   
     -  Para el código, el canal completa la función   _H264_   o código   _JPEG_.  


     -  Para   _IVS_, un canal completa la función de un algoritmo específico y el algoritmo específico se especifican los parámetros típicos durante la creación del canal 


     -  Para  _OSD_, hay una región similar a   _Channel_, una región es un área específica supermetada que puede ser una cobertura de imagen   \( imagen   \(   \(, etc.  


     -  Para   _FrameSource_, un canal produce una imagen original y el canal   _FrameSource_   es en realidad un grupo  


    
       El canal, como unidad funcional, generalmente se conserva en el grupo   \(, excepto   _FrameSource_  \) recibir datos.  

    El número de canales que puede grabar el grupo de varios dispositivos también es diferente.

## Enlace del módulo   \(  _Bind_  \)

Después de que dos grupos estén vinculados por   _Bind_, los datos del grupo de origen se enviarán automáticamente al destino.    
 Dado que el grupo es la unidad de entrada de datos más pequeña y la salida es la unidad de salida de datos más pequeña, el   _deviceID_,   _groupID_   y   _outputID_    _srcCell_   en los dos parámetros de   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   son válidos.    

Si bien   _dstCell_   solo es válido para   _deviceID_   y   _groupID_,   _outputID_   no tiene sentido como la entrada de datos.  

Ejemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Resultado:    
 *  Un grupo genera un grupo que genera un enlace de FRAMESOURCE al codificador. 

* Dos canales están registrados en el grupo de codificadores, por lo que el grupo de codificadores tiene dos productos:   _H264_   y   _JPEG_.  



Ejemplo 2:
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
Aplicar es una aplicación típica   _Bind_ : Código de dos canales.  

Notas:  
  *   Se recomienda que todas las operaciones de enlace se realicen al inicializar el sistema.  

## Funciones

### _int IMP\_System\_Init \(void \)_
Inicio del sistema   _IMP_.  
### Inicio del sistema _int IMP\_System\_Exit \(void\)_. \_

Después de llamar a esta función, se liberará toda la memoria y   _handles_   _IMP_   y se cerrará la unidad de hardware.  

### Después de llamar a esta función, se liberará toda la memoria y _int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_ y se cerrará la unidad de hardware.  \(

Obtenga el campo de tiempo del sistema   _IMP_   en microsegundos.    
 Retorno: Tiempo en microecundos. 

### Obtenga el campo de tiempo del sistema _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ en microsegundos. \_ Retorno: Tiempo en microecundos.  \(
Defina el sistema de marca de tiempo   _IMP_   en microsegundos.    
 Retorno: 0 Si tiene éxito. 

### Defina el sistema de marca de tiempo _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ en microsegundos. \_ Retorno: 0 Si tiene éxito. \_

Lea el valor de un registro de 32 bits.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regandr, valor uint32  _t\)_
Escriba el valor en el registro de 32 bits.  

Nota: Llame a esta API con cuidado y verifique el significado del registro; de lo contrario, puede causar errores en el sistema.

### _int IMP_  Sistema  _GetVersion \(IMPVersion * pstVersion\)_

Obtenga el sistema del sistema   _IMP_.  

### _const char * IMP_  Sistema  _GetCPUInfo \(void\)_
Obtenga información sobre el modelo de CPU.  
Nota: El valor de retorno es una cadena de modelo de CPU, por ejemplo, para T10 hay "T10"y "T10-Lite".

### _int IMP_  Sistema   \(

Enlace entre la celda de origen y el destino.

Nota 1: De acuerdo con los conceptos de dispositivo, grupo y salida, cada dispositivo puede tener varios grupos y cada grupo puede tener varias salidas, el grupo se usa como interfaz de entrada del dispositivo y la salida se usa como interfaz de producto del dispositivo. Por lo tanto, el enlace en realidad conecta una determinada salida del dispositivo de salida a un determinado Grupo del dispositivo de entrada.

Nota 2: Después de un enlace exitoso, los datos generados por   _srcCell_   (  Eligo  )   se transferirán automáticamente al grupo de destino   (   ).  

### _int IMP_  Sistema   \(
Desagrupe las fuentes y los destinos. 

### _int IMP_  Sistema   \(

Recupera información de la celda de origen relacionada con el destino.

