#include"error.hpp"

bool error_process::initialization_error(int error_flag){
    if(error_flag == error_number::initialization::OK)  return(false);
    std::string input_data;
    if(error_flag == error_number::initialization::ALARM_FILE_IS_NOT_FOUND){
        std::cout<<"Unable to obtain alarm history"<<std::endl;
        std::cout<<"Do you want to start it as is?(Y/n)"<<std::endl;
        std::cin>>input_data;
        if(input_data[0] == 'N' || input_data[0] == 'n')    return(false);
    }

    return(true);
}