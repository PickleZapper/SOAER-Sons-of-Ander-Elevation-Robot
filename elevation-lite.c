#pragma config(Sensor, in1,    conveyerAngle,  sensorPotentiometer)
#pragma config(Sensor, in2,    lineFollower,   sensorLineFollower)
#pragma config(Sensor, in3,    position,       sensorPotentiometer)
#pragma config(Motor,  port1,           flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightConveyer, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port5,           leftConveyer,  tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           conveyerElevator, tmotorVex393_MC29, openLoop)


void startConveyerUp(bool up){
	if(up){
		startMotor(leftConveyer,127);
		startMotor(rightConveyer,127);
	}
	else{
		startMotor(leftConveyer,-127);
		startMotor(rightConveyer,-127);
	}
}
//method to start conveyer belt
//if up, spool up, else spool down


task main()
{
	bool tank = true;
	while(true){

		//MOVEMENT
		if(tank){
			startMotor(rightMotor, vexRT(Ch1));
			startMotor(leftMotor, vexRT(Ch3));
		}//tank controls; should work no problem
		else{
			if(vexRT(Ch2)<0){
				startMotor(rightMotor, vexRT(Ch1));
				startMotor(leftMotor,(vexRT(Ch1)*(128+2*vexRT(Ch2))/128));
			}
			else
			{
				startMotor(rightMotor,(vexRT(Ch1)*(128-2*vexRT(Ch2))/128));
				startMotor(leftMotor, vexRT(Ch2));
			}
		}//arcade controls; pray to god they work

		//CONVEYER SPOOLING
		if(vexRT(Btn6U) == 1){
			startConveyerUp(true);
		}
		else if(vexRT(Btn6D) == 1){
			startConveyerUp(false);
		}
		else{
			stopMotor(leftConveyer);
			stopMotor(rightConveyer);
		}
		//if holding right trigger up, move conveyer up
		//if holding right trigger down, move conveyer down
		//else, hold motors

		//CONVEYER ELEVATION
		if(vexRT(Btn5U)==1){
			startMotor(conveyerElevator, 127);
		}
		else if(vexRT(Btn5D)==1){
			startMotor(conveyerElevator, -127);
		}
		else{
			stopMotor(conveyerElevator);
		}
		//if holding left up trigger, move conveyer up
		//if holding left down trigger, move conveyer down
		//else, hold position
	}


}
