#ifndef CLOCK_SYSTEM_CONFIG_HPP
    #define CLOCK_SYSTEM_CONFIG_HPP
    
    #include<atomic>
    //安全に変数を利用すること


    class alarm_system_config{
    public:

        typedef struct week_config{
            unsigned char is_active : 1;
            unsigned char sunday    : 1;
            unsigned char monday    : 1;
            unsigned char tuesday   : 1;
            unsigned char wednesday : 1;
            unsigned char thursday  : 1;
            unsigned char friday    : 1;
            unsigned char saturday  : 1;
        } week_config;
        


        class alarm_list{
        public:
            int alarm_hour;
            int alarm_minute;
            //std::tm型がintなので同様にintに
            alarm_system_config::week_config week_data;

            //アラーム時間の情報を入力する変数
            alarm_system_config::alarm_list *next;
            //次のアラームリストへのポインタ
        };

        static inline alarm_list *alarm_list_head = nullptr;
        //アラームのリストの先頭pointer

        static inline std::atomic<bool> ararm_is_ringing{false};
        //アラームが起動しているかのフラッグ

        
    };
#endif