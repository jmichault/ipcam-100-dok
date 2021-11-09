---
lang: ms
lang-niv: auto
lang-ref: 051-IMP-programigo_gvidilo
layout: page
title: 'Panduan Pengaturcaraan   _IMP_'
---


Dokumentasi API boleh dilihat di sini:   
* [  Versi asal dalam Bahasa Cina  ](../../zh/includes.zh/html/)  


* [  Bahasa Inggeris  ](../../en/includes.en/html/)  


* [  Versi Perancis Diterjemahkan oleh Google  ](../../fr/includes.fr/html/)  




# _IMP_   \(  _Ingenic Media Platform_  \)   \( lihat   _imp\_system.h_  \)

## konsep asas
Program T20 / T21 didasarkan pada konsep-konsep berikut:  
 1. Peranti   \( =  _Device_  \)    
 Peranti melengkapkan fungsi. Contoh:  
       *    _Framesource_ : Lengkapkan output klip video.  
       *    _Encoder_ : Lengkapkan kod video atau fungsi kod imej.  
 2. Kumpulan   \( =  _Group_  \)    
 Kumpulan ialah unit input data terkecil. Peranti boleh mempunyai pelbagai kumpulan dan setiap kumpulan boleh menerima hanya satu saluran input data. Kumpulan boleh mempunyai beberapa keputusan.   
      Kumpulan juga merupakan bekas untuk fungsi   " khusus  ". Lihat penjelasan di bahagian saluran untuk maklumat lanjut.  
 3. Eligo   \( =  _Output_  \)    
 output adalah unit output data terkecil bagi setiap kumpulan.    
 Saluran biasanya berkaitan dengan satu unit fungsi tunggal.    
 Sebagai contoh:   
     -  Untuk CODEL, Saluran melengkapkan fungsi   _H264_   atau kod   _JPEG_.  


     -  Untuk   _IVS_, saluran melengkapkan fungsi algoritma tertentu dan parameter algoritma tertentu yang ditentukan semasa membuat saluran 


     -  Untuk  _OSD_, terdapat rantau yang serupa dengan   _Channel_, sebuah rantau adalah kawasan yang supermetated tertentu yang boleh menjadi Atas   \( Image  \) Cover   \( Occlusion  \), dll.  


     -  Untuk   _FrameSource_, saluran menghasilkan imej asal dan saluran   _FrameSource_   sebenarnya adalah kumpulan  


    
       Saluran, sebagai unit berfungsi, biasanya dipelihara dalam kumpulan   \( kecuali   _FrameSource_  \) menerima data.  

    Bilangan saluran yang dapat dirakam oleh kumpulan pelbagai peranti juga berbeza.

## Pautan Modul   \(  _Bind_  \)

Selepas dua kumpulan dikaitkan dengan   _Bind_, data dari kumpulan sumber secara automatik akan menghantar ke destinasi.    
 Oleh kerana kumpulan itu adalah unit input data terkecil dan output adalah unit output data terkecil,   _deviceID_,   _groupID_   dan   _outputID_    _srcCell_   dalam dua parameter   _IMP\_System\_Bind \(IMPCell * srcCell, IMPCell * dstCell\)_   adalah sah.    

Walaupun   _dstCell_   hanya sah untuk   _deviceID_   dan   _groupID_,   _outputID_   tidak masuk akal seperti pintu masuk data.  

Contoh 1: 
```
IMPCell fs_chn0 = {DEV_ID_FS, 0, 0};    // FrameSource deviceID: DEV_ID_FS groupID: 0 outputID: 0
IMPCell enc_grp0 = {DEV_ID_ENC, 0, 0}; // ENC deviceID: DEV_ID_ENC groupID : 0 outputID: 0, où le troisième paramètre de enc_grp0 n'a pas de sens. 
int ret = IMP_System_Bind (& fs_chn0, & enc_grp0);
if(ret <0>)
  printf ("Bind FrameSource Channel0 and Encoder Group0 failed \ n");

```
Keputusan:    
 *  Kumpulan menjana satu kumpulan yang menghasilkan pautan dari Framesource to Encoder. 

* Dua saluran didaftarkan dalam kumpulan Encoder, jadi kumpulan encoder mempunyai dua produk:   _H264_   dan   _JPEG_.  



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
Memohon adalah aplikasi biasa   _Bind_ : Kod dua saluran.  

Nota:  
  *   Adalah disyorkan bahawa semua operasi pautan dibuat apabila memulakan sistem.  

## Fungsi

### _int IMP\_System\_Init \(void \)_
Permulaan sistem   _IMP_.  
### Permulaan sistem _int IMP\_System\_Exit \(void\)_. \_

Selepas memanggil fungsi ini, semua memori dan   _handles_   _IMP_   akan dikeluarkan, dan unit perkakasan akan ditutup.  

### Selepas memanggil fungsi ini, semua memori dan _int64\_t IMP\_System\_GetTimeStamp \(void\)_ \_ akan dikeluarkan, dan unit perkakasan akan ditutup.  \(

Dapatkan medan masa sistem   _IMP_   dalam mikrosecond.    
 Pulangan: Masa di mikroekond. 

### Dapatkan medan masa sistem _int IMP\_System\_RebaseTimeStamp \(bases int64\_t\)_ dalam mikrosecond. \_ Pulangan: Masa di mikroekond.  \(
Tentukan Sistem Timestamp   _IMP_   dalam Mikroseconds.    
 Pulangan: 0 jika berjaya. 

### Tentukan Sistem Timestamp _uint32\_t IMP\_System\_ReadReg32 \(uint32\_t u32Addr\)_ dalam Mikroseconds. \_ Pulangan: 0 jika berjaya. \_

Baca nilai daftar 32-bit.  

### _void IMP\_System\_WriteReg32 \(uint32_  t regaddr, nilai uint32  _t\)_
Tulis nilai dalam pendaftaran 32-bit.  

Catatan: Sila panggil API ini dengan teliti dan periksa makna pendaftaran, jika tidak, ia boleh menyebabkan kesalahan sistem.

### _int IMP_  sistem  _GetVersion \(IMPVersion * pstVersion\)_

Dapatkan sistem sistem   _IMP_.  

### _const char * IMP_  sistem  _GetCPUInfo \(void\)_
Dapatkan maklumat mengenai model CPU.  
Catatan: Nilai kembali adalah rentetan model CPU, misalnya, untuk T10 terdapat "T10"dan "T10-Lite".

### _int IMP_  sistem   \(

Pautan antara sel sumber dan destinasi.

Catatan 1: Menurut konsep Perangkat, Kelompok dan Keluaran, setiap perangkat dapat memiliki beberapa kelompok, dan setiap kelompok dapat memiliki beberapa output, Grup digunakan sebagai antara muka input Perangkat, dan Keluaran digunakan sebagai antara muka produk Peranti. Oleh itu pautan itu sebenarnya menghubungkan output peranti output tertentu ke Kumpulan peranti input tertentu.

Nota 2: Selepas pautan yang berjaya, data yang dihasilkan oleh   _srcCell_   (  ELEGO  )   akan dipindahkan secara automatik ke destinasi   (  Kumpulan  ).  

### _int IMP_  sistem   \(
Nyahpasang sumber dan destinasi. 

### _int IMP_  sistem   \(

Mengambil maklumat dari sel sumber yang berkaitan dengan tujuan.

