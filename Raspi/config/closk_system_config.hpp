#ifndef CLOCK_SYSTEM_CONFIG_HPP
    #define CLOCK_SYSTEM_CONFIG_HPP

    class alarm_config{
        class WEEK_DAY{
            static constexpr char SUNDAY = 0x02;
            static constexpr char MONDAY = 0x04;
            static constexpr char TUESDAY = 0x08;
            static constexpr char WEDNESDAY = 0x10;
            static constexpr char THURSDAY = 0x20;
            static constexpr char FRIDAY = 0x40;
            static constexpr char SATURDAY = 0x80;
        };
        //各曜日を定数として扱う（char型1byteで扱えるようにする。）


        class alarm_list{
            int alarm_hour;
            int alarm_minut;
            char week_day;
            /*

            */
            //アラーム時間の情報を入力する変数
            alarm_config::alarm_list *next;
            //次のアラームリストへのポインタ
        };
        /*

        */
    };
#endif