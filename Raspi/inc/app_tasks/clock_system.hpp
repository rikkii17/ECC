#ifndef CLOCK_SYSTEM_HPP
    #define CLOCK_SYSTEM_HPP

    #include<chrono>

    class clock_system{
    /*時計関係の情報を載せるクラス*/
        public:
            std::tm *now_time;
            /*
            今の時間を格納する。std::tm型に変換した時間を入力する。
            入力はget_now_time関数によって行われている
            */

            void get_now_time(std::tm *now_time);
            /*
                std::chronoによって現在時刻を取得する。
                mainのsystem_clock_threadによってマルチスレッド処理を常に行うことでstd::tm型として常に時間を把握できるようにする。
                
                    引数：      現在時刻を格納する変数ポインタ(std::tm型)
                    返り値：    void
            */


    };
#endif