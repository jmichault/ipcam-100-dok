---
lang: pt
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Guia de programação sólida'
---

# Áudio IMP_Audio (voir imp_.h)

Módulo de áudio, incluindo gravação e reprodução, codec de áudio, configurações de volume e ganho, cancelamento de eco, ganho automático e outras funções.

## Apresentação
* A função de som inclui 5 módulos: entrada de áudio, saída de áudio, cancelamento de áudio, codificação de áudio e decodificação de áudio.


 * Dentre eles, a entrada e a saída de áudio possuem o conceito de dispositivo e canal. Um dos MICs é considerado um dispositivo e um MIC pode ter várias entradas de canal.


 * O mesmo SPK é considerado um dispositivo de reprodução e um SPK também pode ter várias saídas de canal.


 * A versão lunar da API de áudio suporta apenas um canal por dispositivo.


 * O cancelamento de eco é encontrado na interface de entrada de áudio e instruções específicas são refletidas na descrição da função.


 * Codificação de áudio: A API de áudio atual suporta codificação de áudio nos formatos PT_G711A, PT_G711U e PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

   

 * Decodificação de áudio: A API de áudio atual suporta decodificação de áudio nos formatos PT_G711A, PT_G711U e PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

   

