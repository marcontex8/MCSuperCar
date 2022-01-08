#include "gtest/gtest.h"
#include "SimulationElement.h"
#include "SimulationController.h"
#include "Diagnostics.h"


extern Diagnostics diagnostics = Diagnostics();

using namespace simulation;

TEST(SimulationElementSuite, EmptyConstructorInitializeToDefault) {
	SimulationElement element;
	auto orientation = element.getOrientation();
	auto position = element.getPosition();
	EXPECT_DOUBLE_EQ(orientation.w(), 1.0);
	EXPECT_DOUBLE_EQ(orientation.x(), 0.0);
	EXPECT_DOUBLE_EQ(orientation.y(), 0.0);
	EXPECT_DOUBLE_EQ(orientation.z(), 0.0);

	EXPECT_DOUBLE_EQ(position.x(), 0.0);
	EXPECT_DOUBLE_EQ(position.y(), 0.0);
	EXPECT_DOUBLE_EQ(position.z(), 0.0);
}


class SimulationControllerTest : public ::testing::Test {
protected:
	SimulationController controller;

public:
	SimulationControllerTest() {
	}
	virtual ~SimulationControllerTest() {
	}
};



TEST_F(SimulationControllerTest, OnConstructionEverythingIsStopped) {
	ASSERT_TRUE(controller.getPause());
	ASSERT_TRUE(controller.getStop());
}