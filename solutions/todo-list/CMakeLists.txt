if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
add_executable(todo_app main.cpp ToDoList.cpp ToDoList.h TimeParser.h TimeParser.cpp ToDoItem.h ToDoItem.cpp Job.h Job.cpp)
