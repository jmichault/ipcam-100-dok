---
lang: eo
lang-niv: auto
lang-ref: 052-ISP-programigo_gvidilo
layout: page
title: 'Gvidilo pri video-programado'
---

# IMP_ISP (voir imp_isp.h)
Bildosigna prilaborado. Ĉefe inkluzivas agordojn de bildaj efikoj, reĝimoŝaltilo kaj registrado, aldono kaj forigo de sensilo.

La ISP-modulo havas nenion komunan kun datuma fluo kaj ne bezonas esti ligita, ĝi nur funkcias laŭ efektagordo kaj sensila kontrolo.

## Aktivigo

La paŝoj de aktivigo de ISP-modulo estas jenaj:
* paŝo 1: Kreu ISP-modulon

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* 2a paŝo: Aldonu sensilon, la sensila pelilo estis aldonita al la kerno antaŭ ĉi tiu operacio.


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
* Paŝo 3: Aktivigu la sensilon, ĝi komencos produkti bildojn.


```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* paŝo 4: Aktivigu la agordojn:


```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Paŝo 5: Alvoki ISP-elpurigan interfacon: Bonvolu raporti al la dokumentado de ISP-elpuriga interfaco.



## Senaktivigo de ISP-modulo

La paŝoj por malinstali la ISP-modulon estas jenaj:
* paŝo 1: Malŝalti la ISP-agordon

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
* 2a paŝo: fermu la sensilojn. (FrameSource devas esti fermita antaŭ ĉi tiu operacio)


```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* 3a paŝo: forigu la sensilojn, la sensiloj devas esti fermitaj antaŭ ĉi tiu operacio.


```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Paŝo 4: Purigu la ISP-modulon, ĉiuj sensiloj devas esti forigitaj antaŭ ĉi tiu operacio.


```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## listo de funkcioj

int IMP_ISP_Malferma(malplena);
int IMP_ISP_Fermi(malplenan);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(malplena);
int IMP_ISP_DisableSensor(malplena);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t valoro);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *valoro);
int IMP_ISP_EnableTuning(malplena);
int IMP_ISP_DisableTuning(malplena);
int IMP_ISP_Agordo_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Agordo_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Agordo_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Agordo_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Agordo_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Agordo_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);
int IMP_ISP_Agordo_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);
int IMP_ISP_Agordo_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);
int IMP_ISP_Agordo_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Agordu Brilecon(sennoma signo brila);
int IMP_ISP_Agordo_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(sennoma signokontrasto);
int IMP_ISP_Agordo_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(sennoma akra akreco);
int IMP_ISP_Agordo_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(sennoma signo (sat 22 °);
int IMP_ISP_Agordo_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Agordo_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *vojo);
int IMP_ISP_Agordo_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Agordu ISPHflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Agordo_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Agordo_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
int IMP_ISP_Agordo_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy-strategio);
int IMP_ISP_Agordo_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *gama);
int IMP_ISP_Agordo_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Agordo_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Agordo_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Agordo_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(malplena (*cb)(malplena));
int IMP_ISP_Agordo_SetHiLightDepress(uint32_t forto);
int IMP_ISP_Agordo_SetTemperStrength(uint32_t-proporcio);
int IMP_ISP_Agordo_SetSinterStrength(uint32_t-proporcio);
int IMP_ISP_Agordo_SetDPStrength(uint32_t-proporcio);
int IMP_ISP_Agordo_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


