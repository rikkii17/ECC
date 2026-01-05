#ifndef CLOCK_SYSTEM_H
    #define CLOCK_SYSTEM_H

    #include<chrono>

    class clock_system{
        public:
            std::time_t *now_time;
        
            std::time_t get_now_time(time_t &now_time);
            /*
                現在時刻を取得する。
                    引数：      なし
                    返り値：    現在時刻(time_t型)
            */


    };
#endif