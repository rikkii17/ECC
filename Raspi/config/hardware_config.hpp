#ifndef HARDWARE_CONFIG_HPP
    #define HARDWARE_CONFIG_HPP

    #include<iostream>

    class hardware_config{
    public:
        static constexpr int chip = 0;
        static constexpr int channel = 0;

        //SPI
        static inline const std::string spi_device = "/dev/spidev0.0";
        static constexpr uint32_t spi_speed = 1000000;

    };


#endif