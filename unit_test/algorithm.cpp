#include "defined.h"

TEST(algorithm, PID) {
	ngs::PID pid(0.1, 0.01, 0);

	pid.SetOutputLimits(-100, 100);
	pid.SetOutputRampRate(10);

	double aim = 53.2;
	double cur = 0.0;
	/*ngs::nos.Log("TEST::PID", "start pid\n");
	size_t times = 0;
	while (!ngs::In(cur - aim, -1.0, 1.0))
	{
		auto out = pid.GetOutput(cur, aim);
		ngs::nos.Trace("[%d] current %lf,out %lf\n", times, cur, out);
		cur += out;
		times++;
	}
	ngs::nos.Trace("times %d\n", times);*/
}
