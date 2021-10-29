---
lang: es
lang-niv: auto
lang-ref: 052-ISP-programigo_gvidilo
layout: page
title: 'Guía de programación de video'
---

# IMP_ISP (voir imp_isp.h)
Procesamiento de imágenes. Incluye principalmente ajustes de efectos de imagen, cambio de modo y grabación, adición y eliminación de sensor.

El módulo ISP no tiene nada que ver con el flujo de datos y no necesita estar conectado, solo funciona en términos de configuración de efectos y control de sensores.

## Activación

Los pasos para activar un módulo ISP son los siguientes:
* paso 1: Cree un módulo ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Paso 2: Agregue el sensor, el controlador del sensor se agregó al kernel antes de esta operación.



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
* Paso 3: Activa el sensor, comenzará a producir imágenes.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Paso 4: Activar la configuración:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Paso 5: Invocar la interfaz de depuración del ISP: consulte la documentación de la interfaz de depuración del ISP.




## Deshabilitar un módulo ISP

Los pasos para desinstalar el módulo ISP son los siguientes:
* paso 1: Desactive la configuración del ISP

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
* Paso 2: cierra los sensores. (FrameSource debe estar cerrado antes de esta operación)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Paso 3: retire los sensores, los sensores deben estar cerrados antes de esta operación.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Paso 4: Limpie el módulo ISP, todos los sensores deben quitarse antes de esta operación.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## lista de funciones

int IMP_ISP_Abierto(vacío);
int IMP_ISP_Cerrar(vacío);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(vacío);
int IMP_ISP_DisableSensor(vacío);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_valor t);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *valor);
int IMP_ISP_EnableTuning(en blanco);
int IMP_ISP_DisableTuning(en blanco);
int IMP_ISP_Configuración_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Configuración_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Configuración_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Configuración_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Configuración_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Configuración_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode modo);
int IMP_ISP_Ajuste_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode modo);
int IMP_ISP_Configuración_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode modo);
int IMP_ISP_Configuración_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Establecer brillo(signo sin nombre brillante);
int IMP_ISP_Configuración_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(contraste de caracteres sin nombre);
int IMP_ISP_Configuración_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(nitidez sin nombre nitidez);
int IMP_ISP_Configuración_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_Establezca la saturación(signo sin nombre (en 22 °);
int IMP_ISP_Configuración_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Configuración_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *ruta);
int IMP_ISP_Configuración_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Establecer ISPHflip(IMPISPTuningOpsMode modo);
int IMP_ISP_Configuración_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Configuración_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
int IMP_ISP_Configuración_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(Estrategia IMPISPAeStrategy);
int IMP_ISP_Configuración_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *rango);
int IMP_ISP_Configuración_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Configuración_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Configuración_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Configuración_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_°) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(vacío (*cb)(vacío));
int IMP_ISP_Configuración_SetHiLightDepress(uint32_t fuerza);
int IMP_ISP_Configuración_SetTemperStrength(uint32_Relación t);
int IMP_ISP_Configuración_SetSinterStrength(uint32_Relación t);
int IMP_ISP_Configuración_SetDPStrength(uint32_relación t);
int IMP_ISP_Configuración_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


