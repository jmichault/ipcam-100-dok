---
lang: pt
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Guia de programação   _IMP_'
---


A documentação da APIs pode ser vista aqui:   
* [  Versão Original em Chinês  ](../../zh/includes.zh/html/)  


* [  inglês  ](../../en/includes.en/html/)  


* [  Versão francesa traduzida pelo Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( ver   _imp\_system.h_  \)

## Conceitos Básicos
O programa T20 / T21 é baseado nos seguintes conceitos:  
 1. Dispositivo   \( =  _Device_  \)    
 O dispositivo conclui a função. Exemplos:  
       *    _Framesource_ : complete a saída de clipes de vídeo.  
       *    _Encoder_ : Complete o código de vídeo ou a função de código de imagem.  
 2. Grupo   \( =  _Group_  \)    
 O grupo é a menor unidade de entrada de dados. Um dispositivo pode ter vários grupos e cada grupo pode receber apenas um canal de entrada de dados. O grupo pode ter vários resultados.   
      O grupo também é um recipiente para funções específicas   "  ". Veja a explicação na seção Canal para mais detalhes.  
 3. Eligo   \( =  _Output_  \)    
 A saída é a menor unidade de saída de dados por grupo.    
 O canal é geralmente relacionado a uma única unidade funcional.    
 Por exemplo:   
     -  Para o codel, o canal conclui a função   _H264_   ou código   _JPEG_.  


     -  Para   _IVS_, um canal conclui a função de um algoritmo específico e os parâmetros típicos de algoritmo específicos são especificados durante a criação do canal 


     -  Para  _OSD_, há uma região semelhante a   _Channel_, uma região é uma área supermetada específica que pode ser um top   \( imagem  \) capa   \( oclusão  \), etc.  


     -  Para   _FrameSource_, um canal produz uma imagem original e o canal   _FrameSource_   é realmente um grupo  


    
       O canal, como uma unidade funcional, geralmente ser preservada no grupo   \(, exceto   _FrameSource_  \) recebe dados.  

    O número de canais que podem ser gravados pelo grupo de vários dispositivos também é diferente.

## Link do módulo   \(  _Bind_  \)

Depois que dois grupos estão vinculados por   _Bind_, os dados do grupo de origem enviarão automaticamente para o destino.    
 Como o grupo é a menor unidade de entrada de dados e a saída é a menor unidade de saída de dados, o   _deviceID_,   _groupID_   e   _outputID_    _srcCell_   nos dois parâmetros de   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   são válidos.    

Enquanto   _dstCell_   é válido apenas para   _deviceID_   e   _groupID_,   _outputID_   não faz sentido como entrada de dados.  

Exemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Resultado:    
 *  Um grupo gera um grupo que gera um link da Framesource ao codificador. 

* Dois canais são registrados no Grupo Encoder, então o Grupo Encoder tem dois produtos:   _H264_   e   _JPEG_.  



Exemplo 2:
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
Aplicar é um aplicativo típico   _Bind_ : código de dois canais.  

Notas:  
  *   Recomenda-se que todas as operações de link sejam feitas ao inicializar o sistema.  

## Funções

### _int IMP\_System\_Init \(void \)_
Início do sistema   _IMP_.  
### Início do sistema _int IMP\_System\_Exit \(void\)_. \_

Depois de chamar essa função, toda a memória e   _handles_   _IMP_   será lançada e a unidade de hardware será fechada.  

### Depois de chamar essa função, toda a memória e _int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_ será lançada e a unidade de hardware será fechada.  \(

Obtenha o campo de temporização do sistema   _IMP_   em microssegundos.    
 Return: Hora em microeconds. 

### Obtenha o campo de temporização do sistema _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ em microssegundos. \_ Return: Hora em microeconds.  \(
Defina o sistema Timestamp   _IMP_   em microssegundos.    
 Return: 0 se for bem sucedido. 

### Defina o sistema Timestamp _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ em microssegundos. \_ Return: 0 se for bem sucedido. \_

Leia o valor de um registro de 32 bits.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regaddr, valor uint32  _t\)_
Escreva o valor no registro de 32 bits.  

Nota: Por favor, chame esta API com cuidado e verifique o significado do registro, caso contrário, pode causar erros de sistema.

### _int IMP_  System  _GetVersion \(IMPVersion * pstVersion\)_

Obtenha o sistema do sistema   _IMP_.  

### _const char * IMP_  System  _GetCPUInfo \(void\)_
Obtenha informações sobre o modelo de CPU.  
Nota: O valor de retorno é uma string do modelo da CPU, por exemplo, para T10 há "T10"e "T10-Lite".

### _int IMP_  System   \(

Link entre a célula de origem e o destino.

Nota 1: De acordo com os conceitos de Dispositivo, Grupo e Saída, cada dispositivo pode ter vários grupos, e cada grupo pode ter várias saídas, Grupo é usado como interface de entrada do dispositivo e Saída é usado como interface de produto do dispositivo. Portanto, o link realmente conecta uma determinada saída do dispositivo de saída a um determinado Grupo do dispositivo de entrada.

Nota 2: Após um link bem-sucedido, os dados gerados pelo   _srcCell_   (  Eligo  )   serão automaticamente transferidos para o destino   (  Grupo  ).  

### _int IMP_  System   \(
Desagrupe as origens e destinos. 

### _int IMP_  System   \(

Recupera informações da célula de origem relacionadas ao destino.

