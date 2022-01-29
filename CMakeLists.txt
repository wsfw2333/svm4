PROJECT(svm3) 

cmake_minimum_required(VERSION 3.5) 

find_package(OpenCV REQUIRED) 

include_directories(${OpenCV_INCLUDE_DIRS}) 


add_executable (svm3_pic svm3.cpp) 

link_directories(${OpenCV_LIBRARY_DIRS})



target_link_libraries(svm3_pic  ${OpenCV_LIBRARIES} )
                    

