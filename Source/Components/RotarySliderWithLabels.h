/*
  ==============================================================================

    RotarySliderWithLabels.h
    Created: 30 Jan 2024 10:21:25pm
    Author:  Gavin Zhang

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


struct LookAndFeel : juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics&,
                           int x, int y,
                           int width, int height,
                           float sliderPosProportiona,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider&) override;
};

struct RotarySliderWithLabels  : juce::Slider
{
    RotarySliderWithLabels(juce::RangedAudioParameter& rap, const juce::String &unitSuffix)  :
    juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                 juce::Slider::TextEntryBoxPosition::NoTextBox),
    param(&rap),
    suffix(unitSuffix)
    {
        setLookAndFeel(&lnf);
    }
    
    ~RotarySliderWithLabels()
    {
        setLookAndFeel(nullptr);
    }
    
    struct LabelPos
    {
        float pos;
        juce::String label;
    };
    
    juce::Array<LabelPos> labels;
    
    
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const {return 14;}
    juce::String getDisplayString() const;
private:
    LookAndFeel lnf;
    juce::RangedAudioParameter* param;
    juce::String suffix;
};
