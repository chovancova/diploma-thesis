#include "FuzzificationHierarchicalEntropy.h"
#include "DataSets.h"

using namespace Datasets;

namespace FuzzificationLibrary
{
	FuzzificationHierarchicalEntropy::FuzzificationHierarchicalEntropy(DataSets* dataToTransform) : FuzzificationEntropy(dataToTransform)
	{
	}

	double FuzzificationHierarchicalEntropy::getTreshold() const
	{
		return _treshold;
	}

	void FuzzificationHierarchicalEntropy::setTreshold(const double& value)
	{
		_treshold = value;
	}

	void FuzzificationHierarchicalEntropy::LastStepInFuzzification(int dimension, int interval)
	{
		auto MeanFE = getTotalEntropy()[dimension][interval] / getDataToTransform()->getDatasetSize();
	}

	bool FuzzificationHierarchicalEntropy::ConditionForStopingFuzzificationInDimension(int dimension, double totalEntropyI, double totalEntropyIPrevious)
	{
		setTreshold(-std::log(static_cast<double>(1) / getDataToTransform()->getOutputIntervals()) * (getIntervals()[dimension] - 1) * Theta);
		std::wcout << L"Treshold = " << getTreshold() << std::endl;
		return (totalEntropyI > totalEntropyIPrevious) || (std::abs(totalEntropyI) < 0.00000001) || (totalEntropyI < getTreshold());
	}
}
