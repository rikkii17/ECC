#ifndef INITIALIZATION_HPP
    #define INITIALIZATION_HPP

    #include<iostream>
    //CLI出力させる目的
    #include<iomanip>
    //高度なCLI出力ライブラリ
    #include<filesystem>
    //ディレクトリ、ファイルを操作する目的
    #include<fstream>
    //ファイルを読み書きするためのライブラリ
    #include<csv.hpp>
    //CSVのファイルを扱うためのライブラリ

    #include"softconfig.hpp"
    //filepathの定数などを取得する
    #include"filesystem.hpp"
    //システムのファイル操作などをまとめるライブラリ
    #include"error.hpp"
    //エラー関係を扱うライブラリ
    #include"clock_system_config.hpp"
    //時計関係のconfigを入れるライブラリ
    #include"hardware.hpp"
    #include"hardware_config.hpp"

    class initialization{
    public:
            class software{
            public:
                static int device();
                /*
                    全体の初期化を行う。
                    
                    引数:   void
                    返り値: void
                */

                static int alarm_file_initialization();

                static void input_pin();


        };
    };
    
#endif