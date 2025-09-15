#include "road.h"

const std::map<PavementCondition, double> Road::conditionFactors = {
    {PavementCondition::OTIMO, 1.00},
    {PavementCondition::BOM, 1.25},
    {PavementCondition::RUIM, 1.70}};

const std::map<PavementType, double> Road::typeFactors = {
    {PavementType::ASFALTO, 1.00},
    {PavementType::CALCAMENTO, 1.30},
    {PavementType::CHAO, 1.80}};

Road::Road(Node &rSrc, Node &rDst, double distance, PavementCondition condition, PavementType type)
    : Edge(rSrc, rDst), distanceKm(distance), condition(condition), type(type)
{
}

double Road::getWeight() const
{
    double conditionFactor = conditionFactors.at(condition);
    double typeFactor = typeFactors.at(type);

    return distanceKm * conditionFactor * typeFactor;
}