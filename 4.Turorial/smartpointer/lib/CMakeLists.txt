add_library(SmartPtr STATIC smart_pointer.cpp)

target_include_directories(SmartPtr PUBLIC 
            S{CMAKE_CURRENT_SOURCE_DIR}/lib)