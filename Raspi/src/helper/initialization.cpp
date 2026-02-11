#include"initialization.hpp"


int initialization::software::device(){
    int error_flag;
    
    error_flag = initialization::software::alarm_file_initialization();
    //エラー時の処理
    if(error_flag == error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST){
        std::cerr<<"error"<<std::setw(1)<<":"<<"system directory is not found"<<std::endl;
        std::cerr<<"\t"<<std::filesystem::current_path()<<std::endl;
        return(error_number::initialization::ALARM_FILE_IS_NOT_FOUND);
    }

    return(error_number::filesystem::OK);
}

int initialization::software::alarm_file_initialization(){
    //プロジェクトデータディレクトリまで移動
    if(int errorflag = filesystem_helper::move::device_data_directory() != error_number::filesystem::OK){
        if(errorflag == error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST)  return(error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST);
    }




    return(error_number::filesystem::OK);
}