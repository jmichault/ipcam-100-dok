# IMP_ISP (voir imp_isp.h)
इमेज प्रोसेसिंग। मुख्य रूप से छवि प्रभाव, मोड स्विच और रिकॉर्डिंग, इसके अलावा और सेंसर को हटाने की सेटिंग्स शामिल हैं।

आईएसपी मॉड्यूल का डेटा प्रवाह से कोई लेना-देना नहीं है और इसे कनेक्ट करने की आवश्यकता नहीं है, यह केवल प्रभाव कॉन्फ़िगरेशन और सेंसर नियंत्रण के रूप में काम करता है।

## सक्रियण

ISP मॉड्यूल को सक्रिय करने के चरण इस प्रकार हैं:
* चरण 1: ISP मॉड्यूल बनाएँ

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* चरण 2: सेंसर जोड़ें, सेंसर चालक को इस ऑपरेशन से पहले कर्नेल में जोड़ा गया था।



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
* चरण 3: सेंसर को सक्रिय करें, यह छवियों का उत्पादन शुरू कर देगा।



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* चरण 4: सेटिंग्स सक्रिय करें:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* चरण 5: ISP डिबगिंग इंटरफ़ेस लागू करें: कृपया ISP डीबगिंग इंटरफ़ेस दस्तावेज़ देखें।




## ISP मॉड्यूल को अक्षम करना

ISP मॉड्यूल की स्थापना रद्द करने के चरण इस प्रकार हैं:
* चरण 1: ISP कॉन्फ़िगरेशन को अक्षम करें

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
* चरण 2: सेंसर बंद करें। (फ़्रेमसोर्स इस ऑपरेशन)से पहले बंद होना चाहिए



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* चरण 3: सेंसर को हटा दें, इस ऑपरेशन से पहले सेंसर बंद होना चाहिए।



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* चरण 4: ISP मॉड्यूल को साफ करें, इस ऑपरेशन से पहले सभी सेंसर हटा दिए जाने चाहिए।



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## कार्यों की सूची

int छोटा सा भूत_ISP_खुला(खाली);
int छोटा सा भूत_ISP_बंद(खाली);
int छोटा सा भूत_ISP_AddSensor(IMPSensorInfo *pinfo);
int छोटा सा भूत_ISP_DelSensor(IMPSensorInfo *pinfo);
int छोटा सा भूत_ISP_EnableSensor(खाली);
int छोटा सा भूत_ISP_DisableSensor(खाली);
int छोटा सा भूत_ISP_SetSensorRegister(uint32_t reg, uint32_टी मान);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *मान);
int छोटा सा भूत_ISP_EnableTuning(खाली);
int छोटा सा भूत_ISP_DisableTuning(खाली);
int IMP_ISP_विन्यास_SetSensorFPS(uint32_t एफपीएस_num, uint32_t एफपीएस_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_संख्या, uint32_t *fps_डेन);
int IMP_ISP_विन्यास_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int छोटा सा भूत_ISP_विन्यास_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *: pinfo);
int छोटा सा भूत_ISP_विन्यास_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseArr *पिनोफ़);
int छोटा सा भूत_ISP_विन्यास_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_सेटटेम्परडॉनसेंटर(IMPISPTemperDenoiseArr *पिनोफ़);
int छोटा सा भूत_ISP_विन्यास_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode मोड);
int छोटा सा भूत_ISP_विन्यास_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode मोड);
int छोटा सा भूत_ISP_विन्यास_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode मोड);
int छोटा सा भूत_ISP_विन्यास_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_सेट चमक(अनाम वर्ण उज्ज्वल);
int छोटा सा भूत_ISP_विन्यास_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(अनाम संकेत विपरीत);
int छोटा सा भूत_ISP_विन्यास_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_सेटशरपनेस(नमनीय तीक्ष्णता तीक्ष्णता);
int छोटा सा भूत_ISP_विन्यास_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(अनाम चिह्न (से 22 °);
int छोटा सा भूत_ISP_विन्यास_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_सेटिसप्रोसेस(IMPISPTuningOpsMode मोड);
int छोटा सा भूत_ISP_विन्यास_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(चार *पथ_;
int IMP_ISP_सेटिंग_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_सेटिंग ISPHflip(IMPISPTuningMps मोड);
int छोटा सा भूत_ISP_विन्यास_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode मोड);
int छोटा सा भूत_ISP_विन्यास_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode मोड_;
int छोटा सा भूत_ISP_विन्यास_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy रणनीति);
int IMP_ISP_सेटअप_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_सेटगम्मा(IMPISPGamma *गामा);
int छोटा सा भूत_ISP_विन्यास_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int COMP);
int छोटा सा भूत_ISP_विन्यास_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *एक्स्कप्र);
int छोटा सा भूत_ISP_विन्यास_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_AE_roi);
int IMP_ISP_SetROI(IMPISPAERoi *isp_AE_SetROI(IMPISPAERoi *isp_AE_SetROI(IMPISPAERoi *isp_° 000377 °) ISP_Tuning_SetWB(IMPISPWB *wb);
int छोटा सा भूत_ISP_विन्यास_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb)wb_attr);
int IMP_ISP° 000413 °) अब्ब_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_सेटमैक्सएगैन(uint32_t gain);
int IMP_ISP_Tuning_गेटमैक्सैन(uint32() °) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_ISV_Tuning_SetVideoDrop *) खाली (*cb)(खाली));
int छोटा सा भूत_ISP_विन्यास_SetHiLightDepress(uint32_टी बल);
int छोटा सा भूत_ISP_विन्यास_SetTemperStrength(uint32_टी-अनुपात);
int छोटा सा भूत_ISP_विन्यास_SetSinterStrength(uint32_टी-अनुपात);
int छोटा सा भूत_ISP_विन्यास_SetDPStrength(uint32_टी-अनुपात);
int छोटा सा भूत_ISP_सेटअप_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


