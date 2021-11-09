---
lang: ms
lang-niv: auto
lang-ref: 052-ISP-programigo_gvidilo
layout: page
title: 'Panduan pengaturcaraan video'
---

# _IMP\_ISP_   \( lihat   _imp\_isp.h\_)
Pemprosesan imej. Terutamanya merangkumi tetapan kesan gambar, pertukaran mod dan rakaman, penambahan dan penghapusan sensor.

Modul ISP tidak ada kaitan dengan aliran data dan tidak perlu dihubungkan, ia hanya berfungsi dari segi konfigurasi kesan dan kawalan sensor.

## Pengaktifan

Langkah-langkah untuk mengaktifkan modul ISP adalah seperti berikut:
* langkah 1: Buat modul ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Langkah 2: Tambahkan sensor, pemacu sensor ditambahkan ke kernel sebelum operasi ini.



```
  IMPSensorInfo sensor[2];
  sensor[0].name = "xxx";
  sensor[0].cbus_type = SENSOR_CONTROL_INTERFACE_I2C; // OU SENSOR_CONTROL_INTERFACE_SPI
  sensor[0].i2c = {
    .type = "xxx", // nom du périphérique I2C, qui doit être cohérent avec le nom de la structure i2c_device_id dans le pilote du capteur.
    .addr = xx, // adresse I2C
    .i2c_adapter_id = xx, // ID du contrôleur I2C où se trouve le capteur
  }
  /* OU
   * sensor[0].spi = {
   *   .modalias = "xx", // nom du périphérique SPI, doit être cohérent avec le nom de la structure spi_device_id dans le pilote du capteur.
   *     .bus_num = xx, // adresse du bus SPI
   *}
   */
  sensor[1].name[0]=0; // pas d'autre capteur
  ret = IMP_ISP_AddSensor (& sensor); 
  if (ret <0) {
    printf ("Impossible d'enregistrer le capteur \n");
    return -1;
  }
```
* Langkah 3: Aktifkan sensor, ia akan mula menghasilkan imej. 



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Langkah 4: Aktifkan tetapan:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Langkah 5: Panggil antara muka debugging ISP: Sila rujuk dokumentasi antara muka debugging ISP. 




## Modul ISP menyahaktifkan

Langkah-langkah untuk menyahpasang modul ISP adalah seperti berikut:
* langkah 1: Lumpuhkan konfigurasi ISP

```
int ret = 0;
  IMPSensorInfo sensor[2];
  sensor[0].name = "xxx";
  sensor[1].name[0] = 0;
  ret = IMP_ISP_DisableTuning ();
  if (ret <0) {
  printf ("Impossible de désactiver le réglage \n");
  return -1;
 }
```
* Langkah 2: Tutup sensor.   \( bingkai mesti ditutup sebelum operasi ini  \)  



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Langkah 3: keluarkan sensor, sensor mesti ditutup sebelum operasi ini.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Langkah 4: Bersihkan modul ISP, semua sensor mesti dikeluarkan sebelum operasi ini. 



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## senarai fungsi

```
int IMP_ISP_Open(void);
int IMP_ISP_Close(void);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(void);
int IMP_ISP_DisableSensor(void);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *value);
int IMP_ISP_EnableTuning(void);
int IMP_ISP_DisableTuning(void);
int IMP_ISP_Tuning_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Tuning_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Tuning_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);
int IMP_ISP_Tuning_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);
int IMP_ISP_Tuning_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_SetBrightness(unsigned char bright);
int IMP_ISP_Tuning_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(unsigned char contrast);
int IMP_ISP_Tuning_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(unsigned char sharpness);
int IMP_ISP_Tuning_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(unsigned char sat);
int IMP_ISP_Tuning_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *path);
int IMP_ISP_Tuning_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_SetISPHflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
int IMP_ISP_Tuning_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy strategy);
int IMP_ISP_Tuning_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Tuning_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));
int IMP_ISP_Tuning_SetHiLightDepress(uint32_t strength);
int IMP_ISP_Tuning_SetTemperStrength(uint32_t ratio);
int IMP_ISP_Tuning_SetSinterStrength(uint32_t ratio);
int IMP_ISP_Tuning_SetDPStrength(uint32_t ratio);
int IMP_ISP_Tuning_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);
```

