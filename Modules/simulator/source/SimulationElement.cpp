#include "SimulationElement.h"
#include <iostream>
using namespace simulation;

SimulationElement::SimulationElement() :
	id(0),
	name("NewElement"),
	position(Eigen::Vector3d()),
	orientation(Eigen::Quaterniond(1.0, 0.0, 0.0, 0.0)),
	mass(1)
{
	std::cout << "New generic element created." << std::endl;
}


SimulationElement::SimulationElement(
	int id,
	std::string name,
	Eigen::Vector3d position,
	Eigen::Quaterniond orientation,
	double mass) :
	id(id),
	name(name),
	position(position),
	orientation(orientation),
	mass(mass)
{
	std::cout << "Element " + name + " created, id (" + std::to_string(id) + ")" << std::endl;
}


SimulationElement::SimulationElement(const SimulationElement& other) :
	id(other.id),
	name(other.name),
	position(other.getPosition()),
	orientation(other.getOrientation()),
	mass(other.mass)
{
}

Eigen::Vector3d SimulationElement::getPosition() const {
	std::shared_lock<std::shared_mutex> lk(dataMutex);
	return this->position;
}

void SimulationElement::setPosition(double x, double y, double z) {
	std::unique_lock<std::shared_mutex> lk(dataMutex);
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

void SimulationElement::setPosition(const Eigen::Vector3d& position) {
	std::unique_lock<std::shared_mutex> lk(dataMutex);
	this->position = position;
}


Eigen::Quaterniond SimulationElement::getOrientation() const {
	std::shared_lock<std::shared_mutex> lk(dataMutex);
	return this->orientation;
}

void SimulationElement::setOrientation(const Eigen::Quaterniond& orientation) {
	std::unique_lock<std::shared_mutex> lk(dataMutex);
	this->orientation = orientation;
}

void SimulationElement::setTime(unsigned long time) {
	this->simulationTime = time;
}


void SimulationElement::update(unsigned long newTime) {
	// generic element does nothing. Only sets new time.
	this->simulationTime = newTime;
}

SimulationElement::~SimulationElement() {

}