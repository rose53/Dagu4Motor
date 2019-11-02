#ifndef Dagu4Motor_h  
#define Dagu4Motor_h
 
#include "Arduino.h" 
#include "Motor.h" 

class Dagu4Motor  
{  
	static void isrFrontLeft();
	static void isrRearLeft();
	static void isrFrontRight();
	static void isrRearRight();
	
public:  
	/*
	 * C'tor
	 */
    Dagu4Motor(Motor motor, int pwmPin, int dirPin, int currPin, int encPin, bool reverseDirection = false); 
	
    void stopMotor();  
    void setSpeed(int speed);  
	/*
	 * Returns the value set on the PWM pin
	 */
	int getSpeed(void)  { return _speed; }
	
	void incSpeed(void) { setSpeed(getSpeed() + 1); }
	void decSpeed(void) { setSpeed(getSpeed() - 1); }
	
    void setMotorDirection(bool direction);  
	bool getMotorDirection(void) { return _direction; }
	/**
	 * Returns the current in mA
	 */
	int getCurrent();
	
	float getDistance();
	
	
	void setValue(const char value);
	
	unsigned long getLastPulse() { return micros() - _time; }
	
private:
		
	void handleEncoderInterrupt();
	
private:  

	Motor _motor;
    int   _pwmPin;  
    int   _dirPin; 
	int   _currPin;
	int   _currRate;
	int   _encPin;
	float _distance;
	int   _speed;
	bool  _direction;
	bool  _directionFirstTime;
	bool  _reverseDirection;
	
	volatile unsigned long _pulse;   // Time between pulses
    volatile unsigned long _time;    // Time when the last pulse got in
	
	static Dagu4Motor* _instanceFrontLeft;
	static Dagu4Motor* _instanceRearLeft;
	static Dagu4Motor* _instanceFrontRight;
	static Dagu4Motor* _instanceRearRight;
};


#endif