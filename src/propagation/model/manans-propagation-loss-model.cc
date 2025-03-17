#include "manans-propagation-loss-model.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/log.h"
#include "ns3/mobility-model.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/propagation-cache.h"
#include "ns3/constant-position-mobility-model.h"
#include "ns3/log.h"
#include <cmath>


NS_LOG_COMPONENT_DEFINE("LogNormalShadowingDistancePropagationLossModel");
namespace ns3{
NS_OBJECT_ENSURE_REGISTERED(LogNormalShadowingDistancePropagationLossModel);

TypeId
LogNormalShadowingDistancePropagationLossModel::GetTypeId()
{
    static TypeId tid =
        TypeId("ns3::LogNormalShadowingDistancePropagationLossModel")
            .SetParent<PropagationLossModel>()
            .SetGroupName("Propagation")
            .AddConstructor<LogNormalShadowingDistancePropagationLossModel>()
            .AddAttribute("Exponent",
                          "The exponent of the Path Loss propagation model",
                          DoubleValue(3),
                          MakeDoubleAccessor(&LogNormalShadowingDistancePropagationLossModel::m_exponent),
                          MakeDoubleChecker<double>())
            .AddAttribute("ReferenceDistance",
                          "The distance at which the reference loss is calculated (m)",
                          DoubleValue(1.0),
                          MakeDoubleAccessor(&LogNormalShadowingDistancePropagationLossModel::m_referenceDistance),
                          MakeDoubleChecker<double>())
            .AddAttribute("ReferenceLoss",
                          "The reference loss at reference distance (dB). (Default is Friis at 1m "
                          "with 5.15 GHz)",
                          DoubleValue(46.6777),
                          MakeDoubleAccessor(&LogNormalShadowingDistancePropagationLossModel::m_referenceLoss),
                          MakeDoubleChecker<double>())
            .AddAttribute("ShadowingEffect",
                            "A random gaussian variable",
                            StringValue("ns3::NormalRandomVariable[Mean=0|Variance=2]"),
                            MakePointerAccessor(&LogNormalShadowingDistancePropagationLossModel::shadowing_effect),
                            MakePointerChecker<RandomVariableStream>());
                            
    return tid;
}

LogNormalShadowingDistancePropagationLossModel::LogNormalShadowingDistancePropagationLossModel()
{
}

void
LogNormalShadowingDistancePropagationLossModel::SetPathLossExponent(double n)
{
    m_exponent = n;
}

void
LogNormalShadowingDistancePropagationLossModel::SetReference(double referenceDistance, double referenceLoss)
{
    m_referenceDistance = referenceDistance;
    m_referenceLoss = referenceLoss;
}

double
LogNormalShadowingDistancePropagationLossModel::GetPathLossExponent() const
{
    return m_exponent;
}

double
LogNormalShadowingDistancePropagationLossModel::DoCalcRxPower(double txPowerDbm,
                                               Ptr<MobilityModel> a,
                                               Ptr<MobilityModel> b) const
{
    double distance = a->GetDistanceFrom(b);
    if (distance <= m_referenceDistance)
    {
        NS_LOG_DEBUG("distance=" << distance << "m, reference-attenuation=" << -m_referenceLoss
                                 << "dB, no further attenuation");
        return txPowerDbm - m_referenceLoss;
    }
    /**
     * The formula is:
     * rx = 10 * log (Pr0(tx)) - n * 10 * log (d/d0)
     *
     * Pr0: rx power at reference distance d0 (W)
     * d0: reference distance: 1.0 (m)
     * d: distance (m)
     * tx: tx power (dB)
     * rx: dB
     *
     * Which, in our case is:
     *
     * rx = rx0(tx) - 10 * n * log (d/d0)
     */
    double pathLossDb = 10 * m_exponent * std::log10(distance / m_referenceDistance);
    double rxc = -m_referenceLoss - pathLossDb + shadowing_effect->GetValue();
    NS_LOG_DEBUG("distance=" << distance << "m, reference-attenuation=" << -m_referenceLoss
                             << "dB, "
                             << "attenuation coefficient=" << rxc << "db");
    return txPowerDbm + rxc;
}

int64_t
LogNormalShadowingDistancePropagationLossModel::DoAssignStreams(int64_t stream)
{
    return 0;
}

}

// ------------------------------------------------------------------------- //