

#include "BH1750.h"
BH1750 sensor(0x23, Wire);

String mode;
bool isDay=false;

void setup()
{
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  Serial.begin();
}

void loop()
{
  sensor.make_forced_measurement();

  Serial.println(String::format("%f lux", sensor.get_light_level()));
  
  if(sensor.get_light_level()>100 && !isDay){
      mode="BRIGHT";
      Particle.publish("mode",mode, PRIVATE);
      isDay=true;
  }
  
  else if(sensor.get_light_level()<100 && isDay){
      mode="DARK";
      Particle.publish("mode",mode , PRIVATE);
      isDay=false;
  }
  

  delay(1000);
}
