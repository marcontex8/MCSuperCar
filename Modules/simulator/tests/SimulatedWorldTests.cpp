#include "gtest/gtest.h"
#include "SimulationElement.h"
#include "SimulationController.h"
#include "Diagnostics.h"
#include "SimulatedWorld.h"


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


class SimulatedWorldTest : public ::testing::Test{
protected:
	SimulatedWorld world;
};

TEST_F(SimulatedWorldTest, WorldStartsEmpty) {
	ASSERT_EQ(world.numberOfElements(), 0);
}

TEST_F(SimulatedWorldTest, AddingOneElementIncreaseNumerOfElements) {
	world.addElement(SimulationElement());
	ASSERT_EQ(world.numberOfElements(), 1);
}

TEST_F(SimulatedWorldTest, GetElementAtIndexReturnsValidElement) {
	size_t numberOfElementsToAdd = 10;
	for (int i = 0; i < numberOfElementsToAdd; ++i) {
		world.addElement(SimulationElement());
	}
	for (int i = numberOfElementsToAdd - 1; i >= numberOfElementsToAdd; --i) {
		auto element = world.getElementAtIndex(i);
		ASSERT_NE(element, nullptr);
	}
}


class SimulationElementTest : public testing::TestWithParam<int> {
private:
	SimulationElement element;
public:
	SimulationElementTest() {

	};

};

TEST_P(SimulationElementTest, InitializeWithDifferentDataWorks) {
	auto element = SimulationElement(GetParam(), "ciao", Eigen::Vector3d(), Eigen::Quaterniond(), 10);
	ASSERT_EQ(element.getOrientation().w(), 1);
}

INSTANTIATE_TEST_SUITE_P(InitializeWithDifferentDataWorks,
	SimulationElementTest,
	testing::Values(1,2,3,4));
