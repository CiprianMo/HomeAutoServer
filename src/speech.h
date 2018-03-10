#ifndef SPEECH_H
#define SPEECH_H
#include<iostream>
#include<string>
#include<pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>

class Speech
{
        ps_decoder_t *ps;
        ad_rec_t *ad;
        cmd_ln_t *config;
        char const *hyp;
        int16 buf[4096];
        int k;
        uint8 utt_started, in_speech;
        
        public:
        Speech(const std::string& modelDir);
        std::string contin_recog();
        
};

#endif
