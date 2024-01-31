/*
  ==============================================================================

    Filters.cpp
    Created: 31 Jan 2024 3:04:50pm
    Author:  Gavin Zhang

  ==============================================================================
*/

#include "Filters.h"

Coefficients makePeakFilter(const ChainSettings& chainSettings, double sampleRate)
{
    
    return juce::dsp::IIR::Coefficients<float>::makePeakFilter(
                                                                                sampleRate,
                                                                                chainSettings.peakFreq,
                                                                                chainSettings.peakQuality,
                                                                                juce::Decibels::decibelsToGain(chainSettings.peakGainInDecibels));
}

void updateCoefficients(Coefficients &old, const Coefficients &replacements)
{
    *old = *replacements;
}
