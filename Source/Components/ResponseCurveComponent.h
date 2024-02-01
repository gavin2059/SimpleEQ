/*
  ==============================================================================

    ResponseCurveComponent.h
    Created: 30 Jan 2024 10:34:00pm
    Author:  Gavin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginEditor.h"
#include "PathProducer.h"

struct ResponseCurveComponent: juce::Component,
juce::AudioProcessorParameter::Listener,
juce::Timer
{
    ResponseCurveComponent(SimpleEQAudioProcessor&);
    ~ResponseCurveComponent();
    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {} ;
    void timerCallback() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    SimpleEQAudioProcessor& audioProcessor;
    juce::Atomic<bool> parametersChanged { false };
    MonoChain monoChain;
    void updateChain();
    juce::Image background;
    juce::Rectangle<int> getRenderArea();
    juce::Rectangle<int> getAnalysisArea();
    PathProducer leftPathProducer, rightPathProducer;
};
