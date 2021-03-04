# IMP_Audio (voir imp_audio.h)

Audio-modulo, inkluzive de registrado kaj reprodukto, audio-kodeko, volumena kaj gajna agordoj, e echa nuligo, aŭtomata gajno kaj aliaj funkcioj.

## Prezento
* La sonfunkcio inkluzivas 5 modulojn: aŭd-enigo, aŭd-eliga, eoa nuligo, aŭd-kodado kaj aŭd-malkodado.

 * Inter ili, audio-enigo kaj audio-eliro havas la koncepton de aparato kaj kanalo. Unu el la MICoj estas konsiderata aparato, kaj MIC povas havi multoblajn kanalajn enigaĵojn.

 * La sama SPK estas konsiderata reprodukta aparato, kaj SPK ankaŭ povas havi plurajn kanalajn elirojn.

 * La nuna versio de la audio API nur subtenas unu kanalon por aparato.

 * Echoa nuligo troviĝas en la aŭd-eniga interfaco kaj specifaj instrukcioj reflektiĝas en la priskribo de la funkcio.

 * Audio-kodado: La nuna audio-API subtenas audio-kodadon en formatoj PT_G711A, PT_G711U kaj PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

 * Audio-malkodado: La nuna audio-API subtenas son-malkodadon en formatoj PT_G711A, PT_G711U kaj PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

