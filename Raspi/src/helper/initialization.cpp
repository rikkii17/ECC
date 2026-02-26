#include"initialization.hpp"

//device関数
int initialization::device(){
    
    if(int error_flag = initialization::software::alarm_file_initialization() != error_number::filesystem::OK){
        //ファイルが空の時の処理
        if(error_flag == error_number::filesystem::FILE_IS_EMPTY){
            std::cout<<"\t No alarms are set"<<std::endl;
        }
        //system系のディレクトリが見つからない場合の処理
        else if(error_flag == error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST){
            std::cerr<<"error"<<std::setw(1)<<":"<<"system directory is not found"<<std::endl;
            std::cerr<<"\t"<<std::filesystem::current_path()<<std::endl;
            return(error_number::initialization::ALARM_FILE_IS_NOT_FOUND);
        }
        //ファイルが開かなかった場合の処理
        else if (error_flag == error_number::filesystem::FILE_IS_NOT_OPEN){
            std::cerr<<"error"<<std::setw(2)<<":<<alarm list is not aquisition"<<std::endl;
            return(error_number::initialization::ALARM_FILE_IS_NOT_FOUND);
        }
    }

    return(error_number::filesystem::OK);
}

//softwareクラス
int initialization::software::alarm_file_initialization(){
    //プロジェクトデータディレクトリまで移動
    if(int errorflag = filesystem_helper::move::device_data_directory() != error_number::filesystem::OK){
        if(errorflag == error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST)  return(error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST);
    }

    //アラームリストのファイルを開く(作成して開く)
    std::ofstream alarm_list(std::string{filename::ALARM_LIST});

    //中身があるか確認
    if(!alarm_list.is_open())    return(error_number::filesystem::FILE_IS_NOT_OPEN);
        if(std::filesystem::file_size(std::string{filename::ALARM_LIST}) == 0)   return(error_number::filesystem::FILE_IS_EMPTY);
    alarm_list.close();

    return(error_number::filesystem::OK);
}

//hardwareクラス
