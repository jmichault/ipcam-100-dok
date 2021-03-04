# IMP_ISP (voir imp_isp.h)
Обработка изображений. В основном включает настройки эффектов изображения, переключения режимов и записи, добавления и удаления сенсора.

Модуль ISP не имеет ничего общего с потоком данных и не требует подключения, он работает только с точки зрения настройки эффектов и управления датчиками.

## Активация

Шаги для активации модуля ISP следующие:
* шаг 1: Создание модуля ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Шаг 2: Добавить датчик, драйвер датчика был добавлен в ядро ​​перед этой операцией.



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
* Шаг 3: Активируйте датчик, он начнет создавать изображения.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Шаг 4: Активируйте настройки:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Шаг 5: Вызовите интерфейс отладки ISP: обратитесь к документации по интерфейсу отладки ISP.




## Отключение модуля ISP

Шаги для удаления модуля ISP следующие:
* шаг 1: Отключить конфигурацию ISP

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
* Шаг 2: Закройте датчики. (FrameSource должен быть закрыт перед этой операцией)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Шаг 3: снимите датчики, датчики должны быть закрыты перед этой операцией.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Шаг 4: Очистите модуль ISP, перед этой операцией необходимо снять все датчики.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## список функций

int IMP_ISP_Открытый(пустой);
int IMP_ISP_Закрыть(пустой);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(пусто);
int IMP_ISP_DisableSensor(пустой);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_значение t);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *значение);
int IMP_ISP_EnableTuning(пустой);
int IMP_ISP_DisableTuning(пустой);
int IMP_ISP_Конфигурация_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_число, uint32_t *fps_den);
int IMP_ISP_Конфигурация_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Конфигурация_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Конфигурация_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Конфигурация_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Конфигурация_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);
int IMP_ISP_Настройка_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);
int IMP_ISP_Настройка_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);
int IMP_ISP_Настройка_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Установить яркость(безымянный знак яркий);
int IMP_ISP_Конфигурация_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(безымянный контраст символов);
int IMP_ISP_Конфигурация_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(безымянная резкость резкость);
int IMP_ISP_Конфигурация_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(безымянный знак (до 22 °);
int IMP_ISP_Конфигурация_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Конфигурация_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *путь);
int IMP_ISP_Настройка_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Установить ISPHflip(IMPISPTuningOpsMode режим);
int IMP_ISP_Конфигурация_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Конфигурация_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
int IMP_ISP_Конфигурация_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(Стратегия IMPISPAeStrategy);
int IMP_ISP_Конфигурация_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *диапазон);
int IMP_ISP_Конфигурация_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Конфигурация_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *expr);
int IMP_ISP_Конфигурация_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Конфигурация_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_) °) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop() пустой (*cb)(пустой));
int IMP_ISP_Конфигурация_SetHiLightDepress(uint32_t сила);
int IMP_ISP_Конфигурация_SetTemperStrength(uint32_t-отношение);
int IMP_ISP_Конфигурация_SetSinterStrength(uint32_t-отношение);
int IMP_ISP_Конфигурация_SetDPStrength(uint32_t-отношение);
int IMP_ISP_Конфигурация_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


