cmake_minimum_required(VERSION 3.10)
project(DbMessenger C)

set(ecpg_files main.pgc Accounts.pgc Context.pgc Dialogs.pgc Locks.pgc Messages.pgc)

execute_process(
        COMMAND ecpg ${ecpg_files}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} main.c IO.c)

execute_process(COMMAND pg_config --includedir OUTPUT_VARIABLE ECPG_INCLUDEDIR)
target_include_directories(${PROJECT_NAME} PUBLIC ${ECPG_INCLUDEDIR})
if (WIN32)
    execute_process(COMMAND pg_config --libdir OUTPUT_VARIABLE ECPG_LIBDIR)
    find_library(ECPG_LIB libecpg HINTS ${ECPG_LIBDIR} REQUIRED)
    find_library(PGTYPES_LIB libpgtypes HINTS ${ECPG_LIBDIR} REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${ECPG_LIB} ${PGTYPES_LIB})
endif (WIN32)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC ecpg pgtypes)
endif (UNIX)
