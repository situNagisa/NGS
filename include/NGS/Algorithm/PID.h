#pragma once

#include "NGS/base/base.h"
#include "NGS/math/math.h"

NGS_BEGIN

class NGS_DLL_API  PID {
public:
	PID() {
		_Initialize();
	}
	PID(double p, double i, double d);
	PID(double p, double i, double d, double f);
	/**
	 * Configure the Proportional gain parameter. <br>
	 * this->responds quicly to changes in _setpoint, and provides most of the initial driving force
	 * to make corrections. <br>
	 * Some systems can be used with only a _P gain, and many can be operated with only PI.<br>
	 * For position based controllers, this->is the first parameter to tune, with _I second. <br>
	 * For rate controlled systems, this->is often the second after F.
	 *
	 * @param p Proportional gain. Affects output according to <b>output+=_P*(_setpoint-current_value)</b>
	 */
	void SetP(double);
	/**
	 * Changes the _I parameter <br>
	 * this->is used for overcoming disturbances, and ensuring that the controller always gets to the control mode.
	 * Typically tuned second for "Position" based modes, and third for "Rate" or continuous based modes. <br>
	 * Affects output through <b>output+=previous_errors*Igain ;previous_errors+=current_error</b>
	 *
	 * @see {@link #SetMaxIOutput(double) SetMaxIOutput} for how to restrict
	 *
	 * @param i New gain value for the Integral term
	 */
	void SetI(double);
	void SetD(double);
	/**Configure the FeedForward parameter. <br>
	 * this->is excellent for Velocity, rate, and other	continuous control modes where you can
	 * expect a rough output value based solely on the setpoint.<br>
	 * Should not be used in "position" based control modes.
	 *
	 * @param f Feed forward gain. Affects output according to <b>output+=F*Setpoint</b>;
	 */
	void SetF(double);
	/** Create a new PID object.
	 * @param p Proportional gain. Large if large difference between setpoint and target.
	 * @param i Integral gain.	Becomes large if setpoint cannot reach target quickly.
	 * @param d Derivative gain. Responds quickly to large changes in error. Small values prevents _P and _I terms from causing overshoot.
	 */
	void SetPID(double, double, double);
	void SetPID(double, double, double, double);
	/**Set the maximum output value contributed by the _I component of the system
	 * this->can be used to prevent large windup issues and make tuning simpler
	 * @param maximum. Units are the same as the expected output value
	 */
	void SetMaxIOutput(double);
	/**Specify a maximum output. If a single parameter is specified, the minimum is
	 * set to (-maximum).
	 * @param output
	 */
	void SetOutputLimits(double);
	/**
	 * Specify a maximum output.
	 * @param minimum possible output value
	 * @param maximum possible output value
	 */
	void SetOutputLimits(double, double);
	/** Set the operating direction of the PID controller
	 * @param _reversed Set true to reverse PID output
	 */
	void SetDirection(bool);
	/**Set the target for the PID calculations
	 * @param _setpoint
	 */
	void SetSetpoint(double);
	/**
	 * Resets the controller. this->erases the _I term buildup, and removes _D gain on the next loop.
	 */
	void Reset();
	/**Set the maximum rate the output can increase per cycle.
	 * @param rate
	 */
	void SetOutputRampRate(double);
	/** Set a limit on how far the _setpoint can be from the current position
	 * <br>Can simplify tuning by helping tuning over a small range applies to a much larger range.
	 * <br>this->limits the reactivity of _P term, and restricts impact of large _D term
	 * during large _setpoint adjustments. Increases lag and _I term if range is too small.
	 * @param range
	 */
	void SetSetpointRange(double);
	/**Set a filter on the output to reduce sharp oscillations. <br>
	 * 0.1 is likely a sane starting value. Larger values _P and _D oscillations, but force larger _I values.
	 * Uses an exponential rolling sum filter, according to a simple <br>
	 * <pre>output*(1-strength)*sum(0..n){output*strength^n}</pre>
	 * @param output valid between [0..1), meaning [current output only.. historical output only)
	 */
	void SetOutputFilter(double);
	/**
	 * Calculates the PID value using the last provided _setpoint and actual valuess
	 * @return calculated output value for driving the actual to the target
	 */
	double GetOutput();
	/**
	 *
	 * @param actual
	 * @return calculated output value for driving the actual to the target
	 */
	double GetOutput(double);
	/** Calculate the PID value needed to hit the target _setpoint.
	* Automatically re-calculates the output at each call.
	* @param actual The monitored value
	* @param target The target value
	* @return calculated output value for driving the actual to the target
	*/
	double GetOutput(double, double);

private:
	void _CheckSigns();
	void _Initialize();
#undef _P
#undef _I
#undef _D
#undef _F
	double _P;
	double _I;
	double _D;
	double _F;

	double _maxIOutput;
	double _maxError;
	double _ErrorSum;

	double _maxOutput;
	double _minOutput;

	double _setpoint;

	double _lastActual;

	bool _firstRun;
	bool _reversed;

	double _outputRampRate;
	double _lastOutput;

	double _outputFilter;

	double _setpointRange;
};

NGS_END