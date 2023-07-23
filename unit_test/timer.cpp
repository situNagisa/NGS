#include "defined.h"

using namespace std::chrono_literals;

TEST(timer, delayCall) {
	NGS_LOGL(debug, "666");
	ngs::DelayCall::I().SetTimer([]() {NGS_LOGL(debug, "666"); }, 1s);
	std::this_thread::sleep_for(1s);
	ngs::DelayCall::I().Update();
}
