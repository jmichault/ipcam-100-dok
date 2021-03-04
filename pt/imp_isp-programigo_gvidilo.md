# IMP_ISP (voir imp_isp.h)
Processamento de imagem. Inclui principalmente configurações de efeitos de imagem, troca de modo e gravação, adição e remoção de sensor.

O módulo ISP não tem nada a ver com fluxo de dados e não precisa ser conectado, ele só funciona em termos de configuração de efeito e controle de sensor.

## Ativação

As etapas para ativar um módulo ISP são as seguintes:
* etapa 1: Crie um módulo ISP

```
int ret = 0;
  // étape 1 : 
  ret = IMP_ISP_Open (); 
  if (ret <0) {
    printf ("Échec de ISPInit\n");
    return -1;
  }
```
* Etapa 2: Adicionar sensor, o driver do sensor foi adicionado ao kernel antes desta operação.



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
* Passo 3: Ative o sensor, ele começará a produzir imagens.



```
  ret = IMP_ISP_EnableSensor (void);
  if (ret <0) {
  printf ("Impossible d'activer le capteur \n");
  return -1;
 }
```
* Etapa 4: Ative as configurações:



```
  ret = IMP_ISP_EnableTuning (); 
  if (ret <0) {
  printf ("Impossible d'activer le réglage \n");
  return -1;
 }
```
* Etapa 5: invocar a interface de depuração do ISP: consulte a documentação da interface de depuração do ISP.




## Desativando um módulo ISP

As etapas para desinstalar o módulo ISP são as seguintes:
* etapa 1: Desative a configuração do ISP

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
* Etapa 2: Feche os sensores. (FrameSource deve ser fechado antes desta operação)



```
ret = IMP_ISP_DisableSensor (); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```

* Passo 3: remova os sensores, os sensores devem ser fechados antes desta operação.



```
ret = IMP_ISP_DelSensor (& sensor); 
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```
* Etapa 4: Limpe o módulo ISP, todos os sensores devem ser removidos antes desta operação.



```
ret = IMP_ISP_Close ();
  if (ret <0) {
  printf ("Impossible de désactiver le capteur \n");
  return -1;
 }
```



## lista de funções

int IMP_ISP_Aberto(vazio);
int IMP_ISP_Fechar(vazio);
int IMP_ISP_AddSensor(IMPSensorInfo *pinfo);
int IMP_ISP_DelSensor(IMPSensorInfo *pinfo);
int IMP_ISP_EnableSensor(vazio);
int IMP_ISP_DisableSensor(vazio);
int IMP_ISP_SetSensorRegister(uint32_t reg, uint32_valor t);
int IMP_ISP_GetSensorRegister(uint32_t reg, uint32_t *valor);
int IMP_ISP_EnableTuning(em branco);
int IMP_ISP_DisableTuning(em branco);
int IMP_ISP_Configuração_SetSensorFPS(uint32_t fps_num, uint32_t fps_den);
int IMP_ISP_Tuning_GetSensorFPS(uint32_t *fps_num, uint32_t *fps_den);
int IMP_ISP_Configuração_SetAntiFlickerAttr(IMPISPAntiflickerAttr attr);
int IMP_ISP_Tuning_GetAntiFlickerAttr(IMPISPAntiflickerAttr *pattr);
int IMP_ISP_Configuração_SetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Tuning_GetRawDRC(IMPISPDrcAttr *pinfo);
int IMP_ISP_Configuração_SetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Tuning_GetSinterDnsAttr(IMPISPSinterDenoiseAttr *pinfo);
int IMP_ISP_Configuração_SetTemperDnsCtl(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Configuração_GetTemperDnsAttr(IMPISPTemperDenoiseAttr *pinfo);
int IMP_ISP_Tuning_SetWDRAttr(IMPISPT modo deuningOpsMode);
int IMP_ISP_Configuração_GetWDRAttr(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetSceneMode(modo IMPISPSceneMode);
int IMP_ISP_Configuração_GetSceneMode(IMPISPSceneMode *pmode);
int IMP_ISP_Tuning_SetColorfxMode(IMPISPColorfxMode mode);
int IMP_ISP_Configuração_GetColorfxMode(IMPISPColorfxMode *pmode);
int IMP_ISP_Tuning_Definir brilho(sinal sem nome brilhante);
int IMP_ISP_Configuração_GetBrightness(unsigned char *pbright);
int IMP_ISP_Tuning_SetContrast(contraste de caractere sem nome);
int IMP_ISP_Configuração_GetContrast(unsigned char *pcontrast);
int IMP_ISP_Tuning_Definir nitidez(nitidez sem nome nitidez);
int IMP_ISP_Configuração_GetSharpness(unsigned char *psharpness);
int IMP_ISP_Tuning_Definir Saturação(sinal sem nome (a 22 °);
int IMP_ISP_Configuração_GetSaturation(unsigned char *psat);
int IMP_ISP_Tuning_SetISPProcess(modo IMPISPTuningOpsMode);
int IMP_ISP_Configuração_SetFWFreeze(IMPISPTuningOpsMode mode);
int IMP_ISP_Tuning_SaveAllParam(char *caminho);
int IMP_ISP_Configuração_SetISPBypass(IMPISPTuningOpsMode enable);
int IMP_ISP_Tuning_GetTotalGain(uint32_t *gain);
int IMP_ISP_Tuning_Definir ISPHflip(IMPISPTuningOpsMode modo);
int IMP_ISP_Configuração_GetISPHflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPVflip(IMPISPT modo deuningOpsMode);
int IMP_ISP_Configuração_GetISPVflip(IMPISPTuningOpsMode *pmode);
int IMP_ISP_Tuning_SetISPRunningMode(modo IMPISPRunningMode);
int IMP_ISP_Configuração_GetISPRunningMode(IMPISPRunningMode *pmode);
int IMP_ISP_Tuning_SetAeStrategy(Estratégia IMPISPAeStrategy);
int IMP_ISP_Configuração_GetAeStrategy(IMPISPAeStrategy *pstrategy);
int IMP_ISP_Tuning_SetGamma(IMPISPGamma *intervalo);
int IMP_ISP_Configuração_GetGamma(IMPISPGamma *gamma);
int IMP_ISP_Tuning_SetAeComp(int comp);
int IMP_ISP_Configuração_GetAeComp(int *comp);
int IMP_ISP_Tuning_SetExpr(IMPISPExpr *ekspr);
int IMP_ISP_Configuração_GetExpr(IMPISPExpr *expr);
int IMP_ISP_Tuning_AE_GetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_AE_SetROI(IMPISPAERoi *isp_ae_roi);
int IMP_ISP_Tuning_SetWB(IMPISPWB *wb);
int IMP_ISP_Configuração_GetWB(IMPISPWB *wb);
int IMP_ISP_Tuning_GetWB_Statis(IMPISPWB *wb);
int IMP_ISP_Tuning_Awb_GetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_Awb_SetCwfShift(IMPISPWB *isp_wb_attr);
int IMP_ISP_Tuning_SetMaxAgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxAgain(uint32_t *gain);
int IMP_°) ISP_Tuning_SetMaxDgain(uint32_t gain);
int IMP_ISP_Tuning_GetMaxDgain(uint32_t *gain);
int IMP_ISP_Tuning_SetVideoDrop() vazio (*cb)(vazio));
int IMP_ISP_Configuração_SetHiLightDepress(uint32_t força);
int IMP_ISP_Configuração_SetTemperStrength(uint32_relação t);
int IMP_ISP_Configuração_SetSinterStrength(uint32_relação t);
int IMP_ISP_Configuração_SetDPStrength(uint32_relação t);
int IMP_ISP_Configuração_SetAntiFogAttr(IMPISPAntiFogAttr attr);
int IMP_ISP_Tuning_GetEVAttr(IMPISPEVAttr *atr);


