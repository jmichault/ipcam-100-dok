# ਆਈਐਮਪੀ_ISP (voir imp_isp.h)
ਚਿੱਤਰ ਪ੍ਰੋਸੈਸਿੰਗ. ਮੁੱਖ ਤੌਰ ਤੇ ਚਿੱਤਰ ਪ੍ਰਭਾਵਾਂ ਦੀ ਸੈਟਿੰਗ, ਮੋਡ ਸਵਿੱਚ ਅਤੇ ਰਿਕਾਰਡਿੰਗ, ਸੰਵੇਦਕ ਨੂੰ ਜੋੜ ਅਤੇ ਹਟਾਉਣ ਸ਼ਾਮਲ ਹਨ.

ਆਈਐਸਪੀ ਮੈਡਿ .ਲ ਦਾ ਡੇਟਾ ਪ੍ਰਵਾਹ ਨਾਲ ਕੋਈ ਲੈਣਾ ਦੇਣਾ ਨਹੀਂ ਹੈ ਅਤੇ ਨਾ ਜੁੜਣ ਦੀ ਜ਼ਰੂਰਤ ਹੈ, ਇਹ ਸਿਰਫ ਪ੍ਰਭਾਵ ਕੌਂਫਿਗਰੇਸ਼ਨ ਅਤੇ ਸੈਂਸਰ ਨਿਯੰਤਰਣ ਦੇ ਰੂਪ ਵਿੱਚ ਕੰਮ ਕਰਦਾ ਹੈ.

## ਐਕਟੀਵੇਸ਼ਨ

ਇੱਕ ISP ਮੋਡੀ moduleਲ ਨੂੰ ਸਰਗਰਮ ਕਰਨ ਲਈ ਕਦਮ ਇਸ ਤਰਾਂ ਹਨ:
* ਕਦਮ 1: ਇੱਕ ISP ਮੋਡੀ moduleਲਬਣਾਓ

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* ਕਦਮ 2: ਸੈਂਸਰ ਸ਼ਾਮਲ ਕਰੋ, ਇਸ ਕਾਰਵਾਈ ਤੋਂ ਪਹਿਲਾਂ ਸੈਂਸਰ ਡਰਾਈਵਰ ਨੂੰ ਕਰਨਲ ਵਿੱਚ ਜੋੜਿਆ ਗਿਆ ਸੀ.



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
* ਕਦਮ 3: ਸੈਂਸਰ ਨੂੰ ਸਰਗਰਮ ਕਰੋ, ਇਹ ਚਿੱਤਰ ਤਿਆਰ ਕਰਨਾ ਸ਼ੁਰੂ ਕਰੇਗਾ.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* ਕਦਮ 4: ਸੈਟਿੰਗਾਂ ਨੂੰ ਸਰਗਰਮ ਕਰੋ:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* ਕਦਮ 5: ਆਈਐਸਪੀ ਡੀਬੱਗਿੰਗ ਇੰਟਰਫੇਸ ਨੂੰ ਬੁਲਾਓ: ਕਿਰਪਾ ਕਰਕੇ ਆਈਐਸਪੀ ਡੀਬੱਗਿੰਗ ਇੰਟਰਫੇਸ ਦਸਤਾਵੇਜ਼ ਵੇਖੋ.




## ਇੱਕ ISP ਮੋਡੀ .ਲ ਨੂੰ ਅਸਮਰੱਥ ਬਣਾ ਰਿਹਾ ਹੈ

ਆਈਐਸਪੀ ਮੈਡਿ uninਲ ਨੂੰ ਅਣਇੰਸਟੌਲ ਕਰਨ ਲਈ ਕਦਮ ਇਸ ਪ੍ਰਕਾਰ ਹਨ:
* ਕਦਮ 1: ਆਈਐਸਪੀ ਕੌਂਫਿਗਰੇਸ਼ਨਨੂੰ ਅਯੋਗ ਕਰੋ

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
* ਕਦਮ 2: ਸੈਂਸਰ ਬੰਦ ਕਰੋ. (ਇਸ ਓਪਰੇਸ਼ਨ)ਤੋਂ ਪਹਿਲਾਂ ਫਰੇਮ ਸਰੋਤ ਨੂੰ ਬੰਦ ਕਰਨਾ ਲਾਜ਼ਮੀ ਹੈ



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* ਕਦਮ 3: ਸੈਂਸਰਾਂ ਨੂੰ ਹਟਾਓ, ਇਸ ਕਾਰਵਾਈ ਤੋਂ ਪਹਿਲਾਂ ਸੈਂਸਰਾਂ ਨੂੰ ਬੰਦ ਕਰ ਦੇਣਾ ਚਾਹੀਦਾ ਹੈ.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* ਕਦਮ 4: ਆਈਐਸਪੀ ਮੈਡਿ Cleanਲ ਨੂੰ ਸਾਫ਼ ਕਰੋ, ਇਸ ਕਾਰਵਾਈ ਤੋਂ ਪਹਿਲਾਂ ਸਾਰੇ ਸੈਂਸਰਾਂ ਨੂੰ ਹਟਾ ਦਿੱਤਾ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## ਫੰਕਸ਼ਨ ਦੀ ਸੂਚੀ

ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਖਾਲੀ(ਖਾਲੀ);
ਇੰਟ IMP_ISP_ਬੰਦ ((ਖਾਲੀ);
ਇੰਟ ਆਈਐਮਪੀ (° 11 Add) ਐਡਸੈਂਸਰ(ਆਈ ਐਮ ਪੀਐਸਸੈਂਸਰਇੰਫੋ *ਪਿੰਨਫੋ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਡੈਲਸੈਂਸਰ(ਆਈ ਐਮ ਪੀਐਸਸੈਂਸਰਇੰਫੋ *ਪਿੰਨਫੋ);
ਇੰਟੈਂਡਰ ਆਈਐਮਪੀ (° 23 S) ਯੋਗ ਸੈਂਸਰ(ਖਾਲੀ);
ਇੰਟ IMP_ISP_ਡਿਸਏਬਲਸੈਂਸਰ(ਖਾਲੀ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਸੈੱਟਸੈਂਸਰ ਰਜਿਸਟਰ(ਯੂਇੰਟ 32_t reg, uint32_ਟੀ ਵੈਲਯੂ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਗੇਟਸੈਂਸਰ ਰਜਿਸਟਰ(ਯੂਇੰਟ 32_t reg, uint32_ਟੀ *ਵੈਲਯੂ);
ਇੰਟੈਂਡਰ ਆਈਐਮਪੀ_ISP_ਯੋਗ ਯੋਗਦਾਨ (un 50 °) ਖਾਲੀ);
ਇੰਟ IMP_ISP_ਡਿਸੇਬਲ ਟਿunਨਿੰਗ(ਖਾਲੀ);
ਇੰਟ ਆਈਐਮਪੀ (° 58 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ_SetSensorFPS(uint32_ਟੀ ਐਫਪੀਐਸ_num, uint32_ਟੀ ਐਫਪੀਐਸ_den);
int IMP_ਆਈਐਸਪੀ_Tuning_ਗੇਟਸੈਂਸਰਐਫਪੀਐਸ(uint32_t *fps_ਨੰਬਰ, uint32_t *fps_ਡੇਨ);
ਇੰਟ ਆਈਐਮਪੀ (° 80 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ਆਈਐਸਪੀ_Tuning_ਗੇਟਅੰਟੀਫਲਿਕਅਟਰ(ਆਈਐਮਪੀਆਈਐਸਪੀਐਨਟੀਫਲਿਕਟਰਐਟਰ *ਪੈਟਰ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ਆਈਐਸਪੀ_Tuning_ਗੇਟਆਰਓਡੀਆਰਸੀ(ਆਈਐਮਪੀਆਈਐਸਪੀਆਰਸੀਐਟਰ *ਪਿੰਨਫੋ);
ਇੰਟ ਆਈਐਮਪੀ (° 107 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ (° 109 IS) ਆਈਐਸਪੀ_Tuning_ਗੇਟਸਿੰਟਰਡਰਨਸੈਟਰ(ਆਈਐਮਪੀਆਈਐਸਪੀਨਸਟਰਡੇਨੋਆਇਸਟਰ *ਪਿੰਨਫੋ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਸੈੱਟਟੈਂਪਰਡਨਸੈਟਰ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਟੈਂਪਰਡੈਨੋਇਸ ਏਟਰ *ਪਿੰਨਫੋ);
ਇੰਟ ਆਈਐਮਪੀ (5 135 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ (° 137 IS) ਆਈਐਸਪੀ_Tuning_ਸੈਟ ਡਬਲਯੂ ਡੀ ਡਰਾਟਰ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਟਿingਨਿੰਗ ਓਪਸਮੋਡ ਮੋਡ);
ਇੰਟ IMP_ISP_ਸੈਟਿੰਗ_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੈੱਟਸਨਮੋਡ(ਆਈਐਮਪੀਆਈਐਸਪੀਸਨਮੋਡ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਸੈਟਿੰਗ_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟਕਾਲਫੋਰਕਸਮੋਡ(ਆਈਐਮਪੀਆਈਐਸਪੀਐਲਆਰਪੀਐਕਸਮੋਡ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਸੈਟਿੰਗ_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਬ੍ਰਾਇਟਨੇਸ(ਨਿਰਧਾਰਤ ਨਿਸ਼ਾਨ ਚਮਕਦਾਰ);
ਇੰਟ ਆਈਐਮਪੀ (° 187 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ_GetBrightness(unsigned char *pbright);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟ ਕੰਟ੍ਰਾਸਟ(ਨਾਮ ਰਹਿਤ ਚਰਿੱਤਰ ਦੇ ਉਲਟ ();
ਇੰਟ ਆਈਐਮਪੀ (° 200 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ_GetContrast(unsigned char *pcontrast);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟ ਸ਼ਾਰਪਨੇਸ(ਨਾਮ ਰਹਿਤ ਤਿੱਖਾਪਨ ਸ਼ਾਰਪਨ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetSharpness(unsigned char *psharpness);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਸੈਟਸੈਟੇਸ਼ਨ(ਅਣਜਾਣ ਨਿਸ਼ਾਨ (ਤੋਂ 22 °);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetSaturation(unsigned char *psat);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਸੇਟ ਆਈ ਐਸ ਪੀ ਪ੍ਰੌਸੈੱਸ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਟਿingਨਿੰਗ ਓਪਸਮੋਡ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਂਫਿਗਰੇਸ਼ਨ_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਵ ਆੱਲਪਾਰਮ(ਚਾਰ *ਮਾਰਗ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਸੈਟਅਪ_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ਆਈਐਸਪੀ (° 260 T) ਗੇਟਟੋਟਲਗੈਨ(uint32_t *gain);
int IMP_ਆਈਐਸਪੀ(ਆਈਐਸਪੀਐਫਐਲਪ(ਆਈਐਸਪੀਐਸਪੀਟਿਓਨਿੰਗ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ (3 273 Config) ਕੌਂਫਿਗਰੇਸ਼ਨ_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੈੱਟ ਆਈਐਸਪੀਵੀਫਲਿਪ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਟਿTਨਿੰਗ ਓਪਸਮੋਡ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਂਫਿਗਰੇਸ਼ਨ_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੈੱਟ ਆਈਐਸਪੀਰਨਿੰਗਮੋਡ(ਆਈਐਮਪੀਆਈਐਸਪੀਰਨਿੰਗਮੋਡ ਮੋਡ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟਏਸਟ੍ਰੈਟਜੀ(ਆਈਐਮਪੀਆਈਐਸਪੀਐਸਟਰੈਟਜੀ ਰਣਨੀਤੀ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਸੇਟਗਾਮਾ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਗਾਮਾ *ਸੀਮਾ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetGamma(IMPISPGamma *gamma);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟਏਕੌਮਪ(ਇੰਟ ਕੰਪਿ ;ਟਰ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_GetAeComp(int *comp);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੇਟਐਕਸਪ੍ਰਾਂਪ(ਆਈਐਮਪੀਆਈਐਸਪੀਐਕਸਪੀਆਰਪੀ *ਐਕਸਪੀਆਰ);
ਇੰਟ ਆਈਐਮਪੀ_ISP_ਕੌਂਫਿਗਰੇਸ਼ਨ_GetExpr(IMPISPExpr *expr);
int IMP_ਆਈਐਸਪੀ_Tuning_ਏਈ_GetROI(IMPISPAERoi *isp_ਏਈ_roi);
int IMP_ਆਈਐਸਪੀ_Tuning_ਏਈ_SetROI(IMPISPAERoi *isp_ਏ ( ° 377 IS) ਆਈਐਸਪੀ_Tuning_ਸੈਟ ਡਬਲਯੂ ਬੀ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਡਬਲਯੂ ਬੀ *ਡਬਲਯੂ ਬੀ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਂਫਿਗਰੇਸ਼ਨ_GetWB(IMPISPWB *wb);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਗੇਟ ਡਬਲਯੂ ਬੀ_Statis(IMPISPWB *wb);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਆੱਬ_GetCwfShift(IMPISPWB *isp_ਡਬਲਯੂ ਬੀ_attr);
int IMP_ਆਈ ਐਸ ਪੀ_Tuning_bਬ_SetCwfShift(IMPISPWB *isp_ਡਬਲਯੂਬੀ_attr);
int IMP_ਆਈ ਐੱਸ ਪੀ_Tuning_ਸੇਟ ਮੈਕਸਗੈਨ(ਯੂਇੰਟ 32_t gain);
int IMP_ਆਈ ਐਸ ਪੀ_Tuning_ਗੇਟਮੈਕਸਗੈਗਨ(uint32_t *gain);
int IMP_) °) ਆਈਐਸਪੀ_Tuning_ਸੈੱਟਮੈਕਸਡਗੈਨ(uint32_t gain);
int IMP_ਆਈਐਸਪੀ_Tuning_ਗੇਟਮੈਕਸਡਗੈਨ(uint32_t *gain);
int IMP_ਆਈਐਸਪੀ_Tuning_ਸੈਟਵਿਡਿਓ ਡ੍ਰੌਪ() ਖਾਲੀ (*ਸੀਬੀ)(ਖਾਲੀ));
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetHiLightDepress(uint32_ਟੀ ਫੋਰਸ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetTemperStrength(uint32_ਟੀ-ਰੇਸ਼ੋ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetSinterStrength(uint32_ਟੀ-ਰੇਸ਼ੋ);
ਇੰਟ ਆਈ ਐਮ ਪੀ_ISP_ਕੌਨਫਿਗਰੇਸ਼ਨ_SetDPStrength(uint32_ਟੀ-ਰੇਸ਼ੋ);
ਇੰਟ ਆਈਐਮਪੀ (° 488 Config) ਕੌਨਫਿਗਰੇਸ਼ਨ (° 490 IS) ਆਈਐਸਪੀ (° 495 Get) ਗੈਰੀ ਈਵੀਏਟਰ(ਆਈ ਐਮ ਪੀ ਆਈ ਐਸ ਪੀ ਏ ਟੀ ਐਟਰ *ਅਟਾਰ);


