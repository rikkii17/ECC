#include"initialization.hpp"


int initialization::software::device(){
    int error_flag;
    
    error_flag = initialization::software::alarm_file_initialization();
    //ƒGƒ‰[‚Ìˆ—
    if(error_flag == error_number::initialization::SYSTEM_DIR_IS_NOT_EXIST){
        std::cerr<<"error"<<std::setw(1)<<":"<<"system directory is not found"<<std::endl;
        std::cerr<<"\t"<<std::filesystem::current_path()<<std::endl;
        return(error_number::initialization::ALARM_FILE_IS_NOT_FOUND);
    }

    return(error_number::initialization::OK);
}

int initialization::software::alarm_file_initialization(){

    if(int errorflag = filesystem_helper::move::device_data_directory() != error_number::initialization::OK){
        if(errorflag == error_number::initialization::CREATE_DATA_DIR){
            std::cout<<"create project data directory"<<std::endl;
        }
        if(errorflag == error_number::initialization::SYSTEM_DIR_IS_NOT_EXIST)  return(error_number::initialization::SYSTEM_DIR_IS_NOT_EXIST);
    }
    
    if(!std::filesystem::exists(directory_path::system_data_directory) || !std::filesystem::is_directory(directory_path::system_data_directory))    std::filesystem::create_directory(directory_path::system_data_directory);
    std::filesystem::current_path(directory_path::system_data_directory);

    

    return(error_number::initialization::OK);
}