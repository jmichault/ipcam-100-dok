---
lang: es
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Guía de programación de sonido'
---

# Imp  _Audio \(voir imp_  audio.h  \)

Módulo de audio, que incluye grabación y reproducción, códec de audio, ajustes de volumen y ganancia, cancelación de eco electrónico, ganancia automática y otras funciones.

## Presentación
* La función de sonido incluye 5 módulos: entrada de audio, salida de audio, cancelación de audio, codificación de audio y decodificación de audio.


 * Entre ellos, la entrada de audio y la salida de audio tienen el concepto de dispositivo y canal. Uno de los MIC se considera un dispositivo y un MIC puede tener múltiples entradas de canal.


 * El mismo SPK se considera un dispositivo de reproducción, y un SPK también puede tener salidas de múltiples canales.


 * La versión lunar de la API de audio solo admite un canal por dispositivo.


 * La cancelación de eco se encuentra en la interfaz de entrada de audio y las instrucciones específicas se reflejan en la descripción de la función.


 * Codificación de audio: la API de audio actual admite la codificación de audio en formatos PT_G711A, PT_G711U y PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

   

 * Decodificación de audio: la API de audio actual admite la decodificación de audio en formatos PT_G711A, PT_G711U y PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

   

