//#include "Fifo.h"
//#include <JuceHeader.h>
//
//template<typename T>
//void Fifo<T>::prepare(int numChannels, int numSamples)
//{
//    static_assert( std::is_same_v<T, juce::AudioBuffer<float>>,
//                  "prepare(numChannels, numSamples) should only be used when the Fifo is holding juce::AudioBuffer<float>");
//    for( auto& buffer : buffers)
//    {
//        buffer.setSize(numChannels,
//                       numSamples,
//                       false,   //clear everything?
//                       true,    //including the extra space?
//                       true);   //avoid reallocating if you can?
//        buffer.clear();
//    }
//}
//    
//template<typename T>
//void Fifo<T>::prepare(size_t numElements)
//{
//    static_assert( std::is_same_v<T, std::vector<float>>,
//                  "prepare(numElements) should only be used when the Fifo is holding std::vector<float>");
//    for( auto& buffer : buffers )
//    {
//        buffer.clear();
//        buffer.resize(numElements, 0);
//    }
//}
//
//template<typename T>
//bool Fifo<T>::push(const T& t)
//{
//    auto write = fifo.write(1);
//    if( write.blockSize1 > 0 )
//    {
//        buffers[write.startIndex1] = t;
//        return true;
//    }
//    
//    return false;
//}
//
//template<typename T>
//bool Fifo<T>::pull(T& t)
//{
//    auto read = fifo.read(1);
//    if( read.blockSize1 > 0 )
//    {
//        t = buffers[read.startIndex1];
//        return true;
//    }
//    
//    return false;
//}
//
//template<typename T>
//int Fifo<T>::getNumAvailableForReading() const
//{
//    return fifo.getNumReady();
//}
//
//template<typename BlockType>
//SingleChannelSampleFifo<BlockType>::SingleChannelSampleFifo(Channel ch) : channelToUse(ch)
//{
//    prepared.set(false);
//}
//
//template<typename BlockType>
//void SingleChannelSampleFifo<BlockType>::update(const BlockType& buffer)
//{
//    jassert(prepared.get());
//    jassert(buffer.getNumChannels() > channelToUse );
//    auto* channelPtr = buffer.getReadPointer(channelToUse);
//    
//    for( int i = 0; i < buffer.getNumSamples(); ++i )
//    {
//        pushNextSampleIntoFifo(channelPtr[i]);
//    }
//}
//
//template<typename BlockType>
//void SingleChannelSampleFifo<BlockType>::prepare(int bufferSize)
//{
//    prepared.set(false);
//    size.set(bufferSize);
//    
//    bufferToFill.setSize(1,             //channel
//                         bufferSize,    //num samples
//                         false,         //keepExistingContent
//                         true,          //clear extra space
//                         true);         //avoid reallocating
//    audioBufferFifo.prepare(1, bufferSize);
//    fifoIndex = 0;
//    prepared.set(true);
//}
////==============================================================================
//template<typename BlockType>
//int SingleChannelSampleFifo<BlockType>::getNumCompleteBuffersAvailable() const { return audioBufferFifo.getNumAvailableForReading(); }
//template<typename BlockType>
//bool SingleChannelSampleFifo<BlockType>::isPrepared() const { return prepared.get(); }
//template<typename BlockType>
//int SingleChannelSampleFifo<BlockType>::getSize() const { return size.get(); }
////==============================================================================
//template<typename BlockType>
//bool SingleChannelSampleFifo<BlockType>::getAudioBuffer(BlockType& buf) { return audioBufferFifo.pull(buf); }
//
//
//template<typename BlockType>
//void SingleChannelSampleFifo<BlockType>::pushNextSampleIntoFifo(float sample)
//{
//    if (fifoIndex == bufferToFill.getNumSamples())
//    {
//        auto ok = audioBufferFifo.push(bufferToFill);
//
//        juce::ignoreUnused(ok);
//        
//        fifoIndex = 0;
//    }
//    
//    bufferToFill.setSample(0, fifoIndex, sample);
//    ++fifoIndex;
//}
