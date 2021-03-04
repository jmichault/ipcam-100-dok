

# IMP (Ingenic Media Platform) (ver imp_system.h)

## conceptos básicos
La programación de T20 / T21 se basa en los siguientes conceptos:
1. Periférico (= Dispositivo)  
    El periférico completa una función. Ejemplos:
     *  Fuente de fotograma: finaliza la salida de datos de video.
     *  Codificador: completa la función de codificación de video o codificación de imagen.
2. Grupo  
    El grupo es la unidad de entrada de datos más pequeña. Un dispositivo puede tener varios grupos y cada grupo puede recibir solo un canal de entrada de datos. El grupo puede tener varios resultados.  
    El grupo también es un contenedor para funciones específicas "". Consulte la explicación en la sección de canales para obtener más detalles.
3. Salida  
    La salida es la unidad más pequeña de salida de datos por grupo. Un grupo puede tener varias salidas y cada salida puede producir solo un canal de datos.
4. Celda  
    La celda se refiere a una colección que contiene información sobre el dispositivo, el grupo y la salida. Se presenta en la estructura de datos de IMPCell.
La celda se utiliza principalmente para Bind (@ref bind). De acuerdo con la definición de Dispositivo, Grupo y Salida, Salida es el nodo para la salida de datos y Grupo es el nodo para la entrada de datos.
En Bind, el índice de celda del nodo de salida de datos está en la salida de salida, y el índice de celda del nodo de entrada de datos está en el grupo de entrada (de modo que la entrada de datos de celda, salida es un valor sin sentido).
5. Canal  
    El canal generalmente se refiere a una unidad con una sola función. El canal recibe una función específica cuando se crea (instanciación).  
    Por ejemplo:  
     -  Para el codificador, un canal complementa el código H264 o la función de codificación JPEG. El tipo de función de codificación específica (, parámetro) se especifica al crear el canal


     -  Para IVS, un canal completa la función de un algoritmo específico y se especifican parámetros de tipo algorítmico específicos al crear el canal


     -  Para OSD, hay una región similar al Canal, la región es un área de superposición específica, que puede ser PIC (imagen), CUBIERTA (cierre), etc. .


     -  Para FrameSource, un canal produce una imagen original y el canal FrameSource es en realidad un grupo


     
     El canal, como unidad funcional, generalmente debe estar registrado en el grupo (además de FrameSource) para recibir datos. Después de que el canal se registre en el grupo, recibirá los datos ingresados ​​por el grupo.

    El número de canales que puede grabar el grupo de varios dispositivos también es diferente.

## Encuadernación de módulos (Encuadernación)

Una vez que Bind conecta dos grupos, los datos del grupo de origen se enviarán automáticamente al grupo de destino.  
Debido a que el grupo es la unidad de entrada de datos más pequeña y la salida es la unidad de salida de datos más pequeña, el deviceID, groupID y outputID de srcCell en ambos parámetros de IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) válido.  

Si bien dstCell es válido solo para deviceID y groupID, outputID no tiene sentido como entrada de datos.

Ejemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* se genera un grupo que genera un enlace desde FrameSource a Encoder.


* Se graban dos canales en Encoder Group, por lo que Encoder Group tiene dos salidas H264 y JPEG.



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
Este es un programa Bind típico: un flujo de código de dos canales.
 * FrameSource tiene dos salidas, a saber, el flujo principal Channel0 (1280x720) y el flujo esclavo Channel1 (640x360).
   *   Flujo principal: Canal 0 de FrameSource enlazar grupo OSD.0, grupo OSD.0 enlazar grupo codificador.0. Entre ellos: 
       * OSD Group.0 registró dos regiones que se utilizan para mostrar la marca de tiempo y la información de la cadena, respectivamente
       * Encoder Group .0 registró dos canales. , que son codificación H264 y codificación JPEG respectivamente. Entre ellos, si el tamaño de la imagen del canal de codificación JPEG no coincide con el parámetro de entrada (de FrameSource Channel0), entonces se escalará (en el software T10) ) lograr el objetivo de capturar en cualquier resolución.
       
Notas:
* se recomienda que todas las operaciones de enlace se realicen durante la inicialización del sistema.
* Las operaciones de vinculación y desvinculación no se pueden llamar dinámicamente después de activar _FrameSource_ . UnBind se realiza solo después de la desactivación _FrameSource_.

## Funciones

### int IMP\_Sistema\_Init (vacío )
Inicialización del sistema IMP.
devuelve 0 si tiene éxito.
Después de esta llamada a la API, se inicializará la estructura de datos básica, pero no se inicializará el hardware.
Atención: Esta función debe llamarse para el inicio antes de cualquier otra operación.
### int IMP_System_Salida (vacío)

Después de llamar a esta función, toda la memoria y el IMP _handles_ se liberarán y el hardware se apagará. 
Nota: Después de llamar a esta API, si desea volver a usar IMP, debe restablecer el sistema IMP.

### int64_t IMP_Sistema_GetTimeStamp (void)

Obtenga la marca de tiempo del sistema IMP en microsegundos.  
Retorno: tiempo en microsegundos.

### int IMP_System_RebaseTimeStamp (bases int64_t)
Establezca la marca de tiempo del sistema IMP en microsegundos.  
Devolver: 0 si tiene éxito.

### uint32_t IMP_Sistema_ReadReg32 (uint32_t u32Addr)

Lea el valor de un registro de 32 bits.  

### en blanco IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Escriba el valor en el registro de 32 bits.

Nota: Llame a esta API con cuidado y verifique el significado del registro; de lo contrario, puede causar errores en el sistema.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Obtenga el número de versión del sistema IMP.

### const char * IMP_System_GetCPUInfo (vacío)
Obtenga información sobre el modelo de CPU.  
Nota: El valor de retorno es una cadena de modelo de CPU, por ejemplo, para T10 hay "T10"y "T10-Lite".

### int IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell)

Enlace entre la celda de origen y el destino.

Nota 1: De acuerdo con los conceptos de dispositivo, grupo y salida, cada dispositivo puede tener varios grupos y cada grupo puede tener varias salidas, el grupo se usa como interfaz de entrada del dispositivo y la salida se usa como interfaz de producto del dispositivo. Por lo tanto, el enlace en realidad conecta una determinada salida del dispositivo de salida a un determinado Grupo del dispositivo de entrada.

Nota 2: Después de un enlace exitoso, los datos generados por srcCell (Salida) se transmitirán automáticamente al Grupo de celda de destino ().

### int IMP_System_Desenlazar (IMPCell * srcCell, IMPCell * dstCell)
Desagrupe las fuentes y los destinos. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Recupera información de la celda de origen relacionada con el destino.




