#include"filesystem.hpp"


int filesystem_helper::move::device_data_directory(){
    
    if(!std::filesystem::exists(directory_path::var) || !std::filesystem::is_directory(directory_path::var))  return(error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST);
    std::filesystem::current_path(directory_path::var);
    if(!std::filesystem::exists(directory_path::lib) || !std::filesystem::is_directory(directory_path::lib))  return(error_number::filesystem::SYSTEM_DIR_IS_NOT_EXIST);
    std::filesystem::current_path(directory_path::lib);
    //system標準ディレクトリ内の移動

    if(!std::filesystem::exists(directory_path::system_data_directory) || !std::filesystem::is_directory(directory_path::system_data_directory)){    
        try{
            std::filesystem::create_directory(directory_path::system_data_directory);
            std::filesystem::permissions(
                directory_path::system_data_directory,
                std::filesystem::perms::owner_all | std::filesystem::perms::group_all | std::filesystem::perms::others_all,
                std::filesystem::perm_options::replace
            );
        }catch(const std::filesystem::filesystem_error& e){
            std::cerr<<"error :project file can't create!/n"<<e.what()<<std::endl;
            return(error_number::filesystem::DIR_CANNOT_CREATE);
        }

        std::cout<<"\t\tcreate project data directory"<<std::endl;
        return(error_number::filesystem::CREATE_DATA_DIR);
    }

    
    return(error_number::filesystem::OK);
}