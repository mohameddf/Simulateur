cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Simulateur)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INSTALL_PREFIX ~/Bureau)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ./bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "-lsqlite3")

install(PROGRAMS bin/Release/Simulateur
  DESTINATION ~/Bureau
  RENAME ${CMAKE_PROJECT_NAME})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)


# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)
if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
     message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ../Simulateur
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
endif()


include_directories( ${Qt5Widgets_INCLUDES} include/ include/core include/gui include/states /usr/include)
link_directories(/usr/lib)

file(
        GLOB_RECURSE
        HEADERS
        "include/*.h"
)
file(
	GLOB_RECURSE
	SOURCES
	"src/*.cc"
	)

add_executable (Simulateur ${SOURCES} ${HEADERS})
target_link_libraries(Simulateur ${Qt5Widgets_LIBRARIES} Qt5::Xml sqlite3)	


#Crée l'archive du project
SET(DIST_DIR "${CMAKE_PROJECT_NAME}")
ADD_CUSTOM_TARGET(dist 
		  COMMAND rm -rf ${DIST_DIR}
		  COMMAND mkdir  ${DIST_DIR}
                  COMMAND cp -r ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/bin ${CMAKE_SOURCE_DIR}/docs ${CMAKE_SOURCE_DIR}/.gitignore ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/simulateur.db ${DIST_DIR}   || true
		  COMMAND rm -rf ${DIST_DIR}/build
		  COMMAND mkdir ${DIST_DIR}/build
		  COMMAND rm -rf ${DIST_DIR}/build
                  COMMAND tar --exclude="*~" --exclude="._*" --exclude="CMakeFiles" --exclude="cmake*" --exclude="docs/html" -zcvf ${DIST_DIR}.tar.gz ${DIST_DIR}
		  COMMAND rm -rf  ${DIST_DIR}
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

ADD_CUSTOM_TARGET(run COMMAND cd bin/Release && ./Simulateur)
ADD_CUSTOM_TARGET(rundebug COMMAND cd bin/Debug && ./Simulateur)
ADD_CUSTOM_TARGET(doc COMMAND doxygen docs/Doxyfile)
ADD_CUSTOM_TARGET(release COMMAND cmake -DCMAKE_BUILD_TYPE=Release && make)
ADD_CUSTOM_TARGET(debug COMMAND cmake -DCMAKE_BUILD_TYPE=Debug && make)
