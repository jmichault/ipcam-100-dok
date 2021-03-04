# IMP_ISP (voir imp_isp.h)
Elaborazione delle immagini. Include principalmente le impostazioni degli effetti dell'immagine, il cambio di modalità e la registrazione, l'aggiunta e la rimozione del sensore.

Il modulo ISP non ha nulla a che fare con il flusso di dati e non ha bisogno di essere collegato, funziona solo in termini di configurazione degli effetti e controllo dei sensori.

## Attivazione

I passaggi per l'attivazione di un modulo ISP sono i seguenti:
* passaggio 1: creazione di un modulo ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Passaggio 2: aggiungere il sensore, il driver del sensore è stato aggiunto al kernel prima di questa operazione.



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
* Passaggio 3: attiva il sensore, inizierà a produrre immagini.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Passaggio 4: attivare le impostazioni:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Passaggio 5: richiamare l'interfaccia di debug dell'ISP: fare riferimento alla documentazione dell'interfaccia di debug dell'ISP.




## Disattivazione di un modulo ISP

I passaggi per disinstallare il modulo ISP sono i seguenti:
* passaggio 1: Disabilitare la configurazione ISP

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
* Passaggio 2: chiudere i sensori. (FrameSource deve essere chiuso prima di questa operazione)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Fase 3: rimuovere i sensori, i sensori devono essere chiusi prima di questa operazione.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Passaggio 4: pulire il modulo ISP, tutti i sensori devono essere rimossi prima di questa operazione.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## elenco delle funzioni

int IMP_ISP_Aperto(vuoto);
int IMP_ISP_Chiude(vuoto);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(vuoto);
int IMP_ISP_DisableSensor(vuoto);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_valore t);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_valore t *);
int IMP_ISP_EnableTuning(blank);
int IMP_ISP_DisableTuning(blank);
int IMP_ISP_Configurazione_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Configurazione_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Configurazione_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Configurazione_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Configurazione_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Configurazione_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPTuningOpsMode mode);
int IMP_ISP_Impostazione_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(IMPISPSceneMode mode);
int IMP_ISP_Setting_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);
int IMP_ISP_Impostazione_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Set Luminosità(segno senza nome luminoso);
int IMP_ISP_Configurazione_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(contrasto caratteri senza nome);
int IMP_ISP_Configurazione_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_SetSharpness(senza nome nitidezza nitidezza);
int IMP_ISP_Configurazione_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_Imposta Saturazione(segno senza nome (a 22 °);
int IMP_ISP_Configurazione_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(IMPISPTuningOpsMode mode);
int IMP_ISP_Configurazione_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *percorso);
int IMP_ISP_Configurazione_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Imposta ISPHflip(IMPISPTuningOpsMode modalità);
int IMP_ISP_Configurazione_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPTuningOpsMode mode);
int IMP_ISP_Configurazione_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(IMPISPRunningMode mode);
int IMP_ISP_Configurazione_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(Strategia IMPISPAeStrategy);
int IMP_ISP_Configurazione_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *range);
int IMP_ISP_Configurazione_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Configurazione_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Configurazione_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Configurazione_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_°) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop(vuoto (*cb)(vuoto));
int IMP_ISP_Configurazione_SetHiLightDepress(uint32_t forza);
int IMP_ISP_Configurazione_SetTemperStrength(uint32_rapporto t);
int IMP_ISP_Configurazione_SetSinterStrength(uint32_rapporto t);
int IMP_ISP_Configurazione_SetDPStrength(uint32_rapporto t);
int IMP_ISP_Configurazione_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *attr);


