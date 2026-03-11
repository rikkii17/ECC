#ifndef CLOCK_SYSTEM_HPP
    #define CLOCK_SYSTEM_HPP

    #include<chrono>
    //時刻を取得するためのライブラリ
    #include<atomic>
    //now_time_tをスレッド間で安全に利用できるように規定
    #include<filesystem>
    //alarmのファイルを扱うために必須

    #include"softconfig.hpp"
    #include"clock_system_config.hpp"


    class clock_system{
    /*時計関係の情報を載せるクラス*/
        private:
            static inline std::atomic<std::time_t> now_time_t{};

        public:
            static void set_now_time();
            /*
                std::chronoによって現在時刻を取得する。
                mainのsystem_clock_threadによってマルチスレッド処理を常に行うことでstd::tm型として常に時間を把握できるようにする。
                
                    引数：      void
                    返り値：    void
            */

            static std::tm get_now_time();
            /*
                現在の時刻を取得する
                    引数:       void
                    返り値:     現在時刻（std::tm)
            */

    };

    class alarm_system{
        //アラームに関係する情報を扱うクラス
        public:
            static void check_alarm();
            /*
                アラームに関する処理を行うスレッド
                    引数:       void
                    返り値:     void
            */
            static void set_alarm_list(int hour,int minuts,alarm_system_config::week_config week_data);
            /*
                アラームリストに新しい時間を設定する
                    第1引数:    アラームの時間（int)
                    第2引数:    アラームの分（int)
                    第3引数:    アラームの曜日の設定（alarm_system_config::week_config)
                    返り値:     void
            */
           static void get_alarm_list_from_csv();
           /*
                CSVファイルからアラームリストを取得する
                    引数:       void
                    返り値:     void
           */
            static void save_alarm_list_to_csv();
            /*
                アラームリストをCSVファイルに保存する
                    引数:       void
                    返り値:     void
            */

            static int select_alarm_list();
            /*
                任意のアラームリストを選択させるための機能をまとめた関数
                引数:   void
                返り値: リストの何番目を選択したか（0～）（int)
            */

            static void set_new_alarm();
            /*
                アラームリストに新しい時間を設定する
                    引数:       void
                    返り値:     void
            */
            static void edit_alarm();
            /*
                アラームリストのON/OFFを設定する
                引数:   vod
                返り値: void
            */

    };
#endif