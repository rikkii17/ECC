//config/softconfig.hpp
//hardwareの基本設定に関するヘッダー
#ifndef  SOFTCONFIG_HPP
    #define SOFTCONFIG_HPP

    #include<atomic>

    class software_config{
        public:
            class controller{
                private:
                    static inline std::atomic<bool> system_is_running{true};
                
                public:
                    static std::atomic<bool>& get_system_is_running();
                    /*
                        system_is_running変数を安全に取得する目的
                            引数：       void               
                            返り値 ：   std::atomic<bool>&  system_is_runningのパス
                    */
                    static void put_system_is_running(bool system_flag);
                    /*
                        system_is_runningの値をsystem_flagの値で上書きする
                        第1引数：   bool    system_flag      上書きする値
                        返り値：    void   
        
                    */

            };
    };
#endif