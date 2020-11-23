file(GLOB sources lab*)
foreach(item IN ITEMS ${sources})
    add_subdirectory(${item})
endforeach()