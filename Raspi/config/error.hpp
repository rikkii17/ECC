#ifndef ERROR_HPP
    #define ERROR_HPP
    
    #include<iostream>
    //CLIÇ…ÉGÉâÅ[ï∂Çï\é¶

    class error_number{
    public:
        class initialization{
        public:
            static constexpr int OK = 0;

            static constexpr int ALARM_FILE_IS_NOT_FOUND = -1;

            static constexpr int OPT_DIR_IS_NOT_EXIST = -1;
        };
    };

    class error_process{
    public:
       static bool initialization_error(int error_flag);
    };


#endif