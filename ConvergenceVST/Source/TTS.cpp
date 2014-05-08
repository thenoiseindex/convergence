/*
 ==============================================================================
 
 TTS.cpp
 Created: 3 May 2013 11:42:30pm
 Author:  Jordan Hochenbaum & Owen Vallis
 
 ==============================================================================
 */

#include "TTS.h"

static bool initialized = false;

extern "C"{
    cst_val *flite_set_voice_list(void);
    cst_voice* register_cmu_us_kal16();
    cst_voice* register_cmu_us_awb();
    cst_voice* register_cmu_us_rms();
    cst_voice* register_cmu_us_slt();
}

TTS::TTS() : Thread("TTS"), bufferReady(false), ttsBuffer(1, 512), upsampledTTSBuffer(1,512), samplesProcessed(0), nextTweetTimeMax(10) {
	voice = NULL;
    
    startThread();
    //get timer going
    int randomTime = Random::getSystemRandom().nextInt(nextTweetTimeMax) * 1000;
    startTimer(randomTime);
}

TTS::~TTS() {
    stopThread(2000);
}


void TTS::initialize(){
	if(!initialized){
		flite_init();
		initialized = true;
	}
	/*flite_voice_list = flite_set_voice_list();
     voice = flite_voice_select("alice.wav");
     */
	//flite_voice_list = flite_set_voice_list();
	//voice = flite_voice_select("charles");
    voice=register_cmu_us_awb();
	if(!voice) DBG("couldn't initialize voices");
}

void TTS::run(){
    while (!threadShouldExit()) {
        
        wait(-1);

        cst_wave* wave = flite_text_to_wave(textToConvert.toRawUTF8(),voice);
        double srate;
        
        if(wave){
            srate = wave->sample_rate;
            ttsBuffer.setSize(1, wave->num_samples);
            ttsBuffer.clear();
            
            float* ttsChannelData = ttsBuffer.getWritePointer (0);
            short* waveData = wave->samples;
            
            for (int i = 0; i < wave->num_samples; ++i) {
                
                *ttsChannelData = (*waveData)/65536.0;
                waveData++;
                ttsChannelData++;
            }
            
            ttsChannelData = ttsChannelData - wave->num_samples;
            
            upsampledTTSBuffer.setSize(1, roundToInt(wave->num_samples*(44100.0/srate)));
            upsampledTTSBuffer.clear();
            
            const double localRatio = srate/44100.0;
            
            double nextSample = 0.0;
            
            float* upsampledttsChannelData = upsampledTTSBuffer.getWritePointer (0);
            
            for (int s = 0; s < upsampledTTSBuffer.getNumSamples(); ++s)
            {
                int lower = (int) nextSample;
                int upper = lower + 1;
                if (upper == ttsBuffer.getNumSamples())
                    upper = 0;
                double difference = nextSample - lower;
                
                *upsampledttsChannelData = (*(ttsChannelData+upper) * difference) + (*(ttsChannelData+lower) * (double) (1.0 - difference));
                upsampledttsChannelData++;
                
                nextSample += localRatio;
            }
            
            for (int i = 1; i < upsampledTTSBuffer.getNumChannels(); ++i)
            {
                upsampledTTSBuffer.clear (i, 0, upsampledTTSBuffer.getNumSamples());
            }
            
            delete[] wave->samples;
            delete wave;
            
            upsampledTTSBuffer.applyGainRamp(0, 200, 0.0, 1.0);
            upsampledTTSBuffer.applyGainRamp(upsampledTTSBuffer.getNumSamples()-200, 200, 1.0, 0.0);
            
            bufferReady = true;
            samplesProcessed = 0;
            
        }else{
            DBG("couldn't generate wave");
        }
    }
}

void TTS::convertToAudio(String text, int samplingRate){
    textToConvert = text;
    notify();
}

void TTS::addText(String text){
    convertToAudio(text,44100);
}

void TTS::setNextTweetTimeMax(int interval){
    nextTweetTimeMax = interval;
}

void TTS::setVoice(int voiceToSet){
    switch (voiceToSet) {
        case 0:
            voice=register_cmu_us_awb(); break;
            break;
            
        case 1:
            voice=register_cmu_us_rms(); break;
            
        case 2:
            voice=register_cmu_us_slt(); break;
            
        case 3:
            voice=register_cmu_us_kal16(); break;
            
        default:
            voice=register_cmu_us_rms(); break;
    }
}

void TTS::getNextAudioBlock ( AudioSampleBuffer &bufferToFill){
   
    float* blockToFill =  bufferToFill.getWritePointer(outputChannel);

    if (bufferReady) {
        float* ttsChannelData = upsampledTTSBuffer.getWritePointer(0, samplesProcessed);
        //float* ttsChannelData = upsampledTTSBuffer.getSampleData(0, samplesProcessed);
        
        if ((samplesProcessed + bufferToFill.getNumSamples()) < upsampledTTSBuffer.getNumSamples()) {
            for (int i = 0; i < bufferToFill.getNumSamples(); ++i) {
                *blockToFill++ = *ttsChannelData++;
                samplesProcessed++;
            }
            
        } else {
            for (int i = 0; i < upsampledTTSBuffer.getNumSamples() - samplesProcessed; ++i) {
                *blockToFill++ = *ttsChannelData++;
                samplesProcessed++;
            }
            
            //fill any leftover with zero's
            for (int i=samplesProcessed; i<bufferToFill.getNumSamples(); ++i) {
                *blockToFill++ = 0;
            }
            
            bufferReady = false;
            
            int randomTime = Random::getSystemRandom().nextInt(nextTweetTimeMax) * 1000;
            startTimer(randomTime);
        }
    } else {
        for (int i=0; i<bufferToFill.getNumSamples(); ++i) {
            *blockToFill++ = 0;
        }
    }
}

void TTS::timerCallback(){
    //DBG("Timer...");
    stopTimer();
    sendChangeMessage();
}