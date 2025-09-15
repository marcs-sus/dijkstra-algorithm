#pragma once

#include "edge.h"

#include <map>

enum class PavementCondition
{
    OTIMO,
    BOM,
    RUIM
};

enum class PavementType
{
    ASFALTO,
    CALCAMENTO,
    CHAO
};

class Road : public Edge
{
public:
    Road(Node &rSrc, Node &rDst, double distance, PavementCondition condition, PavementType type);

    double getWeight() const override;

private:
    double distanceKm;
    PavementCondition condition;
    PavementType type;

    static const std::map<PavementCondition, double> conditionFactors;
    static const std::map<PavementType, double> typeFactors;
};