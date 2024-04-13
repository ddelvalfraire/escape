#include "pch.h"

class Calculator {
public:
	int add(int a, int b) {
		return a + b;
	}
};

TEST(newTest, someOtherTest) {
	ASSERT_TRUE(true);
}

TEST(CalculatorTest, addTest) {
	Calculator c;
	ASSERT_EQ(c.add(2, 2), 4);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}