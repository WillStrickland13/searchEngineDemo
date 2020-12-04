cmake_minimum_required(VERSION 3.14)
project(search-engine)
set (EXE_NAME search_engine)


##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "00acd3fd31ed0cde8df286697caefc5298e54df1.json")
set (input02 "stopWords.txt")

#
##########################################

#Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
add_executable(${EXE_NAME} quickstart.cpp simdjson.cpp simdjson.h HashTable.cpp HashTable.h
        documentParser.cpp documentParser.h porter2_stemmer.h porter2_stemmer.cpp
        hash.h string_view.h AVLTree.h Document.cpp Document.h Word.h Word.cpp Index.cpp Index.h
        QueryEngine.cpp QueryEngine.h)