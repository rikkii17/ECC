//config/hardconfig.hpp
//hardwareの基本設定に関するヘッダー
#ifndef  HARDCONFIG_HPP
    #define HARDCONFIG_HPP

    #include<atomic>

    class hardwere_config{
        public:
            class controller{
                private:
                static inline std::atomic<bool> system_is_running{true};
                
                public:
                    std::atomic<bool>& get_esystem_is_running();

            };
    };
#endif