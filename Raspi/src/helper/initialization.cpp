#include"initialization.hpp"

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
#include"error.hpp"
//エラー関係を扱うライブラリ


int initialization::software::device(){
    int error_flag;
    
    error_flag = initialization::software::alarm_file_initialization();
    //エラー時の処理
    if(error_flag = error_number::initialization::OPT_DIR_IS_NOT_EXIST){
        std::cerr<<"error"<<std::setw(1)<<":"<<"opt directory is not found"<<std::endl;
        return(error_number::initialization::ALARM_FILE_IS_NOT_FOUND);
    }

    return(error_number::initialization::OK);
}

int initialization::software::alarm_file_initialization(){
    std::filesystem::current_path("/");
    //ディレクトリを一度システムルートディレクトリに戻す
    
    if(!std::filesystem::exists("/opt") || !std::filesystem::is_directory("/opt"))  return(error_number::initialization::OPT_DIR_IS_NOT_EXIST);
    

    return(error_number::initialization::OK);
}