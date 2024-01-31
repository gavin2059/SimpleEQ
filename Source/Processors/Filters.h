/*
  ==============================================================================

    Filters.h
    Created: 31 Jan 2024 3:04:50pm
    Author:  Gavin Zhang

  ==============================================================================
*/

#pragma once
#include "ChainSettings.h"
#include <JuceHeader.h>

using Coefficients = Filter::CoefficientsPtr;
void updateCoefficients(Coefficients& old, const Coefficients& replacements);

template<int Index, typename ChainType, typename CoefficientType>
void update(ChainType& chain, const CoefficientType& coefficients)
{
    updateCoefficients(chain.template get<Index>().coefficients, coefficients[Index]);
    chain.template setBypassed<Index>(false);
}

template<typename ChainType, typename CoefficientType>
void updateCutFilter(ChainType& leftLowCut, const CoefficientType& cutCoefficients, const Slope& lowCutSlope)
{
    leftLowCut.template setBypassed<0>(true);
    leftLowCut.template setBypassed<1>(true);
    leftLowCut.template setBypassed<2>(true);
    leftLowCut.template setBypassed<3 >(true);
    
    switch( lowCutSlope )
    {
        case Slope_48:
            update<3>(leftLowCut, cutCoefficients);
        case Slope_36:
            update<2>(leftLowCut, cutCoefficients);
        case Slope_24:
            update<1>(leftLowCut, cutCoefficients);
        case Slope_12:
            update<0>(leftLowCut, cutCoefficients);
            break;
    }
}

inline auto makeLowCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
   return juce::dsp::FilterDesign<float>::
    designIIRHighpassHighOrderButterworthMethod(
                                                chainSettings.lowCutFreq,
                                                sampleRate,
                                                (chainSettings.lowCutSlope + 1) * 2);
}

inline auto makeHighCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
   return  juce::dsp::FilterDesign<float>::
    designIIRLowpassHighOrderButterworthMethod(
                                               chainSettings.highCutFreq,
                                               sampleRate,
                                               (chainSettings.highCutSlope + 1) * 2);
}

Coefficients makePeakFilter(const ChainSettings& chainSettings, double sampleRate);
