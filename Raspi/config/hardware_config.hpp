#ifndef HARDWARE_CONFIG_HPP
    #define HARDWARE_CONFIG_HPP

    #include<iostream>

    class hardware_config{
    public:
        class pin_number{
        public:
            
    static inline const std::string gpio_output = "12";
    //outputピンを設定する
        };

    static inline const std::string base_path = "/sys/class/gpio/";
    //gpioにハードからアクセスするためのpath
    };

#endif