---
lang: bn
lang-niv: auto
lang-ref: 052-ISP-programigo_gvidilo
layout: page
title: 'ভিডিও প্রোগ্রামিং গাইড'
---

# _IMP\_ISP_   \(   _imp\_isp.h\_) দেখুন
চিত্র প্রক্রিয়াজাতকরণ। মূলত চিত্রের এফেক্টস, মোড সুইচ এবং রেকর্ডিং, সংবেদক সংযোজন এবং অপসারণের সেটিংস অন্তর্ভুক্ত রয়েছে।

আইএসপি মডিউলটির ডেটা প্রবাহের সাথে কোনও সম্পর্ক নেই এবং এটি সংযুক্ত হওয়ার দরকার নেই, এটি কেবল কার্যকর কনফিগারেশন এবং সেন্সর নিয়ন্ত্রণের ক্ষেত্রে কাজ করে।

## অ্যাক্টিভেশন

আইএসপি মডিউলটি সক্রিয় করার পদক্ষেপগুলি নিম্নরূপ:
* পদক্ষেপ 1: একটি আইএসপি মডিউল তৈরি করুন

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* পদক্ষেপ 2: সেন্সর যুক্ত করুন, সেন্সর ড্রাইভারটি এই অপারেশনের আগে কার্নেলের সাথে যুক্ত হয়েছিল।



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
* ধাপ 3: সেন্সরটি সক্রিয় করুন, এটি চিত্রগুলি তৈরি করতে শুরু করবে। .



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* পদক্ষেপ 4: সেটিংস সক্রিয় করুন:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* ধাপ 5: একটি আইএসপি ডিবাগিং ইন্টারফেসটি কল করুন: একটি আইএসপি ডিবাগিং ইন্টারফেসের ডকুমেন্টেশনটি পড়ুন। .




## আইএসপি মডিউল নিষ্ক্রিয়করণ

আইএসপি মডিউলটি আনইনস্টল করার পদক্ষেপগুলি নিম্নরূপ:
* পদক্ষেপ 1: আইএসপি কনফিগারেশন অক্ষম করুন

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
* পদক্ষেপ 2: সেন্সর বন্ধ করুন।   \( ফ্রেমগুলি এই ক্রিয়াকলাপের আগে বন্ধ করা আবশ্যক  \)  



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* পদক্ষেপ 3: সেন্সরগুলি অপসারণ করুন, সেন্সরগুলি এই অপারেশনের আগে বন্ধ করতে হবে।



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* ধাপ 4: আইএসপি মডিউলটি পরিষ্কার করুন, এই ক্রিয়াকলাপের আগে সমস্ত সেন্সরগুলি সরানো আবশ্যক। .



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## কার্য তালিকা

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

