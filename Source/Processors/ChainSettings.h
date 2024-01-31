/*
  ==============================================================================

    ChainSettings.h
    Created: 31 Jan 2024 3:04:38pm
    Author:  Gavin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


enum Slope
{
  Slope_12, Slope_24, Slope_36, Slope_48
};

struct ChainSettings
{
    float peakFreq {0}, peakGainInDecibels{0}, peakQuality {1.f};
    float lowCutFreq {0}, highCutFreq {0};
    Slope lowCutSlope {Slope::Slope_12}, highCutSlope {Slope::Slope_12};
    bool lowCutBypassed { false }, peakBypassed { false }, highCutBypassed { false };
};

ChainSettings getChainSettings(juce::AudioProcessorValueTreeState& apvts);

using Filter = juce::dsp::IIR::Filter<float>;
using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;
enum ChainPositions
{
    LowCut,
    Peak,
    HighCut
};
