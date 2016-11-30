#include <iostream>
#include "gtest/gtest.h"
#include "SoundexListener.h"

using namespace testing;

int main(int argc, char** argv) {
	InitGoogleTest(&argc, argv);
	// uncomment these lines to turn on the "TDD smackdown tool":
//    TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
//    listeners.Append(new SoundexListener);
	RUN_ALL_TESTS();
	// uncomment if you want to keep a VS popup console from closing before you can read it:
//	std::getchar();
}
