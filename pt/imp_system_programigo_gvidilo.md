---
lang: pt
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Guia de programação do Imp.'
---


A documentação da APIs pode ser vista aqui: (° 1 ° 1  
* [Versão original em Chinês](../../zh/includes.zh/html/)


* [Versão em inglês](../../en/includes.en/html/)


* (° 1 ° 1 ° 1 ° 1 ° 1 ° 1 ° 1 ° French Versão traduzida por Google](../../fr/includes.fr/html/)




# IMP (Plataforma de meio genético) (ver imp_system.h)

## Conceitos Básicos
A programação T20 / T21 é baseada nos seguintes conceitos:
1. Periférico (= Dispositivo)  
    O periférico completa uma função. Exemplos:
     *  Fonte de quadro: finaliza a saída de dados de vídeo.
     *  Codificador: completa a codificação de vídeo ou a função de codificação de imagem.
2. Grupo  
    O grupo é a menor unidade de entrada de dados. Um dispositivo pode ter vários grupos e cada grupo pode receber apenas um canal de entrada de dados. O grupo pode ter vários resultados.  
    O grupo também é um recipiente para funções específicas "". Veja a explicação na seção do canal para mais detalhes.
3. Saída  
    A saída é a menor unidade de saída de dados por grupo. Um grupo pode ter várias saídas e cada saída pode produzir apenas um canal de dados.
4. Célula  
    A célula se refere a uma coleção que contém informações sobre o dispositivo, o grupo e a saída. É apresentado na estrutura de dados IMPCell.
A célula é usada principalmente para Bind (@ref bind). De acordo com a definição de Dispositivo, Grupo e Saída, Saída é o nó para saída de dados e Grupo é o nó para entrada de dados.
No Bind, o índice de célula do nó de saída de dados está na saída de saída e o índice de célula do nó de entrada de dados está no grupo de entrada (de modo que a célula, entrada de dados de saída é um valor sem sentido).
5. Canal  
    O canal geralmente se refere a uma unidade com uma única função. O canal recebe uma função específica ao ser criada (a instanciação).  
    Por exemplo:  
     -  Para o codificador, um canal complementa o código H264 ou a função de codificação JPEG. O tipo de função de codificação específica (, parâmetro) é especificado ao criar o canal


     -  Para IVS, um canal completa a função de um algoritmo específico e parâmetros de tipo algorítmico específicos são especificados ao criar o canal


     -  Para OSD, há uma região semelhante ao Canal, a região é uma área de sobreposição específica, que pode ser PIC (imagem), COBERTURA (, fechamento)e assim por diante .


     -  Para FrameSource, um canal produz uma imagem original e o canal FrameSource é na verdade um grupo


     
     O canal, como unidade funcional, geralmente deve ser registrado no grupo (além do FrameSource) para receber dados. Após o canal ser registrado no grupo, ele receberá os dados inseridos pelo grupo.

    O número de canais que podem ser gravados pelo grupo de vários dispositivos também é diferente.

## Módulos de ligação (Ligação)

Assim que dois grupos forem conectados pelo Bind, os dados do grupo de origem serão enviados automaticamente ao grupo de destino.  
Como o grupo é a menor unidade de entrada de dados e a saída é a menor unidade de saída de dados, o deviceID, groupID e outputID de srcCell em ambos os parâmetros de IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) válido.  

Embora dstCell seja válido apenas para deviceID e groupID, outputID não faz sentido como uma entrada de dados.

Exemplo 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* é gerado um grupo que gera um link do FrameSource para o Encoder.


* Dois canais são gravados no Grupo de Codificadores, portanto, o Grupo de Codificadores tem duas saídas H264 e JPEG.



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
Este é um programa Bind típico: um fluxo de código de dois canais.
 * FrameSource tem duas saídas, a saber, o stream principal Channel0 (1280x720) e o stream escravo Channel1 (640x360).
   *   Fluxo principal: Channel0 Bind OSD Group.0 do FrameSource, OSD Group.0 Bind Encoder Group.0. Entre eles: 
       * OSD Group.0 gravou duas regiões que são usadas para exibir informações de data e hora e string respectivamente
       * Encoder Group .0 gravou dois canais. , que são codificação H264 e codificação JPEG, respectivamente. Entre eles, se o tamanho da imagem do canal de codificação JPEG não corresponder ao parâmetro de entrada (do FrameSource Channel0), então será dimensionado (software em T10) ) atingir o objetivo de capturar em qualquer resolução.
       
Notas:
* é recomendado que todas as operações de link sejam realizadas durante a inicialização do sistema.
* As operações Bind e UnBind não podem ser chamadas dinamicamente após _FrameSource_ ser ativado. O UnBind é feito somente após a desativação _FrameSource_.

## Funções

### int IMP\_Sistema\_Init (vazio )
Inicialização do sistema IMP.
retorna 0 se for bem-sucedido.
Após esta chamada API, a estrutura básica de dados será inicializada, mas o hardware não será inicializado.
Atenção: Esta função deve ser chamada para inicialização antes de qualquer outra operação.
### int IMP_System_Saída (vazio)

Após chamar esta função, toda a memória e IMP _handles_ serão liberados e o hardware será desligado. 
Nota: Depois de chamar este API, se você quiser usar o IMP novamente, é necessário reiniciar o sistema IMP.

### int64_t IMP_Sistema_GetTimeStamp (void)

Obtenha o carimbo de data / hora do sistema IMP em microssegundos.  
Retorno: tempo em microssegundos.

### int IMP_System_RebaseTimeStamp (bases int64_t)
Defina o carimbo de data / hora do sistema IMP em microssegundos.  
Retorno: 0 se for bem-sucedido.

### uint32_t IMP_Sistema_ReadReg32 (uint32_t u32Addr)

Leia o valor de um registro de 32 bits.  

### em branco IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Grave o valor no registro de 32 bits.

Nota: Por favor, chame esta API com cuidado e verifique o significado do registro, caso contrário, pode causar erros de sistema.

### int IMP_System_GetVersion (IMPVersão * pstVersion) 

Obtenha o número da versão do sistema IMP.

### const char * IMP_System_GetCPUInfo (vazio)
Obtenha informações sobre o modelo de CPU.  
Nota: O valor de retorno é uma string do modelo da CPU, por exemplo, para T10 há "T10"e "T10-Lite".

### int IMP_System_Ligação (IMPCell * srcCell, IMPCell * dstCell)

Link entre a célula de origem e o destino.

Nota 1: De acordo com os conceitos de Dispositivo, Grupo e Saída, cada dispositivo pode ter vários grupos, e cada grupo pode ter várias saídas, Grupo é usado como interface de entrada do dispositivo e Saída é usado como interface de produto do dispositivo. Portanto, o link realmente conecta uma determinada saída do dispositivo de saída a um determinado Grupo do dispositivo de entrada.

Nota 2: Após um link bem-sucedido, os dados gerados por srcCell (Saída) serão automaticamente transmitidos ao Grupo de Célula de destino ().

### int IMP_System_UnBind (IMPCell * srcCell, IMPCell * dstCell)
Desagrupe as origens e destinos. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Recupera informações da célula de origem relacionadas ao destino.




