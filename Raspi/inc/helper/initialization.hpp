#ifndef INITIALIZATION_HPP
    #define INITIALIZATION_HPP

    #include<iostream>
    //CLI出力させる目的
    #include<filesystem>
    //ディレクトリ、ファイルを操作する目的
    #include<fstream>
    //ファイルを読み書きするためのライブラリ
    #include<csv.hpp>
    //CSVのファイルを扱うためのライブラリ

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


        };
    };
    
#endif