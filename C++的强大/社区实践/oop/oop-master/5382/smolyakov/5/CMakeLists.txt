project(curs_work)	

set(SOURCE_TEST test.cpp)	
set(SOURCE_EXE main.cpp)	
set(SOURCE_LAB_FUN lab_fun.cpp )	
set(SOURCE_FIGURE_LIB figure.cpp )	
set(SOURCE_VECTOR_LIB vector.cpp )	
set(SOURCE_SHARED_PTR_LIB shared_ptr.cpp )	

add_definitions()

add_library(figure STATIC ${SOURCE_FIGURE_LIB})
add_library(vector STATIC ${SOURCE_VECTOR_LIB})
#add_library(lab_fun STATIC ${SOURCE_LAB_FUN_LIB})
add_library(shared_ptr STATIC ${SOURCE_SHARED_PTR_LIB})

add_executable(main ${SOURCE_EXE} ${SOURCE_LAB_FUN})	
add_executable(test ${SOURCE_TEST} ${SOURCE_LAB_FUN})	

target_link_libraries(main vector figure shared_ptr)		
target_link_libraries(test vector figure shared_ptr gtest)		
