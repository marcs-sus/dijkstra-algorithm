#pragma once

#include "edge.h"

// Enums for pavement condition and type
enum class PavementCondition
{
    EXCELLENT,
    GOOD,
    BAD
};

enum class PavementType
{
    ASPHALT,
    PAVEMENT,
    DIRT
};

// Road class representing a custom edge for specific graphs
class Road : public Edge
{
public:
    Road(Node *src, Node *dst, double distance, PavementCondition condition, PavementType type);

    // Override getWeight to calculate based on distance, condition, and type
    double getWeight() const override;

    // Getters for road properties
    double getDistance() const { return distanceKm; }
    PavementCondition getCondition() const { return condition; }
    PavementType getType() const { return type; }

private:
    double distanceKm;
    PavementCondition condition;
    PavementType type;

    // Helpers to get factors based on enums
    double getConditionFactor() const;
    double getTypeFactor() const;
};
