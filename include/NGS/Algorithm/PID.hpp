#include "NGS/Algorithm/PID.h"

NGS_BEGIN

inline PID::PID(double p, double i, double d) {
	_Initialize();
	_P = p; _I = i; _D = d;
}
inline PID::PID(double p, double i, double d, double f) {
	_Initialize();
	_P = p; _I = i; _D = d; _F = f;
}
inline void PID::_Initialize() {
	_P = 0;
	_I = 0;
	_D = 0;
	_F = 0;

	_maxIOutput = 0;
	_maxError = 0;
	_ErrorSum = 0;
	_maxOutput = 0;
	_minOutput = 0;
	_setpoint = 0;
	_lastActual = 0;
	_firstRun = true;
	_reversed = false;
	_outputRampRate = 0;
	_lastOutput = 0;
	_outputFilter = 0;
	_setpointRange = 0;
}

inline void PID::SetP(double p) {
	_P = p;
	_CheckSigns();
}

inline void PID::SetI(double i) {
	if (_I != 0) {
		_ErrorSum = _ErrorSum * _I / i;
	}
	if (_maxIOutput != 0) {
		_maxError = _maxIOutput / i;
	}
	_I = i;
	_CheckSigns();
	/* Implementation note:
	* this->Scales the accumulated error to avoid output errors.
	* As an example doubling the _I term cuts the accumulated error in half, which results in the
	* output change due to the _I term constant during the transition.
	*
	*/
}

inline void PID::SetD(double d) {
	_D = d;
	_CheckSigns();
}

inline void PID::SetF(double f) {
	_F = f;
	_CheckSigns();
}


inline void PID::SetPID(double p, double i, double d) {
	_P = p; _I = i; _D = d;
	_CheckSigns();
}

inline void PID::SetPID(double p, double i, double d, double f) {
	_P = p; _I = i; _D = d; _F = f;
	_CheckSigns();
}


inline void PID::SetMaxIOutput(double maximum) {
	/* Internally _maxError and Izone are similar, but scaled for different purposes.
	 * The _maxError is generated for simplifying math, since calculations against
	 * the max error are far more common than changing the _I term or Izone.
	 */
	_maxIOutput = maximum;
	if (_I != 0) {
		_maxError = _maxIOutput / _I;
	}
}


inline void PID::SetOutputLimits(double output) { SetOutputLimits(-output, output); }


inline void PID::SetOutputLimits(double minimum, double maximum) {
	if (maximum < minimum)return;
	_maxOutput = maximum;
	_minOutput = minimum;

	// Ensure the bounds of the _I term are within the bounds of the allowable output swing
	if (_maxIOutput == 0 || _maxIOutput > (maximum - minimum)) {
		SetMaxIOutput(maximum - minimum);
	}
}


inline void PID::SetDirection(bool _reversed) {
	this->_reversed = _reversed;
}

inline void PID::SetSetpoint(double _setpoint) {
	this->_setpoint = _setpoint;
}


inline double PID::GetOutput(double actual, double setPoint) {
	double output;
	double Poutput;
	double Ioutput;
	double Doutput;
	double Foutput;

	_setpoint = setPoint;

	//Ramp the setPoint used for calculations if user has opted to do so
	if (_setpointRange != 0) {
		setPoint = Clamp<double>(setPoint, actual - _setpointRange, actual + _setpointRange);
	}

	//Do the simple parts of the calculations
	double error = setPoint - actual;

	//Calculate _F output. Notice, this->depends only on the setPoint, and not the error. 
	Foutput = _F * setPoint;

	//Calculate _P term
	Poutput = _P * error;

	//If this->is our first time running this-> we don't actually _have_ a previous input or output. 
	//For sensor, sanely assume it was exactly where it is now.
	//For last output, we can assume it's the current time-independent outputs. 
	if (_firstRun) {
		_lastActual = actual;
		_lastOutput = Poutput + Foutput;
		_firstRun = false;
	}


	//Calculate _D Term
	//Note, this->is negative. this->actually "slows" the system if it's doing
	//the correct thing, and small values helps prevent output spikes and overshoot 

	Doutput = -_D * (actual - _lastActual);
	_lastActual = actual;



	//The Iterm is more complex. There's several things to factor in to make it easier to deal with.
	// 1. maxIoutput restricts the amount of output contributed by the Iterm.
	// 2. prevent windup by not increasing _ErrorSum if we're already running against our max Ioutput
	// 3. prevent windup by not increasing _ErrorSum if output is output=_maxOutput	
	Ioutput = _I * _ErrorSum;
	if (_maxIOutput != 0) {
		Ioutput = Clamp<double>(Ioutput, -_maxIOutput, _maxIOutput);
	}

	//And, finally, we can just add the terms up
	output = Foutput + Poutput + Ioutput + Doutput;

	//Figure out what we're doing with the error.
	if (_minOutput != _maxOutput && !In<double>(output, _minOutput, _maxOutput)) {
		_ErrorSum = error;
		// Reset the error sum to a sane level
		// Setting to current error ensures a smooth transition when the _P term 
		// decreases enough for the _I term to start acting upon the controller
		// From that point the _I term will build up as would be expected
	}
	else if (_outputRampRate != 0 && !In<double>(output, _lastOutput - _outputRampRate, _lastOutput + _outputRampRate)) {
		_ErrorSum = error;
	}
	else if (_maxIOutput != 0) {
		_ErrorSum = Clamp<double>(_ErrorSum + error, -_maxError, _maxError);
		// In addition to output limiting directly, we also want to prevent _I term 
		// buildup, so restrict the error directly
	}
	else {
		_ErrorSum += error;
	}

	//Restrict output to our specified output and ramp limits
	if (_outputRampRate != 0) {
		output = Clamp<double>(output, _lastOutput - _outputRampRate, _lastOutput + _outputRampRate);
	}
	if (_minOutput != _maxOutput) {
		output = Clamp<double>(output, _minOutput, _maxOutput);
	}
	if (_outputFilter != 0) {
		output = _lastOutput * _outputFilter + output * (1 - _outputFilter);
	}

	_lastOutput = output;
	return output;
}


inline double PID::GetOutput() {
	return GetOutput(_lastActual, _setpoint);
}


inline double PID::GetOutput(double actual) {
	return GetOutput(actual, _setpoint);
}


inline void PID::Reset() {
	_firstRun = true;
	_ErrorSum = 0;
}


inline void PID::SetOutputRampRate(double rate) {
	_outputRampRate = rate;
}


inline void PID::SetSetpointRange(double range) {
	_setpointRange = range;
}


inline void PID::SetOutputFilter(double strength) {
	if (strength == 0 || Clamp<double>(strength, 0, 1)) {
		_outputFilter = strength;
	}
}

/**
 * To operate correctly, all PID parameters require the same sign,
 * with that sign depending on the {@literal}_reversed value
 */
inline void PID::_CheckSigns() {
	if (_reversed) {	//all values should be below zero
		if (_P > 0) _P *= -1;
		if (_I > 0) _I *= -1;
		if (_D > 0) _D *= -1;
		if (_F > 0) _F *= -1;
	}
	else {	//all values should be above zero
		if (_P < 0) _P *= -1;
		if (_I < 0) _I *= -1;
		if (_D < 0) _D *= -1;
		if (_F < 0) _F *= -1;
	}
}

NGS_END