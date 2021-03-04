# আইএমপি_ISP (voir imp_isp.h)
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
* পদক্ষেপ 3: সেন্সরটি সক্রিয় করুন, এটি চিত্র উত্পাদন শুরু করবে।



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
* পদক্ষেপ 5: আইএসপি ডিবাগিং ইন্টারফেসটি আহ্বান করুন: দয়া করে আইএসপি ডিবাগিং ইন্টারফেস ডকুমেন্টেশন দেখুন।




## একটি আইএসপি মডিউল অক্ষম করা হচ্ছে

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
* পদক্ষেপ 2: সেন্সরগুলি বন্ধ করুন। (এই অপারেশন)এর আগে ফ্রেমসোর্স বন্ধ করতে হবে



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
* পদক্ষেপ 4: আইএসপি মডিউলটি পরিষ্কার করুন, এই ক্রিয়াকলাপের আগে সমস্ত সেন্সর অবশ্যই অপসারণ করতে হবে।



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## কার্য তালিকা

int IMP_ISP_খালি(খালি);
int IMP_ISP_ক্লোজ(খালি);
int IMP_ISP_অ্যাডসেন্সর(IMPSensorInfo *পিনফো);
int IMP_ISP_DelSensor(IMPSensorInfo *পিনফো);
int IMP_ISP_সক্ষম সেন্সর(খালি);
int IMP_ISP_DisableSensor(খালি);
int IMP_ISP_সেট সেন্সররেজিস্টার(uint32_t reg, uint32_টি মান);
int IMP_ISP_getSensorRegister(uint32_t reg, uint32_t *মান);
আইএমপি_ISP_সক্ষমযোগ্যতা(ফাঁকা);
int IMP_ISP_DisableTuning(ফাঁকা);
int IMP_ISP_কনফিগারেশন_SetSensorFPS(uint32_টি fps_num, uint32_টি fps_den);
int IMP_আইএসপি_Tuning_getSensorFPS(uint32_t *fps_num, uint32_t *fps_ড্যান);আইএমপি_ISP_কনফিগারেশন_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_আইএসপি_Tuning_গেটআন্টি ফ্লিকারআটার(আইএমপিআইএসপিএন্টিফ্লিক্ল্যাটার *প্যাটার);
int IMP_ISP_কনফিগারেশন_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_আইএসপি_Tuning_getRawDRC(IMPISPDrcAttr *পিনফো);
int IMP_ISP_কনফিগারেশন_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_আইএসপি_Tuning_getSinterDnsAttr(IMPISPSinterDenoiseAttr *পিনফো);
int IMP_ISP_কনফিগারেশন_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_আইএসপি_Tuning_সেটটেম্পারডেন্সআত্র(IMPISPTemperDenoiseAttr *পিনফো);
আইএমপি_ISP_কনফিগারেশন_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_আইএসপি_Tuning_সেটডাব্লুড্রেট্র(IMPISPTuningOpsMode মোড); (° 147;) আইএমপি_ISP_সেটিং_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_আইএসপি_Tuning_সেটসনেমোড(আইএমপিআইএসপিএসসিনমোড মোড);
int IMP_ISP_সেটিং_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_আইএসপি_Tuning_সেটকলর্ফক্সমোড(আইএমপিআইএসপি কলর্ফেক্সমড মোড);
int IMP_ISP_সেটিং_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_আইএসপি_Tuning_উজ্জ্বলতা সেট করুন)নামবিহীন চিহ্নটি উজ্জ্বল); (° 186;) int IMP_ISP_কনফিগারেশন_GetBrightness(unsigned char *pbright);
int IMP_আইএসপি_Tuning_সেটকন্ট্রাস্ট(নামহীন চরিত্রের বিপরীতে);
int IMP_ISP_কনফিগারেশন_GetContrast(unsigned char *pcontrast);
int IMP_আইএসপি_Tuning_সেটসার্পনেস(নামহীন তীক্ষ্ণতা তীক্ষ্ণতা);
int IMP_ISP_কনফিগারেশন_GetSharpness(unsigned char *psharpness);
int IMP_আইএসপি_Tuning_সেটস্যাচুরেশন(নামবিহীন চিহ্ন (থেকে 22 °); (° 226;) আইএমপি_ISP_কনফিগারেশন_GetSaturation(unsigned char *psat);
int IMP_আইএসপি_Tuning_সেটআইএসপিপ্রসেস(আইএমপিআইএসপিটিউনিংপসমোড মোড);
int IMP_ISP_কনফিগারেশন_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_আইএসপি_Tuning_সেভআলাপারাম(চর *পাথ);
আইএমপি_ISP_সেটআপ_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_আইএসপি_Tuning_গেটটোটালগেইন(ইউন্ট 32_t *gain);
int IMP_আইএসপি_Tuning_আইএসপিএফএফলিপ(আইএমপিআইএসপিডিউনওটিং মোড);
int IMP_ISP_কনফিগারেশন_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_আইএসপি_Tuning_সেটআইএসপিভিফ্লিপ(IMPISPTuningOpsMode মোড);
int IMP_ISP_কনফিগারেশন_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_আইএসপি_Tuning_সেটআইএসপিআরানিংমোড(আইএমপিআইএসপিআরানিংমোড মোড); (° 298;) আইএমপি_ISP_কনফিগারেশন_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_আইএসপি_Tuning_সেটএস্টেরট্যাগি(আইএমপিআইএসপিএস্টেরট্রেজি কৌশল);
int IMP_ISP_কনফিগারেশন_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_আইএসপি_Tuning_সেটগ্যামা(আইএমপিআইএসপিগামা *পরিসর);
int IMP_ISP_কনফিগারেশন_GetGamma(IMPISPGamma *gamma);
int IMP_আইএসপি_Tuning_সেটএইকম্প(ইন্ট কম);
int আইএমপি_ISP_কনফিগারেশন_GetAeComp(int *comp);
int IMP_আইএসপি_Tuning_সেটেক্সপ্রিপ(আইএমপিআইএসপিএক্সপ্রিপ (° 350 ks) ekspr);
int IMP_ISP_কনফিগারেশন_GetExpr(IMPISPExpr *expr);
int IMP_আইএসপি_Tuning_এই_GetROI(IMPISPAERoi *isp_এ_roi);
int IMP_আইএসপি_Tuning_এই_SetROI(IMPISPAERoi *isp_এ ( ° 377 IS) আইএসপি_Tuning_সেটডাব্লুবি(আইএমপিআইএসপিডাব্লুবি *ডাব্লুবি);
int IMP_ISP_কনফিগারেশন_GetWB(IMPISPWB *wb);
int IMP_আইএসপি_Tuning_getWB_Statis(IMPISPWB *wb);
int IMP_আইএসপি_Tuning_আওব (b 405 °) ডাব্লু_attr);
int IMP_আইএসপি_Tuning_ওব_SetCwfShift(IMPISPWB *isp_ডাব্লুবি_attr);
int IMP_আইএসপি_Tuning_সেটম্যাক্সএইগেইন(ইউন্ট 32_t gain);
int IMP_আইএসপি_Tuning_গেটম্যাক্সঅ্যাগেইন(ইউন্ট 32_t *gain);
int IMP_) °) আইএসপি_Tuning_সেটম্যাক্সডেগেইন(ইউন্ট 32_t gain);
int IMP_আইএসপি_Tuning_গেটম্যাক্সডেগেইন(ইউন্ট 32_t *gain);
int IMP_আইএসপি_Tuning_সেটভিডিওড্রপ() খালি (*সিবি)(খালি));
int IMP_ISP_কনফিগারেশন_SetHiLightDepress(uint32_টি ফোর্স);
int IMP_ISP_কনফিগারেশন_SetTemperStrength(uint32_টি-অনুপাত); (° 473;) int IMP_ISP_কনফিগারেশন_SetSinterStrength(uint32_টি-অনুপাত);
int IMP_ISP_কনফিগারেশন_SetDPStrength(uint32_টি-অনুপাত);
int IMP_ISP_কনফিগারেশন_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_আইএসপি_Tuning_getEVAttr(IMPISPEVAttr *অ্যাটর);


