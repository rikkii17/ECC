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
            static int alarm_file_initialization();
            /*
                アラームファイルの読み込みを行う（未実装）
                
                引数    ;なし
                返り値  :レスポンスコード
            */
        };

        class hardware{
            static void output_pin();
            /*
                ハードウェアのoutputピンを確保するための関数
            */
        };


        
        static int device();
            /*
                全体の初期化を行う。
                
                引数:   void
                返り値: レスポンスコード
            */
           
    };
    
#endif