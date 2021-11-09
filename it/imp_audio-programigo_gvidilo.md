---
lang: it
lang-niv: auto
lang-ref: 053-audio-programigo_gvidilo
layout: page
title: 'Guida alla programmazione del suono'
---

# Imp  _Audio \(voir imp_  audio.h  \)

Modulo audio, inclusa registrazione e riproduzione, codec audio, impostazioni di volume e guadagno, cancellazione dell'eco, guadagno automatico e altre funzioni.

## Presentazione
* La funzione audio comprende 5 moduli: ingresso audio, uscita audio, cancellazione audio, codifica audio e decodifica audio.


 * Tra questi, l'ingresso audio e l'uscita audio hanno il concetto di dispositivo e canale. Uno dei MIC è considerato un dispositivo e un MIC può avere più ingressi di canale.


 * Lo stesso SPK è considerato un dispositivo di riproduzione e un SPK può anche avere più uscite di canale.


 * La versione lunare dell'API audio supporta solo un canale per dispositivo.


 * La cancellazione dell'eco si trova nell'interfaccia di ingresso audio e le istruzioni specifiche si riflettono nella descrizione della funzione.


 * Codifica audio: l'attuale API audio supporta la codifica audio nei formati PT_G711A, PT_G711U e PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

   

 * Decodifica audio: l'attuale API audio supporta la decodifica audio nei formati PT_G711A, PT_G711U e PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

   

