# IMP_ISP (voir imp_isp.h)
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
* Langkah 3: Aktifkan sensor, ia akan mula menghasilkan gambar.



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
* Langkah 5: Memohon antaramuka debug ISP: Sila rujuk dokumentasi antara muka debug ISP.




## Melumpuhkan modul ISP

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
* Langkah 2: Tutup sensor. (FrameSource mesti ditutup sebelum operasi ini)



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

int IMP_ISP_Terbuka(kosong);
int IMP_ISP_Tutup(kosong);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(kosong);
int IMP_ISP_DisableSensor(kosong);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t value);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *nilai);
int IMP_ISP_EnableTuning(blank);
int IMP_ISP_DisableTuning(kosong);
int IMP_ISP_Konfigurasi_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Konfigurasi_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Konfigurasi_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Konfigurasi_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Konfigurasi_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Konfigurasi_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(Mod IMPISPTuningOpsMode);
int IMP_ISP_Setting_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(Mode IMPISPSceneMode);
int IMP_ISP_Pengaturan_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(mod IMPISPColorfxMode);
int IMP_ISP_Tetapan_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Tetapkan Kecerahan(tanda tidak bernama terang);
int IMP_ISP_Konfigurasi_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(kontras watak tanpa nama);
int IMP_ISP_Konfigurasi_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(ketajaman ketajaman tanpa nama);
int IMP_ISP_Konfigurasi_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_Set Ketepuan(tanda tanpa nama (hingga 22 °);
int IMP_ISP_Konfigurasi_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Configuration_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *path);
int IMP_ISP_Persediaan_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Tetapkan ISPHflip(IMPISPTuningOpsMode mod);
int IMP_ISP_Konfigurasi_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPV Flip(mod IMPISPTuningOpsMode);
int IMP_ISP_Konfigurasi_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(Mod IMPISPRunningMode);
int IMP_ISP_Konfigurasi_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategi(Strategi IMPISPAeStrategi);
int IMP_ISP_Konfigurasi_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *range);
int IMP_ISP_Konfigurasi_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Konfigurasi_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Konfigurasi_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Konfigurasi_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_) °) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop() kosong (*cb)(kosong));
int IMP_ISP_Konfigurasi_SetHiLightDepress(uint32_daya t);
int IMP_ISP_Konfigurasi_SetTemperStrength(uint32_nisbah t);
int IMP_ISP_Konfigurasi_SetSinterStrength(uint32_nisbah t);
int IMP_ISP_Konfigurasi_SetDPStrength(uint32_nisbah t);
int IMP_ISP_Konfigurasi_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


