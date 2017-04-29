#pragma once

#include "FuzzificationEntropy.h"
#include <iostream>
#include <cmath>


using namespace Datasets;

namespace FuzzificationLibrary
{
	class FuzzificationHierarchicalEntropy : public FuzzificationEntropy
	{
	private:
		double _treshold = 0;

	public:
		static constexpr double Theta = 0.01;
		FuzzificationHierarchicalEntropy(DataSets* dataToTransform);
		double getTreshold() const;
		void setTreshold(const double& value);
		void LastStepInFuzzification(int dimension, int interval) override;

	protected:
		bool ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious) override;
	};
}
