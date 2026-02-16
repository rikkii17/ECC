#ifndef HARDWARE_CONFIG_HPP
    #define HARDWARE_CONFIG_HPP

    #include<iostream>

    class hardware_config{
    public:
        class pin_number{
        public:
            
    static inline const std::string gpio_input = "12";
        };

    static inline const std::string base_path = "/sys/class/gpio/";
    };

#endif