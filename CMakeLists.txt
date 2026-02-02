cmake_minimum_required(VERSION 4.0)
project(MyString)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyString main.cpp
        OOP_Lab_Buffer.cpp
        OOP_Lab_Buffer.h
        OOP_Lab_String.cpp
        OOP_Lab_String.h
)

if (WIN32)
    add_custom_command(TARGET MyString POST_BUILD
            # Runtime MinGW
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/JetBrains/CLion 2025.3.1/bin/mingw/bin/libgcc_s_seh-1.dll"
            "$<TARGET_FILE_DIR:MyString>"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/JetBrains/CLion 2025.3.1/bin/mingw/bin/libstdc++-6.dll"
            "$<TARGET_FILE_DIR:MyString>"

            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/Program Files/JetBrains/CLion 2025.3.1/bin/mingw/bin/libwinpthread-1.dll"
            "$<TARGET_FILE_DIR:MyString>"
    )
endif()
