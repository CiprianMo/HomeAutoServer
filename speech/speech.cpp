#include<iostream>
#include<string>
#include<pocketsphinx.h>
#include<sphinxbase/ad.h>
#include<sphinxbase/err.h>

using namespace std;

ps_decoder_t *ps;  //pocket decoder struct
cmd_ln_t *config;  //config struct

ad_rec_t *ad;      //create audio recording struct - for use with ALSA function

int16 adbuf[4096];
uint8 utt_started, in_speech; //flags for tracking active speech -has started ? is speech currently happening?

int32 k; // holds the number of frame in the audio buffer
char const *hyp; //pointer to hypothesis best guess at the decoded result

string recognized_from_mic()
{
        ad_start_rec(ad); //start redording
        ps_start_utt(ps); //mark the start of the utterance
        utt_started = FALSE;

        while(1)
        {
                k=ad_read(ad, adbuf, 4096); //send audio buffer to pocket
                ps_process_raw(ps, adbuf, k,FALSE,FALSE);
                in_speech = ps_get_in_speech(ps);

                if(in_speech && !utt_started)
                {
                        utt_started = TRUE;
                }

                if(!in_speech && utt_started)
                {
                        ps_end_utt(ps);
                        ad_stop_rec(ad);
                        hyp = ps_get_hyp(ps, NULL);

                        return hyp;
                        break;
                }
        }
}

int main(int argc, char *argv[])
{
        config = cmd_ln_init(NULL, ps_args(), TRUE,
                        "-hmm","usr/local/share/pocketsphinx/model/en-us/en-us",
                        "-lm","4436.lm",
                        "-dict","4436.dic",
                        "-logfn","/dev/null",
                        NULL);
        ps = ps_init(config);
        ad = ad_open_dev("sysdefault",(int) cmd_ln_float32_r(config,"-samprate"));
        while(1)
        {
                string decoded_speech = recognized_from_mic();
                cout << "Decoded Speech: "<<decoded_speech <<"\n"<<endl;
        }

        ad_close(ad);
        return 0;
}

