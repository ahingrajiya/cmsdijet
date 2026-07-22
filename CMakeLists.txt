cmake_minimum_required(VERSION 3.10)
project(JetAnalysis
        VERSION 1.0 
        LANGUAGES C CXX)

set(libname JetAnalysis)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")

set(ROOUNFOLD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Unfoilding/RooUnfold/build)
message(STATUS "Looking for CERN ROOT")
#Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT CONFIG REQUIRED)
if (ROOT_FOUND)
        message(STATUS "ROOT ${ROOT_VERSION} found at ${ROOT_BINDIR}") 
        message(STATUS "ROOT include dir found at ${ROOT_INCLUDE_DIRS}")
        message(STATUS "ROOT libraries found at ${ROOT_LIBRARIES}")
else()
        message(FATAL_ERROR "ROOT not found. CMake will exit!")
endif()

find_library(ROOUNFOLD_LIBRARY
        NAMES RooUnfold
        PATHS ${ROOUNFOLD_DIR}
        NO_DEFAULT_PATH
)

if (NOT ROOUNFOLD_LIBRARY)
        message(FATAL_ERROR "RooUnfold library not found in ${ROOUNFOLD_DIR}. Build RooUnfold there first.")
endif()

message(STATUS "Found RooUnfold library at ${ROOUNFOLD_LIBRARY}")
#Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# Directories where to search for include files
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/interface
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${ROOT_INCLUDE_DIRS}
        ${ROOUNFOLD_DIR}
)

# Add same CXX flags that were used to combile and build ROOT (including CXX standard)
add_definitions(${ROOT_CXX_FLAGS})

# List all headers to be used to generate dictionary and added to the library
set(HEADERS
        interface/JetEnergyScale.h
        interface/Unfolding.h

)

# List source files
set(SRC 
        src/JetEnergyScale.cc
        src/Unfolding.cc
       
)

# Generate ROOT dictionaries
root_generate_dictionary(G__${libname} 
                         ${HEADERS}
                         LINKDEF interface/LinkDef.h
)

# Generate rootmap
root_generate_rootmap(${libname} LINKDEF interface/LinkDef.h)


add_library(${libname} SHARED ${SRC} G__${libname}.cxx)
# Link libraries need to run the code
target_link_libraries(${libname} ${ROOT_LIBRARIES})
target_link_libraries(${libname} ${ROOT_LIBRARIES} ${ROOUNFOLD_LIBRARY})


add_executable(unfoldingAna src/unfoldingAna.cxx)
target_link_libraries(unfoldingAna ${libname})

foreach(src_file IN LISTS SRC)
    get_filename_component(src_name ${src_file} NAME_WE)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${src_name}.s
        COMMAND ${CMAKE_CXX_COMPILER} -S -masm=intel -O2
                ${CMAKE_CURRENT_SOURCE_DIR}/${src_file}
                -o ${CMAKE_CURRENT_BINARY_DIR}/${src_name}.s
        DEPENDS ${src_file}
        COMMENT "Generating assembly for ${src_name}.cc"
    )
endforeach()


