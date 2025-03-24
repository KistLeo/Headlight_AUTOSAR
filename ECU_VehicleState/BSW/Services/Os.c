// /**
//  * @file OsekIntro_Example2.c
//  * @author Sarea Alhariri (Sarea.h95@outlook.com)
//  * @brief  Extended task and periodic event setting. 
//  * @version 0.1
//  * @date 2020-08-19
//  *
//  * @copyright Sarea Alhariri - All rights reserved
//  *
//  */


//  #include "os.h"
//  #include "Rte_VehicleStateSensor.h"
//  #include "VehicleStateSensor.h"
 
 
 
//  static uint8_t AppTask_PeriodicExtended_Toggle = 0U ; 
//  static int speed_check = 0;
//  static sint16 angle_check = 0;
 
//  bool hwinitFlag = false;
 
//  volatile uint8_t Simulate_Error = 0;
 
//  DeclareTask(AppTask_SensorProcessing);
//  DeclareTask(AppTask_InitHW);
 
 
 
//  void SystemInit(void)
//  {
//  }
//  int main(void)
//  {
//    StartOS();
//    while(1); /* Should not be executed */
//    return 0;
//  }
 
//  TASK(AppTask_SensorProcessing)
//  { 
//              while(true){
//                      WaitEvent(Ev_SensorUpdate);
//                      ClearEvent(Ev_SensorUpdate);
//                      AppTask_PeriodicExtended_Toggle ^= 1; 
//                    Rte_Ev_ReadSpeedAndSteering(&speed_check, &angle_check);  
//                      Rte_Ev_SendSensorData(); 
//                      if (OsCnt_GetSystemCounter() == 1000)
//                      {
//                          Simulate_Error = 1;
//                      }
//                      if (Simulate_Error == 1)
//                      {
//                          // printf("Sensor Task Failed! System will reset...\n");
//                          while (1)
//                              ;
//                      }
//              }
//  }
 
//  TASK(AppTask_InitHW)
//  {
//          if (hwinitFlag == false){
//              hwinitFlag = true;
//          }
     
 
//      TerminateTask(); 
//  }
 