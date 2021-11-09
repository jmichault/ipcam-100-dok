---
lang: en
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Sound programming Guide'
---

# Imp  _Audio \(voir imp_  Audio.h  \)

Audio module, including recording and playback, audio codec, volume and gain settings, e echo cancellation, automatic gain and other functions.

## Presentation
* The sound function includes 5 modules: audio input, audio output, audio cancellation, audio encoding and audio decoding.


 * Among them, audio input and audio output have the concept of device and channel. One of the MICs is considered a device, and a MIC can have multiple channel inputs.


 * The same SPK is considered a breeding device, and an SPK can also have multiple channel outputs.


 * The lunar version of the audio API only supports one channel per device.


 * Echoa cancellation is found in the audio input interface and specific instructions are reflected in the description of the function.


 * Audio encoding: The current audio API supports audio encoding in PT_G711A, PT_G711U and PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   formats

   

 * Audio decoding: The current audio API supports audio decoding in PT_G711A, PT_G711U and PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   formats

   

