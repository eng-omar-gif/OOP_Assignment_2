#include "PlayerGui.h"

/*
 * PlayerGUI.cpp
 * -----------------------------
 * Implements the visual part of the player (UI behavior).
 */

PlayerGui::PlayerGui()
{
    formatManager.registerBasicFormats();

    // Buttons
    for (auto* btn : { &loadButton, &playButton, &stopButton,
                       &goStartButton, &goEndButton })
    {
        addAndMakeVisible(btn);
        btn->addListener(this);
    }

    // Volume
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Metadata label (Made by Adham Tamer)
    addAndMakeVisible(metadataLabel);
    metadataLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    metadataLabel.setJustificationType(juce::Justification::centredLeft);
}

PlayerGui::~PlayerGui()
{
    transportSource.releaseResources();
}

void PlayerGui::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(16.0f);
    g.drawText("Simple Player", getLocalBounds(), juce::Justification::centredTop);
}

void PlayerGui::resized()
{
    int margin = 20;
    int y = 40;
    int buttonWidth = 80;
    int buttonHeight = 35;

    loadButton.setBounds(margin, y, buttonWidth, buttonHeight);
    playButton.setBounds(margin + 100, y, buttonWidth, buttonHeight);
    stopButton.setBounds(margin + 200, y, buttonWidth, buttonHeight);
    volumeSlider.setBounds(margin, y + 60, getWidth() - 2 * margin, 30);

    // ===== Made by Adham Tamer =====

    goStartButton.setBounds(margin + 420, y, buttonWidth + 10, buttonHeight);
    goEndButton.setBounds(margin + 520, y, buttonWidth + 10, buttonHeight);
    metadataLabel.setBounds(margin, y + 120, getWidth() - 2 * margin, 80);
    // ================================
}

void PlayerGui::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGui::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() != nullptr)
        transportSource.getNextAudioBlock(bufferToFill);
    else
        bufferToFill.clearActiveBufferRegion();
}

void PlayerGui::releaseResources()
{
    transportSource.releaseResources();
}

void PlayerGui::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto file = fc.getResult();
                if (file != juce::File{})
                {
                    auto* reader = formatManager.createReaderFor(file);
                    if (reader != nullptr)
                    {
                        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
                        readerSource.reset(newSource.release());

                        juce::String title = reader->metadataValues.getValue("title", file.getFileNameWithoutExtension());
                        juce::String artist = reader->metadataValues.getValue("artist", "Unknown Title");

                        double duration = reader->lengthInSamples / reader->sampleRate;

                        metadataLabel.setText("Title: " + title + "\nArtist: " + artist + "\nDuration: " + juce::String(duration, 2) + " sec", juce::dontSendNotification);
                    }
                }
            });
    }
    if (button == &stopButton)
    {
        transportSource.stop();
        transportSource.setPosition(0.0);
    }
    // ===== Added by Adham Tamer =====
    if (button == &playButton)
    {
        if (transportSource.isPlaying())
        {

            transportSource.stop();
        }
        else {
            transportSource.start();
            playButton.setButtonText("Pause");
        }
    }






    if (button == &goStartButton)
        transportSource.setPosition(0.0);

    if (button == &goEndButton)
        transportSource.setPosition(transportSource.getLengthInSeconds());
    // ================================
}

void PlayerGui::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        transportSource.setGain((float)slider->getValue());
}
