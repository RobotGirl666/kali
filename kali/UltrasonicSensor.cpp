/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UltrasonicSensor.cpp
 * Author: vangelis
 * 
 * Created on 26 April 2020, 7:38 pm
 */

#include <wiringPi.h>
#include <softPwm.h>

#include "Logging.h"
#include "UltrasonicSensor.h"
#include "MicroTimer.h"

UltrasonicSensor::UltrasonicSensor() {
    pinTrigger = 31; //Define the pinTrigger connect to wiringPi port 31 of Raspberry pi
    pinEcho = 30; //Define the EchoPin connect to wiringPi port 30 of Raspberry pi
    
    // initialise the pservo direction
    dir = Up;
}

UltrasonicSensor::UltrasonicSensor(const UltrasonicSensor& orig) {
}

UltrasonicSensor::~UltrasonicSensor() {
}

/**
 * 
 *   Initialises the Wiring Pi library for each set of pins relating to the motor that drives these wheels (could be left or right set of wheels).
 *
 */
void UltrasonicSensor::initialise()
{
    // initialise ultrasonic pins
    pinMode(pinTrigger, OUTPUT);
    pinMode(pinEcho, INPUT);
    
    // initialise servo
    horizontalServo.initialise(4);
}

void UltrasonicSensor::roam(int speed, int seconds)
{
    Logging* kaliLog = Logging::Instance();
    // first do a full sweep so we get a lay of the land
    fullSweep();
    /*
    // let's use the dodgy yaboom code
    horizontalServo.setPos(90);
    float dist = Distance_test();
    string message = "Distance: " + to_string(dist);
    kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    */
}

void UltrasonicSensor::fullSweep()
{
    Logging* kaliLog = Logging::Instance();
    kaliLog->log(typeid(this).name(), __FUNCTION__, "Commencing ultrsonic sweep.");

    // re-initialise the position and movement variables
    dir = Up;
    
    for (int angle = 0; angle <= 180; angle += 10)
    {
        // set the servo to the specified angle
        horizontalServo.setPos(angle);
        
        // measure the distance and store in the array
        dists[angle / 10] = getDistance();

        string message = "Angle: " + to_string(angle) + " distance: " + to_string(dists[angle / 10]);
        kaliLog->log(typeid(this).name(), __FUNCTION__, message);
    }
    
    // future distance measurements will sweep the opposite way
    dir = Down;
}

/**
 * 
 * Get the distance to the object in front of the sensor in mm
 * 
 * @param int limit - maximum distance (can't wait forever for horizon readings)
 *                    default is set to 10,000mm (10m)
 *                    time calculations assume speed of sound of 343 m/s which is true for air at STP
 * 
 * @return int - Nubmer of mm to object
 * 
 */
int UltrasonicSensor::getDistance(int limit)
{
    int distance = limit;
    MicroTimer mt;
    
    // time to get a pulse back from the limit distance in microseconds
    long limitTime = (limit * 2) * 1000 / 343;
    
    // send a pulse of at least 15 microseconds
    digitalWrite(pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pinTrigger, HIGH);
    mt.start(); // start the timer at the start of the pulse and finish once it comes back (leading edge)
    delayMicroseconds(15);
    digitalWrite(pinTrigger, LOW);
    
    // wait for pulse to come back
    while(!digitalRead(pinEcho) == 1)
    {
        if (mt.check() < limitTime)  // stop if exceeds maximum value
        {
            mt.start(); // start timing the length of the echo pulse which will be the distance in microsectonds
            
            // now wait for the pulse to finish and time it
            while(!digitalRead(pinEcho) == 0)
            {
                if (mt.check() > limitTime)  // stop if exceeds maximum value
                {
                    break;
                }
            }
            distance = mt.getCheck() * 343 / 2 / 1000; // distance in mm
            
            // clean it up in case it is a few microseconds over
            if (distance > limit)
            {
                distance = limit;
            }
        }
    }

    return distance;
}

/**
* Function       Distance
* @author        Danny
* @date          2017.08.16
* @brief         measure the distance by Ultrasonic
* @param[in]     void
* @param[out]    void
* @retval        float:distance
* @par History   
*/
float UltrasonicSensor::Distance()
{
	float distance;
	struct timeval tv1;
	struct timeval tv2;
	struct timeval tv3;
	struct timeval tv4;
	long start, stop;
	
	digitalWrite(pinTrigger, LOW);
	delayMicroseconds(2);
	digitalWrite(pinTrigger, HIGH);      //Input a high level of at least 10 US to the Trig pin
	delayMicroseconds(15);
	digitalWrite(pinTrigger, LOW);
    
    gettimeofday(&tv3, NULL);      
	start = tv3.tv_sec * 1000000 + tv3.tv_usec;
	while(!digitalRead(pinEcho) == 1)
	{
		gettimeofday(&tv4, NULL);    
		stop = tv4.tv_sec * 1000000 + tv4.tv_usec;
		
		if ((stop - start) > 30000)  //Maximum time value (5m)：10/340=0.03s
		{
			return -1;              
		}
	} 
	
	gettimeofday(&tv1, NULL);      
    start = tv1.tv_sec*1000000+tv1.tv_usec;
	while(!digitalRead(pinEcho) == 0)
	{
		gettimeofday(&tv3,NULL);   
		stop = tv3.tv_sec*1000000+tv3.tv_usec;
		if ((stop - start) > 30000)
		{
			return -1;
		}
	}                              
	gettimeofday(&tv2, NULL);      

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop = tv2.tv_sec * 1000000 + tv2.tv_usec;

	distance = (float)(stop - start)/1000000 * 34000 / 2;
	return distance;
}

/**
* Function       bubble
* @author        Danny
* @date          2017.08.16
* @brief         Bubble sorting 
* @param[in1]    a:Ultrasonic array first address
* @param[in2]    n:Size of Ultrasonic array 
* @param[out]    void
* @retval        void
* @par History   
*/
void UltrasonicSensor::bubble(unsigned long *a, int n)

{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

/**
* Function       Distane_test
* @author        Danny
* @date          2017.08.16
* @brief         Remove the maximum, minimum of the 5 datas, and get average values of 3 datas to improve accuracy of test
* @param[in]     void
* @param[out]    void
* @retval        float:distance
* @par History   
*/
float UltrasonicSensor::Distance_test()
{
  float distance;
  unsigned long ultrasonic[5] = {0};
  int num = 0;
  while (num < 5)
  {
     distance = Distance();
	 while((int)distance == -1)
	 {
		 distance = Distance();
	 }
    //Filter out data greater than 500 or smaller than 0 in the test distance
    while ( (int)distance >= 500 || (int)distance == 0)
    {
         distance = Distance();
    }
    ultrasonic[num] = distance;
    num++;
	delay(10);
  }
  num = 0;
  bubble(ultrasonic, 5);
  distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  
  printf("distance:%f\n",distance);      
  return distance;
}