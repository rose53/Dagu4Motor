#include "Arduino.h"  
#include "Dagu4Motor.h"

Dagu4Motor* Dagu4Motor::_instanceFrontLeft;
Dagu4Motor* Dagu4Motor::_instanceRearLeft;
Dagu4Motor* Dagu4Motor::_instanceFrontRight;
Dagu4Motor* Dagu4Motor::_instanceRearRight;
	
Dagu4Motor::Dagu4Motor(Motor motor, int pwmPin, int dirPin, int currPin, int encPin, bool reverseDirection):
	_motor(motor),
	_pwmPin(pwmPin),
	_dirPin(dirPin),
	_currPin(currPin),
	_encPin(encPin),
	_currRate(0),
	_speed(0),
	_directionFirstTime(true),
	_direction(true),
	_reverseDirection(reverseDirection)
{  	
	pinMode(_pwmPin, OUTPUT);  
    pinMode(_dirPin, OUTPUT); 
	pinMode(_currPin, INPUT);
	
	switch (_motor)
    {
    case FRONT_LEFT: 
		attachInterrupt(_encPin,isrFrontLeft,CHANGE); 
		_instanceFrontLeft = this;
		break;    
    case REAR_LEFT: 
		attachInterrupt (_encPin,isrRearLeft,CHANGE); 
        _instanceRearLeft = this;
		break;
    case FRONT_RIGHT: 
		attachInterrupt (_encPin,isrFrontRight,CHANGE); 
        _instanceFrontRight = this;
		break;
    case REAR_RIGHT: 
		attachInterrupt (_encPin,isrRearRight,CHANGE); 
        _instanceRearRight = this;
		break;
    }  
	
}

void Dagu4Motor::stopMotor()  
{  
    digitalWrite(_pwmPin, LOW);  
    setSpeed(0);  
}  

void Dagu4Motor::setSpeed(int speed)  
{  
	_speed = constrain(speed, 0, 220);	
	analogWrite(_pwmPin, _speed);
}

void Dagu4Motor::setMotorDirection(bool direction)  
{  
	if (!_directionFirstTime && direction == _direction) {
		return;
	}
    if (direction)  
    {  
		if (!_reverseDirection) {
			digitalWrite(_dirPin, LOW);  //Set motor direction, 1 low, 2 high  
	    } else {
			digitalWrite(_dirPin, HIGH);  //Set motor direction, 1 low, 2 high  
		}
    } else {  
		if (!_reverseDirection) {
			digitalWrite(_dirPin, HIGH);  //Set motor direction, 1 low, 2 high  
	    } else {
			digitalWrite(_dirPin, LOW);  //Set motor direction, 1 low, 2 high  
		}
    }
    _direction = direction;
	_directionFirstTime = false;
}

void Dagu4Motor::setValue(char value) {
	
	if (value >= 0) {
		setMotorDirection(true);  
	} else {
		setMotorDirection(false);  
	}
	
	setSpeed(2 * abs(value));
	
}

int Dagu4Motor::getCurrent()
{
	int rawValue = analogRead(_currPin);
	return rawValue * (5.0 * 1000.0 / 1023.0);
}

void Dagu4Motor::handleEncoderInterrupt() {
	_pulse = micros() - _time;
    _time  = micros();
}

void Dagu4Motor::isrFrontLeft() {
	_instanceFrontLeft->handleEncoderInterrupt();  
}  
	
void Dagu4Motor::isrRearLeft() {
	_instanceRearLeft->handleEncoderInterrupt();  
}  

void Dagu4Motor::isrFrontRight() {
	_instanceFrontRight->handleEncoderInterrupt();  
}  

void Dagu4Motor::isrRearRight() {
	_instanceRearRight->handleEncoderInterrupt();  
}  
