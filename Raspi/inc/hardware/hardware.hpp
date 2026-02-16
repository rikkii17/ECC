#ifndef HARDWARE_HPP
    #define HARDWARE_HPP
    #include<string>
    
    class hardware{
    public:
        class pwm{
            public:
            std::string base_path;

            pwm(int chip,int channnel);
        };

        static void hardware_system();
    };

#endif