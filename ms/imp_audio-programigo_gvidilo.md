# IMP_Audio (voir imp_audio.h)

Modul audio, termasuk rakaman dan main balik, kodek audio, tetapan kelantangan dan keuntungan, pembatalan gema, keuntungan automatik dan fungsi lain.

## Pembentangan
* Fungsi suara merangkumi 5 modul: input audio, output audio, pembatalan audio, pengekodan audio dan penyahkodan audio.


 * Antaranya, input audio dan output audio mempunyai konsep peranti dan saluran. Salah satu MIC dianggap sebagai peranti, dan MIC dapat memiliki banyak input saluran.


 * SPK yang sama dianggap sebagai alat pembiakan, dan SPK juga dapat memiliki banyak output saluran.


 * Versi audio API audio hanya menyokong satu saluran setiap peranti.


 * Pembatalan echoa terdapat di antara muka input audio dan arahan khusus dicerminkan dalam keterangan fungsi.


 * Pengekodan audio: API audio semasa menyokong pengekodan audio dalam format PT_G711A, PT_G711U dan PT_G726. Si vous devez ajouter une nouvelle méthode d'encodage, vous devez enregistrer l'encodeur.
   

   

 * Penyahkodan audio: API audio semasa menyokong penyahkodan audio dalam format PT_G711A, PT_G711U dan PT_G726. Si vous devez ajouter une nouvelle méthode de décodage, vous devez enregistrer le décodeur.
   

   

