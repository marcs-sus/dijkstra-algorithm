#include "road.h"

Road::Road(Node *src, Node *dst, double distance, PavementCondition condition, PavementType type)
    : Edge(src, dst, 0.0), distanceKm(distance), condition(condition), type(type)
{
    // Calculate and set the weight after initialization
    weight = distanceKm * getConditionFactor() * getTypeFactor();
}

double Road::getWeight() const
{
    double conditionFactor = getConditionFactor();
    double typeFactor = getTypeFactor();

    // Calculate weight as distance * pavement condition * pavement type
    return distanceKm * conditionFactor * typeFactor;
}

double Road::getConditionFactor() const
{
    switch (condition)
    {
    case PavementCondition::EXCELLENT:
        return 1.00;
    case PavementCondition::GOOD:
        return 1.25;
    case PavementCondition::BAD:
        return 1.70;
    default:
        // Default to EXCELLENT if unknown
        return 1.00;
    }
}

double Road::getTypeFactor() const
{
    switch (type)
    {
    case PavementType::ASPHALT:
        return 1.00;
    case PavementType::PAVEMENT:
        return 1.30;
    case PavementType::DIRT:
        return 1.80;
    default:
        // Default to ASPHALT if unknown
        return 1.00;
    }
}
