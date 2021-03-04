# IMP_ISP (voir imp_isp.h)
画像処理。主に画像効果の設定、モード切り替えと記録、センサーの追加と削除が含まれます。

ISPモジュールはデータフローとは関係がなく、接続する必要はありません。エフェクト構成とセンサー制御に関してのみ機能します。

## アクティベーション

ISPモジュールをアクティブ化する手順は次のとおりです。
* 手順1：ISPモジュールを作成します

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* ステップ2：センサーを追加します。この操作の前にセンサードライバーがカーネルに追加されました。



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
* ステップ3：センサーをアクティブにすると、画像の生成が開始されます。



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* ステップ4：設定をアクティブにする：



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* 手順5：ISPデバッグインターフェイスを呼び出す：ISPデバッグインターフェイスのドキュメントを参照してください。




## ISPモジュールの無効化

ISPモジュールをアンインストールする手順は次のとおりです。
* 手順1：ISP構成を無効にします

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
* ステップ2：センサーを閉じます。 (この操作の前にFrameSourceを閉じる必要があります)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* ステップ3：センサーを取り外します。この操作の前にセンサーを閉じる必要があります。



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* ステップ4：ISPモジュールをクリーニングします。この操作の前に、すべてのセンサーを取り外す必要があります。



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## 関数のリスト

int IMP_ISP_オープン(空);
int IMP_ISP_閉じる(空);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(empty);
int IMP_ISP_DisableSensor(empty);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t値);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *値);
int IMP_ISP_EnableTuning(ブランク);
int IMP_ISP_DisableTuning(ブランク);
int IMP_ISP_構成_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num、uint32_t *fps_den);
int IMP_ISP_構成_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_構成_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_構成_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_構成_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_構成_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsModeモード);
int IMP_ISP_設定_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSce​​neModeモード);
int IMP_ISP_設定_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxModeモード);
int IMP_ISP_設定_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_明るさの設定(名前のない記号明るい);
int IMP_ISP_構成_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(名前のない文字のコントラスト);
int IMP_ISP_構成_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(無名のシャープネスシャープネス);
int IMP_ISP_構成_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(名前のない符号 (から22°);
int IMP_ISP_構成_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsModeモード);
int IMP_ISP_構成_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *パス);
int IMP_ISP_セットアップ_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Set ISPHflip(IMPISPTuningOpsModeモード);
int IMP_ISP_構成_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsModeモード);
int IMP_ISP_構成_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningModeモード);
int IMP_ISP_構成_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy戦略);
int IMP_ISP_構成_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *範囲);
int IMP_ISP_構成_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_構成_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_構成_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_構成_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_°）ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(空 (*cb)(空));
int IMP_ISP_構成_SetHiLightDepress(uint32_t力);
int IMP_ISP_構成_SetTemperStrength(uint32_t比);
int IMP_ISP_構成_SetSinterStrength(uint32_t比);
int IMP_ISP_構成_SetDPStrength(uint32_t比);
int IMP_ISP_構成_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


