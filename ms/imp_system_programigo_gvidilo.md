

# IMP (Platform Media Ingenic) (lihat imp_system.h)

## konsep asas
Pengaturcaraan T20 / T21 berdasarkan konsep berikut:
1. Periferal (= Peranti)  
    Periferal melengkapkan fungsi. Contoh:
     *  Sumber bingkai: mengakhiri output data video.
     *  Encoder: melengkapkan fungsi pengekodan video atau pengekodan gambar.
2. Kumpulan  
    Kumpulan adalah unit input data terkecil. Peranti boleh mempunyai beberapa kumpulan dan setiap kumpulan hanya dapat menerima satu saluran input data. Kumpulan tersebut dapat memperoleh beberapa hasil.  
    Kumpulan ini juga merupakan wadah untuk fungsi "tertentu". Lihat penjelasan di bahagian saluran untuk maklumat lebih lanjut.
3. Keluar  
    Output adalah unit output data terkecil bagi setiap kumpulan. Satu kumpulan boleh mempunyai beberapa output dan setiap output hanya dapat menghasilkan satu saluran data.
4. Sel  
    Sel merujuk kepada koleksi yang mengandungi maklumat mengenai peranti, kumpulan, dan keluarannya. Ia disajikan dalam struktur data IMPCell.
Sel digunakan terutamanya untuk Bind (@ref bind). Menurut definisi Peranti, Kumpulan dan Output, Output adalah node untuk output data dan Group adalah node untuk input data.
Di Bind, indeks sel dari simpul output data berada pada output Output, dan indeks sel dari simpul input data berada pada kelompok input (sehingga sel, input data Output adalah nilai tidak masuk akal).
5. Saluran  
    Saluran umumnya merujuk kepada unit dengan fungsi tunggal. Saluran menerima fungsi tertentu ketika dibuat (instantiasi).  
    Contohnya:  
     -  Untuk pengekod, satu saluran melengkapkan kod H264 atau fungsi pengekodan JPEG. Jenis fungsi pengekodan khusus (, parameter) ditentukan semasa membuat saluran


     -  Untuk IVS, saluran menyelesaikan fungsi algoritma tertentu dan parameter jenis algoritma tertentu ditentukan semasa membuat saluran


     -  Untuk OSD, terdapat kawasan yang serupa dengan Saluran, wilayah adalah kawasan lapisan khas, yang boleh berupa gambar PIC (), penutupan COVER (), dan sebagainya .


     -  Untuk FrameSource, saluran menghasilkan gambar asal dan saluran FrameSource sebenarnya adalah kumpulan


     
     Saluran, sebagai unit berfungsi, umumnya mesti didaftarkan dalam kumpulan (sebagai tambahan kepada FrameSource) untuk menerima data. Setelah saluran didaftarkan dalam kumpulan, ia akan menerima data yang dimasukkan oleh kumpulan.

    Bilangan saluran yang dapat dirakam oleh kumpulan pelbagai peranti juga berbeza.

## Modul pengikat (Ikatan)

Setelah dua kumpulan dihubungkan oleh Bind, data dari kumpulan sumber akan dihantar secara automatik ke kumpulan tujuan.  
Kerana kumpulan adalah unit input data terkecil dan outputnya adalah unit output data terkecil, deviceID, groupID, dan outputID srcCell dalam kedua-dua parameter IMP_System_Bind (IMPCell * srcCell, IMPCell * dstCell) sah.  

Walaupun dstCell hanya berlaku untuk deviceID dan groupID, outputID tidak masuk akal sebagai entri data.

Contoh 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```

* kumpulan dihasilkan yang menghasilkan pautan dari FrameSource ke Encoder.


* Dua saluran direkodkan dalam Kumpulan Encoder, jadi Kumpulan Encoder mempunyai dua output H264 dan JPEG.



Contoh 2:
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
Ini adalah program khas Bind: aliran kod dua saluran.
 * FrameSource mempunyai dua output, iaitu aliran utama Channel0 (1280x720) dan saluran budak Channel1 (640x360).
   *   Aliran utama: FrameSource's Channel0 Bind OSD Group.0, OSD Group.0 Bind Encoder Group.0. Antaranya: 
       * OSD Group.0 merakam dua wilayah yang masing-masing digunakan untuk memaparkan cap waktu dan maklumat rentetan
       * Kumpulan Encoder .0 merakam dua saluran. , yang masing-masing adalah pengekodan H264 dan pengekodan JPEG. Antaranya, jika ukuran gambar saluran pengekodan JPEG tidak sesuai dengan parameter input (dari FrameSource Channel0), maka ia akan skala (perisian pada T10) ) mencapai matlamat untuk menangkap sebarang resolusi.
       
Catatan:
* disarankan agar semua operasi pautan dilakukan semasa inisialisasi sistem.
* Operasi pengikat dan pengikat tidak dapat dipanggil secara dinamik setelah _FrameSource_ diaktifkan. Unbind dilakukan hanya selepas penyahaktifan _FrameSource_.

## Fungsi

### int IMP\_Sistem\_Init (kosong )
Permulaan sistem IMP.
mengembalikan 0 jika berjaya.
Selepas panggilan API ini, struktur data asas akan diinisialisasi, tetapi perkakasan tidak akan diinisialisasi.
Perhatian: Fungsi ini mesti dipanggil untuk memulakan sebelum operasi lain.
### int IMP_System_Keluar (kosong)

Setelah memanggil fungsi ini, semua memori dan IMP _handles_ akan dilepaskan, dan perkakasan akan dimatikan. 
Catatan: Setelah memanggil API ini, jika anda ingin menggunakan IMP sekali lagi, anda perlu menetapkan semula sistem IMP.

### int64_t IMP_Sistem_GetTimeStamp (void)

Dapatkan cap waktu sistem IMP dalam mikrodetik.  
Kembali: masa dalam mikrodetik.

### int IMP_System_asas RebaseTimeStamp (int64_t)
Tetapkan cap waktu sistem IMP dalam mikrodetik.  
Pulangkan: 0 jika berjaya.

### uint32_t IMP_Sistem_ReadReg32 (uint32_t u32Addr)

Baca nilai daftar 32-bit.  

### kosong IMP_System_WriteReg32 (uint32_t regAddr, valeur uint32_t)
Tuliskan nilai ke daftar 32-bit.

Catatan: Sila panggil API ini dengan teliti dan periksa makna pendaftaran, jika tidak, ia boleh menyebabkan kesalahan sistem.

### int IMP_System_GetVersion (IMPVersion * pstVersion) 

Dapatkan nombor versi sistem IMP.

### const char * IMP_System_GetCPUInfo (kosong)
Dapatkan maklumat mengenai model CPU.  
Catatan: Nilai kembali adalah rentetan model CPU, misalnya, untuk T10 terdapat "T10"dan "T10-Lite".

### int IMP_System_Ikatan (IMPCell * srcCell, IMPCell * dstCell)

Pautan antara sel sumber dan destinasi.

Catatan 1: Menurut konsep Perangkat, Kelompok dan Keluaran, setiap perangkat dapat memiliki beberapa kelompok, dan setiap kelompok dapat memiliki beberapa output, Grup digunakan sebagai antara muka input Perangkat, dan Keluaran digunakan sebagai antara muka produk Peranti. Oleh itu pautan itu sebenarnya menghubungkan output peranti output tertentu ke Kumpulan peranti input tertentu.

Catatan 2: Setelah pautan berjaya, data yang dihasilkan oleh srcCell (Output) akan dihantar secara automatik ke Kumpulan sel (destinasi).

### int IMP_System_Unbind (IMPCell * srcCell, IMPCell * dstCell)
Nyahpasang sumber dan destinasi. 

### int IMP_System_GetBindbyDest (IMPCell * dstCell, IMPCell * srcCell)

Mengambil maklumat dari sel sumber yang berkaitan dengan tujuan.




