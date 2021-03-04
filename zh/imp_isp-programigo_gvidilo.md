# IMP_ISP (voir imp_isp.h)
图像处理。主要包括图像效果的设置，模式切换和记录，传感器的添加和删除。

ISP模块与数据流无关，不需要连接，仅在效果配置和传感器控制方面起作用。

## 激活

激活ISP模块的步骤如下：
* 步骤1：创建ISP模块

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* 步骤2：添加传感器，此操作之前已将传感器驱动程序添加到内核中。



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
* 步骤3：激活传感器，它将开始生成图像。



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* 步骤4：激活设置：



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* 步骤5：调用ISP调试界面：请参阅ISP调试界面文档。




## 禁用ISP模块

卸载ISP模块的步骤如下：
* 步骤1：禁用ISP配置

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
* 步骤2：关闭传感器。 (必须在此操作之前关闭FrameSource)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* 步骤3：卸下传感器，在执行此操作之前必须关闭传感器。



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* 步骤4：清洁ISP模块，在执行此操作之前必须卸下所有传感器。



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## 功能清单

int IMP_ISP_打开(空);
int IMP_ISP_关闭(空);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
内部IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(空);
int IMP_ISP_DisableSensor(空);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t值);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *值);
int IMP_ISP_EnableTuning(空白);
内置IMP_ISP_禁用调谐(挡片);
内置IMP_ISP_配置_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num，uint32_t *fps_den);
int IMP_ISP_配置_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *模式);
int IMP_ISP_配置_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_配置_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_配置_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_配置_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode模式);
int IMP_ISP_设置_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSce​​neMode模式);
int IMP_ISP_设置_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode模式);
int IMP_ISP_设置_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_设置亮度(无名标志亮);
int IMP_ISP_配置_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(无名字符对比度);
int IMP_ISP_配置_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(无名锐度锐度);
int IMP_ISP_配置_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(无名符号 (至22°);
int IMP_ISP_配置_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode模式);
内部IMP_ISP_配置_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(字符 *路径);
int IMP_ISP_设置_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_设置ISPHflip(IMPISPTuningOpsMode模式);
int IMP_ISP_配置_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode模式);
int IMP_ISP_配置_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode模式);
内部IMP_ISP_配置_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy策略);
int IMP_ISP_配置_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *范围);
int IMP_ISP_配置_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
内部IMP_ISP_配置_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
内置IMP_ISP_配置_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
内置IMP_ISP_配置_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_）°）ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(）空 (*cb)(空));
int IMP_ISP_配置_SetHiLightDepress(uint32_t力);
内部IMP_ISP_配置_SetTemperStrength(uint32_t比);
内部IMP_ISP_配置_SetSinterStrength(uint32_t比);
int IMP_ISP_配置_SetDPStrength(uint32_t比);
内部IMP_ISP_配置_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


