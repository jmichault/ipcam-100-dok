---
lang: de
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Solide Programmieranleitung.'
---

# IMP_Audio (voir imp_audio.h)

Audiomodul, einschließlich Aufnahme und Wiedergabe, Audio-Codec, Lautstärke- und Verstärkungseinstellungen, E-Echo-Unterdrückung, automatische Verstärkung und andere Funktionen.

## Präsentation
* Die Soundfunktion umfasst 5 Module: Audioeingang, Audioausgang, Audioauslöschung, Audiocodierung und Audiodecodierung.


 * Unter diesen haben Audioeingang und Audioausgang das Konzept von Gerät und Kanal. Eine der MICs wird als Gerät betrachtet, und eine MIC kann mehrere Kanaleingänge haben.


 * Dieselbe SPK wird als Zuchtgerät betrachtet, und eine SPK kann auch mehrere Kanalausgänge haben.


 * Die Mondversion der Audio-API unterstützt nur einen Kanal pro Gerät.


 * Die Echokompensation befindet sich in der Audioeingangsschnittstelle, und spezifische Anweisungen sind in der Beschreibung der Funktion enthalten.


 * Audiokodierung: Die aktuelle Audio-API unterstützt die Audiokodierung in den Formaten PT_G711A, PT_G711U und PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

   

 * Audio-Decodierung: Die aktuelle Audio-API unterstützt die Audio-Decodierung in den Formaten PT_G711A, PT_G711U und PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

   

