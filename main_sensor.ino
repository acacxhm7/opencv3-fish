#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 5    //引脚5输出温度

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celcius=0;          //摄氏温度

float PH_analogRead=0.0;  //模拟口读得的电压值
float PH_voltage=0.0;     //PH值对应输出的电压
float PH_value=0.0;       //PH值

float TU=0.0;             //模拟值转化为电压(0-5V)
float TU_value=0.0;       //浑浊度
float TU_calibration=0.0; //温度校准
float temp_data=25.0;     //暂时不鸟温度校准，直接定25C
float K_Value=3220.33;

void setup(void)
{
  
  Serial.begin(9600);
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);       //获得摄氏温度
  Serial.print(Celcius);                     //串口打印温度
  Serial.println("C");

  int PH_analogRead = analogRead(A2);       //获得PH温度A2引脚模拟值，
  float PH_voltage = PH_analogRead* (5.0 / 1024.0); // 模拟值转化为电压(0-5V)
  PH_value=-15.0*(PH_voltage)+16.01;        //电压转化为PH值公式
  if(PH_value<=0){PH_value=0;}
  if(PH_value>=14){PH_value=14;}
  Serial.print("PH Value:");
  Serial.println(PH_value);                 //串口打印PH值

  int sensorValue = analogRead(A0);         //获得浑浊度A0引脚模拟值
  float TU = sensorValue * (5.0 / 1024.0);  //模拟值转化为电压(0-5V)
  TU_calibration=-0.0192*(temp_data-25)+TU; //温度校准公式 
  TU_value=-865.68*TU_calibration + K_Value;//电压转化公式
  if(TU_value<=0){TU_value=0;}
  if(TU_value>=3000){TU_value=3000;}
  Serial.print("TU Value:");
  Serial.print(TU_value);                   //浑浊度
  Serial.println("NTU");

  delay(1000);
}
