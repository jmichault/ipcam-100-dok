---
lang: fr
lang-niv: fonto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Guide de programmation du son'
---

# IMP_Audio (voir imp_audio.h)

Module audio, comprenant l'enregistrement et la lecture, le codec audio, les paramètres de volume et de gain, l'annulation d'écho, le gain automatique et d'autres fonctions.

## Présentation
* La fonction audio comprend 5 modules: entrée audio, sortie audio, annulation d'écho, encodage audio et décodage audio.
 * Parmi eux, l'entrée audio et la sortie audio ont le concept de périphérique et de canal. L'un des MIC est considéré comme un périphérique et un MIC peut avoir plusieurs entrées de canal.
 * Le même SPK est considéré comme un périphérique de lecture, et un SPK peut également avoir plusieurs sorties de canal.
 * La version actuelle de l'API audio ne prend en charge qu'un seul canal par appareil.
 * L'annulation d'écho se trouve dans l'interface d'entrée audio et les instructions spécifiques sont reflétées dans la description de la fonction.
 * Encodage audio : L'API audio actuelle prend en charge l'encodage audio aux formats PT_G711A, PT_G711U et PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
 * Décodage audio : L'API audio actuelle prend en charge le décodage audio aux formats PT_G711A, PT_G711U et PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
