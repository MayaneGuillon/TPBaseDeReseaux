cmake_minimum_required(VERSION 3.23)
project(TPBaseDeReseaux C)

set(CMAKE_C_STANDARD 11)

add_executable(TPBaseDeReseaux
        main.c Q4/rrq_data_ack.c)
