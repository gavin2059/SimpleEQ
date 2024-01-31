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

/**
    @param old Reference to the old coefficients to replace
    @param replacements Reference to the new coefficients
 */
void updateCoefficients(Coefficients& old, const Coefficients& replacements);

/**
    @brief Updates a chain with new coefficients
    @param chain The chain to update
    @param coefficients The coefficients to use
 */
template<int Index, typename ChainType, typename CoefficientType>
void update(ChainType& chain, const CoefficientType& coefficients)
{
    updateCoefficients(chain.template get<Index>().coefficients, coefficients[Index]);
    chain.template setBypassed<Index>(false);
}

/**
    @brief updates a cut filter
    @param leftLowCut reference to the cut filter chain to update
    @param cutCoefficients reference to the coefficients to use
    @param lowCutSlope reference to slope to use
 */
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

/**
    @return low cut filter
 */
inline auto makeLowCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
   return juce::dsp::FilterDesign<float>::
    designIIRHighpassHighOrderButterworthMethod(
                                                chainSettings.lowCutFreq,
                                                sampleRate,
                                                (chainSettings.lowCutSlope + 1) * 2);
}

/**
    @return high cut filter
 */
inline auto makeHighCutFilter(const ChainSettings& chainSettings, double sampleRate)
{
   return  juce::dsp::FilterDesign<float>::
    designIIRLowpassHighOrderButterworthMethod(
                                               chainSettings.highCutFreq,
                                               sampleRate,
                                               (chainSettings.highCutSlope + 1) * 2);
}

/**
    @return peak filter
 */
Coefficients makePeakFilter(const ChainSettings& chainSettings, double sampleRate);
