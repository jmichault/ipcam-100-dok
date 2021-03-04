# IMP_ISP (voir imp_isp.h)
Bildverarbeitung. Enthält hauptsächlich Einstellungen für Bildeffekte, Moduswechsel und Aufnahme, Hinzufügen und Entfernen des Sensors.

Das ISP-Modul hat nichts mit Datenfluss zu tun und muss nicht angeschlossen werden, es funktioniert nur in Bezug auf Effektkonfiguration und Sensorsteuerung.

## Aktivierung

Die Schritte zum Aktivieren eines ISP-Moduls lauten wie folgt:
* Schritt 1: Erstellen eines ISP-Moduls

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Schritt 2: Sensor hinzufügen, der Sensortreiber wurde vor diesem Vorgang zum Kernel hinzugefügt.



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
* Schritt 3: Aktivieren Sie den Sensor, um Bilder zu produzieren.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Schritt 4: Aktivieren Sie die Einstellungen:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Schritt 5: Aufrufen der ISP-Debugging-Schnittstelle: Weitere Informationen finden Sie in der Dokumentation zur ISP-Debugging-Schnittstelle.




## Deaktivieren eines ISP-Moduls

Die Schritte zum Deinstallieren des ISP-Moduls lauten wie folgt:
* Schritt 1: Deaktivieren Sie die ISP-Konfiguration.

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
* Schritt 2: Schließen Sie die Sensoren. (FrameSource muss vor diesem Vorgang geschlossen werden)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Schritt 3: Entfernen Sie die Sensoren. Die Sensoren müssen vor diesem Vorgang geschlossen werden.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Schritt 4: Reinigen Sie das ISP-Modul. Vor diesem Vorgang müssen alle Sensoren entfernt werden.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## Liste der Funktionen

int IMP_ISP_Offen(leer);
int IMP_ISP_Schließen(leer);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(leer);
int IMP_ISP_DisableSensor(leer);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_t Wert);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *Wert);
int IMP_ISP_EnableTuning(leer);
int IMP_ISP_DisableTuning(leer);
int IMP_ISP_Konfiguration_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Konfiguration_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Konfiguration_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Konfiguration_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Konfiguration_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Konfiguration_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode-Modus);
int IMP_ISP_Einstellung_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode-Modus);
int IMP_ISP_Einstellung_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode-Modus);
int IMP_ISP_Einstellung_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Helligkeit einstellen(namenloses Zeichen hell);
int IMP_ISP_Konfiguration_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(namenloser Zeichenkontrast);
int IMP_ISP_Konfiguration_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(namenlose Schärfe Schärfe);
int IMP_ISP_Konfiguration_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_SetSaturation(unbenanntes Zeichen (auf 22 °);
int IMP_ISP_Konfiguration_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode-Modus);
int IMP_ISP_Konfiguration_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *Pfad);
int IMP_ISP_Setup_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Stellen Sie ISPHflip(IMPISPTuningOpsMode ein Modus);
int IMP_ISP_Konfiguration_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode-Modus);
int IMP_ISP_Konfiguration_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode-Modus);
int IMP_ISP_Konfiguration_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(IMPISPAeStrategy-Strategie);
int IMP_ISP_Konfiguration_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *Bereich);
int IMP_ISP_Konfiguration_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Konfiguration_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Konfiguration_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Konfiguration_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_) °) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop() leer (*cb)(leer));
int IMP_ISP_Konfiguration_SetHiLightDepress(uint32_t Kraft);
int IMP_ISP_Konfiguration_SetTemperStrength(uint32_t-Verhältnis);
int IMP_ISP_Konfiguration_SetSinterStrength(uint32_t-Verhältnis);
int IMP_ISP_Konfiguration_SetDPStrength(uint32_t-Verhältnis);
int IMP_ISP_Konfiguration_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


