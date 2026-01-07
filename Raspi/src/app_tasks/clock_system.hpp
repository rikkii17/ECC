#ifndef CLOCK_SYSTEM_H
    #define CLOCK_SYSTEM_H

    #include<chrono>

    class clock_system{
    /*時計関係の情報を載せるクラス*/
        public:
            std::time_t *now_time;
            /*
            今の時間を格納する。time_t型に変換した時間を入力する。
            入力はget_now_time関数によって行われている
            */
        
            static::time_t get_now_time(time_t &now_time);
            /*
                現在時刻を取得する。
                    引数：      なし
                    返り値：    現在時刻(time_t型)
            */


    };
#endif