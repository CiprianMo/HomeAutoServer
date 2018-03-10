#include"speech.h"
#include<thread>
#include<chrono>

Speech::Speech(const std::string& ModelDir)
{
        config =cmd_ln_init(NULL, ps_args(), TRUE,
                        "-hmm","/usr/local/share/pocketsphinx/model/en-us/en-us",
                   //     "-lm","4436.lm",
                        "-kws","keywords.kws",
                        "-dict","4436.dic",
                        "-logfn","/dev/null",
                        NULL);
        ps = ps_init(config);

        if(( ad = ad_open_dev("sysdefault",(int) cmd_ln_float32_r(config,"-samprate")))==NULL)
            std::cerr<<"Failed to open audio device "<<std::endl;
}

std::string Speech::contin_recog()
{ 
	if(ad_start_rec(ad) < 0)
		std::cerr<<"Faild to start recording "<<std::endl;
    if(ps_start_utt(ps) < 0)
        std::cerr<<"Failed to start utterance "<<std::endl;  
    utt_started = FALSE;

    std::cout<<"Ready..\n";

while(1)
{ 
    if((k=ad_read(ad,buf,4096))<0)
            std::cerr<<"Failed to read audio "<<std::endl;

    ps_process_raw(ps, buf,k ,FALSE, FALSE);

    in_speech = ps_get_in_speech(ps);

    if(in_speech && !utt_started)
    {
            std::cout<<"Listening ...\n";
            utt_started = TRUE;
    }

    if(!in_speech && utt_started)
    {
            ps_end_utt(ps);
            ad_stop_rec(ad);
            if(ps_get_hyp(ps,NULL))
            {
               std::string data(ps_get_hyp(ps,NULL)); 

                std::cout <<"Sgins is "<<data<<std::endl;
               return data;
            }                        
            return "";
            break;
    }
}
}

