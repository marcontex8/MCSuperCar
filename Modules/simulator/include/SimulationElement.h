#ifndef SIMULATIONELEMENT_H
#define SIMULATIONELEMENT_H

#include <string>
#include <Eigen/Dense>
#include <shared_mutex>

static int elements_id = 0;

namespace simulation {
	class SimulationElement {
	protected:
		Eigen::Vector3d position;
		Eigen::Quaterniond orientation;
		mutable std::shared_mutex dataMutex;

	public:
		const std::string name;
		const double mass;
		const int id;


		SimulationElement();
		SimulationElement(
			int id,
			std::string name,
			Eigen::Vector3d position,
			Eigen::Quaterniond(),
			double mass);
		SimulationElement(const SimulationElement& other);

		Eigen::Vector3d getPosition() const;
		void setPosition(double x, double y, double z);
		void setPosition(const Eigen::Vector3d& position);

		Eigen::Quaterniond getOrientation() const;
		void setOrientation(const Eigen::Quaterniond& orientation);

		virtual ~SimulationElement();
	};
}


#endif