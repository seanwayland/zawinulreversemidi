/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Zawinulreversemidi2AudioProcessor::Zawinulreversemidi2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Zawinulreversemidi2AudioProcessor::~Zawinulreversemidi2AudioProcessor()
{
}

//==============================================================================
const String Zawinulreversemidi2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Zawinulreversemidi2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Zawinulreversemidi2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Zawinulreversemidi2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Zawinulreversemidi2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Zawinulreversemidi2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Zawinulreversemidi2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Zawinulreversemidi2AudioProcessor::setCurrentProgram (int index)
{
}

const String Zawinulreversemidi2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Zawinulreversemidi2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Zawinulreversemidi2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Zawinulreversemidi2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Zawinulreversemidi2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Zawinulreversemidi2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    
    MidiMessage m;
    MidiMessage n;
    buffer.clear();
    
    
    
    MidiBuffer processedMidi;
    int time;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
        {

            
            int note = m.getNoteNumber();
            if (note<60)
            {
                n = MidiMessage::noteOn(m.getChannel(), 60 + ( 60 - note ) , m.getVelocity());
                processedMidi.addEvent(n, time);
                
            }
            else
            {
                n = MidiMessage::noteOn(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
                processedMidi.addEvent(n, time);
                
            }
            
       }
       else if (m.isNoteOff()) {
            
            
            int note = m.getNoteNumber();
            if (note<60)
            {
                n = MidiMessage::noteOff(m.getChannel(), 60 + ( 60 - note ), m.getVelocity());
                processedMidi.addEvent(n, time);
                
            }
            else
            {
                n = MidiMessage::noteOff(m.getChannel(), 60 - ( note - 60) , m.getVelocity());
                processedMidi.addEvent(n, time);
                
            }
            
 
        }
        
       else if (m.isAftertouch())
        {
        }
        else if (m.isPitchWheel())
        {
        }
        
    }
    
    midiMessages.swapWith  (processedMidi) ;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
   // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            {
      //  buffer.clear (i, 0, buffer.getNumSamples());
            }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    
   // for (int channel = 0; channel < totalNumInputChannels; ++channel)
   // {
      //  auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
   // }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Zawinulreversemidi2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Zawinulreversemidi2AudioProcessor::createEditor()
{
    return new Zawinulreversemidi2AudioProcessorEditor (*this);
}

//==============================================================================
void Zawinulreversemidi2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Zawinulreversemidi2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Zawinulreversemidi2AudioProcessor();
}
