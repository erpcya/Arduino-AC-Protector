#include <Arduino.h>
// MEDICION DE VOLTAJE AC USANDO EL MOD ZMPT101

class WaitTime
{
	// Class Member Variables
	// These are initialized at startup
	int ledPin;      // the number of the LED pin
	unsigned long OnTime = 0;     // milliseconds of on-time
	unsigned long OffTime = 0 ;    // milliseconds of off-time

	// These maintain the current state
	int TimingOn;             		// TimingOn used to set the LED
	unsigned long previousMillis = 0;  	// will store last time LED was updated

  boolean endTimer= false;

  // Constructor - creates a WaitTime 
  // and initializes the member variables and state
  public:
  WaitTime(int pin, long on, long off)
  {
	ledPin = pin;
	pinMode(ledPin, OUTPUT);     
	  
	OnTime = on;
	OffTime = off;
	
	TimingOn = LOW; 
	previousMillis = 0;
  }

  //Action
  void Update()
  {
    // check to see if it's time to change state
    unsigned long currentMillis = millis();
     
    if((TimingOn == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
    	TimingOn = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, TimingOn);  // Update the actual state
    }
    else if ((TimingOn == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      TimingOn = HIGH;  // Turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, TimingOn);	  // Update the actual state
    }
  }

  boolean timer(unsigned long OnTime){
    unsigned long currentMillis = millis();
     endTimer = false;   
        if(currentMillis - previousMillis >= OnTime)
        {
          endTimer =  true;
          previousMillis = currentMillis;  // Remember the time
        } else
        {
          endTimer =  false;
        }
        
        return endTimer;
  }

  boolean crossingtimer(){
    unsigned long currentMillis = millis();
     endTimer = false;   
        if(currentMillis - previousMillis >= 500)
        {
          endTimer =  true;
          previousMillis = currentMillis;  // Remember the time
        } else
        {
          endTimer =  false;
        }
        
        return endTimer;
  }

};

class zeroCrossing : public WaitTime {
	// Class Member Variables
	// These are initialized at startup
  int aPin;
  int max = 0;
  int min = 1023;
	// These maintain the current state
	unsigned long previousMillis;  	// will store last time LED was updated

  
  // Constructor - creates a zeroCrossing 
  // and initializes the member variables and state
  public:
  zeroCrossing(int pin)
  {
    aPin = pin;   
    previousMillis = 0;
  }
  
  // 
  //Action
  int getMaxValue()
  {
    // check to see if it's time to change state

    boolean waiting = crossingtimer();
    if(waiting)
    {
          // read the input on analog pin 0:
      int sensorValue = analogRead(aPin);

      if(sensorValue > max){
         max=sensorValue;
      }
    }
   return max;
  }

int getMinValue()
  {
    // check to see if it's time to change state
    int max = 0;
    int min = 1023;
    boolean waiting = crossingtimer();
    if(waiting)
    {
          // read the input on analog pin 0:
      int sensorValue = analogRead(aPin);

      if(sensorValue < min){
         min=sensorValue;
      }
    }
   return max;
  }

};

/* class readVoltage
{
	// Class Member Variables
	// These are initialized at startup
	 private:
    int SensorPin;      // the number of the Analog pin
	  int Adc_max;      //Reemplazar por valor adc_max entregado por el sketch: volt_ac_cal
    int Adc_min;
    int Volt_inst;
    int Volt;
    

	
    float Volt_multi; //Reemplazar por el "voltaje ac rms" entregado por un multimetro
    float volt_multi_p;
    float volt_multi_n;

	  unsigned long previousMillis;  	// will store last time of read was updated
   
  // Constructor - creates a read Voltage
  // and initializes the member variables and state
  public:
  readVoltage(int sensorPin,float volt_multi,int adc_max, int adc_min)
  {
	  pinMode(sensorPin, OUTPUT);     
    SensorPin = sensorPin;
    Volt_multi = volt_multi;
    Adc_max = adc_max;
    Adc_min = adc_min;
    volt_multi_p = volt_multi * 1.4142;   //Voltaje pico= Voltaje RMS * 1.4142 (Corriente Monofasica)
    volt_multi_n = volt_multi_p * -1;  
	  previousMillis = 0;
  }

  //Action
  void readVoltage()
  {
      int Adc_sample;
      int Sumatory;
      int N;
      int rVolt;
      unsigned long currentMillis = millis();
    // check to see if it's time to change state
        if ( currentMillis - previousMillis >= 500) //Duración 0.5 segundos(Aprox. 30 ciclos de 60Hz)
    {
        Adc_sample = analogRead(SensorPin);    //voltaje del sensor
        Volt_inst = map(Adc_sample, Adc_min, Adc_max, volt_multi_n, volt_multi_p);
        Sumatory= Sumatory + sq(Volt_inst);  //Sumatoria de Cuadrados
        N = N + 1;
        previousMillis = currentMillis;  // Remember the time
         rVolt = sqrt((Sumatory) / N); //ecuación del RMS
    return Volt=rVolt;
    }
  }
}; */


int adc_max = 680;      //Reemplazar por valor adc_max entregado por el sketch: volt_ac_cal
int adc_min = 374;      //Reemplazar por valor adc_min entregado por el sketch: volt_ac_cal
float volt_multi = 120; //Reemplazar por el "voltaje ac rms" entregado por un multimetro
float volt_multi_p;
float volt_multi_n;

WaitTime led1(11, 123, 400);
WaitTime led2(12, 350, 350);

void setup() {
  pinMode(8, OUTPUT);
}


void loop() {
    led1.Update();
    led2.Update();
}
