---
lang: ar
lang-niv: auto
lang-ref: 052-ISP-programigo_gvidilo
layout: page
title: 'دليل برمجة الفيديو'
---

# IMP_ISP (voir imp_isp.h)
معالجة الصورة. يتضمن بشكل أساسي إعدادات تأثيرات الصورة ومفتاح الوضع والتسجيل وإضافة وإزالة المستشعر.

لا علاقة لوحدة ISP بتدفق البيانات ولا تحتاج إلى الاتصال ، فهي تعمل فقط من حيث تكوين التأثير والتحكم في المستشعر.

## التنشيط

خطوات تنشيط وحدة ISP هي كما يلي:
* الخطوة 1: إنشاء وحدة ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* الخطوة 2: إضافة جهاز استشعار ، تمت إضافة برنامج تشغيل المستشعر إلى النواة قبل هذه العملية.



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
* الخطوة 3: قم بتنشيط المستشعر ، وسيبدأ في إنتاج الصور.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* الخطوة 4: تنشيط الإعدادات:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* الخطوة 5: استدعاء واجهة تصحيح أخطاء ISP: يرجى الرجوع إلى وثائق واجهة تصحيح أخطاء ISP.




## تعطيل وحدة ISP

خطوات إلغاء تثبيت وحدة ISP كما يلي:
* الخطوة 1: تعطيل تكوين ISP

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
* الخطوة الثانية: أغلق المستشعرات. (يجب إغلاق مصدر الإطار قبل هذه العملية)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* الخطوة الثالثة: قم بإزالة المستشعرات ، يجب إغلاق المستشعرات قبل هذه العملية.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* الخطوة 4: قم بتنظيف وحدة ISP ، يجب إزالة جميع أجهزة الاستشعار قبل هذه العملية.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## قائمة الوظائف

int IMP_ISP_فتح(فارغ)؛
int IMP_ISP_إغلاق(فارغ)؛
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo)؛
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo)؛
int IMP_ISP_EnableSensor(فارغ)؛
int IMP_ISP_DisableSensor(فارغ)؛
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_قيمة t)؛
الباحث IMP_ISP_GetSensorRegister(uint32_t reg, uint32_ر *بقيمة)؛
int IMP_ISP_EnableTuning(فارغ)؛
الباحث IMP_ISP_DisableTuning(فارغة)؛
الباحث IMP_ISP_تكوين_SetSensorFPS(uint32_ر إطارا في الثانية (درجة 63 درجة) ر إطارا في الثانية (درجة 65 درجة) ISP_Tuning_GetSensorFPS(uint32_t *fps_الأسطوانات، uint32_t *fps_دن)؛
الباحث IMP_ISP_تكوين_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr)؛
الباحث IMP_ISP_تكوين_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP (درجة 101 درجة) GetRawDRC (درجة 103 درجة) IMPISPDrcAttr (درجة 104 درجة) pinfo (درجة 105 درجة).
int IMP_ISP_التكوين_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo)؛
int IMP_ISP_التكوين_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo)؛
int IMP_ISP_التكوين_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(وضع IMPISPTuningOpsMode)؛ (° 147 درجة) الباحث IMP_ISP_وضع (درجة 150 درجة) ISP (درجة 156 درجة) SetSceneMode (درجة 158 درجة) واسطة IMPISPSceneMode (درجة 159 درجة).
int IMP_ISP_الإعداد_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(وضع IMPISPColorfxMode)؛
int IMP_ISP_الإعداد_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_ضبط السطوع(إشارة بدون اسم مشرق)؛ (° 186 درجة) الباحث IMP (درجة 187 درجة) تكوين (درجة 189 درجة) ISP (درجة 195 درجة) SetContrast (درجة 197 درجة) على النقيض من شخصية مجهول (درجة 198 درجة).
int IMP_ISP_التكوين_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(الحدة بدون اسم)؛
int IMP_ISP_التكوين_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_ضبط التشبع(علامة غير مسماة (إلى 22 °)؛
int IMP_ISP_التكوين_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode)؛
int IMP_ISP_التكوين_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(مسار شار *)؛
int IMP_ISP_الإعداد_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_اضبط ISPHflip(IMPISPTuningOpsMode الوضع)؛ (° 272 درجة) الباحث IMP (درجة 273 درجة) تكوين (درجة 275 درجة) ISP (درجة 281 درجة) SetISPVflip (درجة 283 درجة) وضع IMPISPTuningOpsMode (درجة 284 درجة).
int IMP_ISP_التكوين_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(وضع IMPISPRunningMode)؛
int IMP_ISP_التكوين_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(استراتيجية IMPISPAeStrategy)؛
int IMP_ISP_التكوين_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(نطاق IMPISPGamma *)؛ (° 325 درجة) الباحث IMP (درجة 326 درجة) تكوين (درجة 328 درجة) ISP (درجة 334 درجة) SetAeComp (درجة 336 درجة) الباحث شركات (° 337 درجة).
int IMP_ISP_التكوين_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr)؛ (° 352 درجة) الباحث IMP (درجة 353 درجة) تكوين (درجة 355 درجة) ISP (درجة 361 درجة) AE (درجة 363 درجة) عبد اللطيف (درجة 367 درجة) ISP (درجة 371 درجة) AE (درجة 373 درجة) عبد اللطيف_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb)؛
int IMP_ISP_التكوين_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_) درجة) ISP (درجة 438 درجة) SetMaxDgain (درجة 440 درجة) uint32 (درجة 441 درجة) ISP (درجة 445 درجة) GetMaxDgain (درجة 447 درجة) uint32 (درجة 448 درجة) ISP (درجة 453 درجة) SetVideoDrop(تفريغ (درجة 456 درجة) CB (° 457 درجة) تفريغ (درجة 458 درجة). (° 459 درجة) الباحث IMP (درجة 460 درجة) تكوين (درجة 462 درجة) قوة ر (درجة 465 درجة).
int IMP_ISP_التكوين_SetTemperStrength(uint32_نسبة t)؛
int IMP_ISP_التكوين_SetSinterStrength(uint32_نسبة t)؛ (° 480 درجة) الباحث IMP (درجة 481 درجة) تكوين (درجة 483 درجة) تي نسبة (درجة 486 درجة).
int IMP_ISP_التكوين_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr)؛ (° 500 درجة)


