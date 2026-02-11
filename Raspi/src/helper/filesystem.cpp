#include"filesystem.hpp"


int filesystem_helper::move::device_data_directory(){
    
    if(!std::filesystem::exists(directory_path::var) || !std::filesystem::is_directory(directory_path::var))  return(error_number::initialization::SYSTEM_DIR_IS_NOT_EXIST);
    std::filesystem::current_path(directory_path::var);
    if(!std::filesystem::exists(directory_path::lib) || !std::filesystem::is_directory(directory_path::lib))  return(error_number::initialization::SYSTEM_DIR_IS_NOT_EXIST);
    std::filesystem::current_path(directory_path::lib);
    //system標準ディレクトリ内の移動

    if(!std::filesystem::exists(directory_path::system_data_directory) || !std::filesystem::is_directory(directory_path::system_data_directory)){    
        std::filesystem::create_directory(directory_path::system_data_directory);
        return(error_number::initialization::CREATE_DATA_DIR);
    }

    
    return(error_number::initialization::OK);
}