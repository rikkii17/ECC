//config/hardconfig.hpp
//hardwareの基本設定に関するヘッダー
#ifndef  HARDCONFIG_HPP
    #define HARDCONFIG_HPP

    class hardwere_config{
        public:
            class controller{
                public:
                    bool end_system;
                    /*
                        終了の操作に関するフラグ
                        true::市システム全体の終了
                        false::システム全体の継続
                    */
            };
    };
#endif