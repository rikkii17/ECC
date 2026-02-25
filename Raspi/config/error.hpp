#ifndef ERROR_HPP
    #define ERROR_HPP
    
    #include<iostream>
    //CLIにエラー文を表示

    class error_number{
    public:
        class initialization{
        public:

            static constexpr int ALARM_FILE_IS_NOT_FOUND = -1;
        };

        class filesystem{
        public:
            
            static constexpr int OK = 0;
            static constexpr int CREATE_DATA_DIR = 1;
            static constexpr int FILE_IS_EMPTY = 1;
            
            static constexpr int SYSTEM_DIR_IS_NOT_EXIST = -1;
            static constexpr int DIR_CANNOT_CREATE = -2;
            static constexpr int FILE_IS_NOT_OPEN = -3;
            
        };
    };

    class error_process{
    public:
        static bool initialization_error(int error_flag);
        /*
            っ初期化エラーが出たものによってエラー処理を分岐する関数
            第1引数 :   エラーフラグ（int)
            返り値  :   system_is_runningに返すブール値
        */
    };


#endif