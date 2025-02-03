#include "PluginEditor.h"

PluginEditor::PluginEditor (PluginProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
    //presetPanel (p.getPresetManager())
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible (inspectButton);
    //addAndMakeVisible (presetPanel);

    // this chunk of code instantiates and opens the melatonin inspector
    inspectButton.onClick = [&] {
        if (!inspector)
        {
            inspector = std::make_unique<melatonin::Inspector> (*this);
            inspector->onClose = [this]() { inspector.reset(); };
        }

        inspector->setVisible (true);
    };

    constrainer.setFixedAspectRatio (16.0f / 9.0f);
    setConstrainer (&constrainer);

    // Allow the editor to be resizable
    setResizable (true, true);
    constrainer.setMinimumSize (720, 405);
    constrainer.setMaximumSize (960, 540);

    setSize (720, 405);
}

PluginEditor::~PluginEditor()
{
}

void PluginEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    g.setColour (juce::Colours::white);
    g.setFont (16.0f);
}

void PluginEditor::resized()
{

    //presetPanel.setBounds (getLocalBounds().removeFromTop (proportionOfHeight (0.1f)));

    // layout the positions of your child components here
    auto area = getLocalBounds();
    area.removeFromBottom(50);
    inspectButton.setBounds (getLocalBounds().withSizeKeepingCentre(100, 50));
}
