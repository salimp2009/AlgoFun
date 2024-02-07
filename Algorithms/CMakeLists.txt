cmake_minimum_required(VERSION 3.21)
project(Algorithms)

add_compile_options(
  -O1 -g -flto #[[ -S ]] 
  #[[ -fsanitize=address ]] #[[ -fsanitize=memory ]]
  #[[ -fno-omit-frame-pointer ]]
)
add_link_options(
  -g -flto #[[ -S ]]
  #[[ -fsanitize=address ]]
)

include(../cmake/warnings.cmake)
project_warnings()

# added to use precompiled headers
add_library(algorithmsPCH INTERFACE)
target_precompile_headers(algorithmsPCH INTERFACE [["algorithmsPCH.hpp"]])

target_include_directories(
  algorithmsPCH INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)

add_library(
  algoFunLib
  src/AlgoFun/AlgoFindMissingElem.hpp
  src/AlgoFun/AlgoFun.cpp
  src/AlgoFun/AlgoFun.hpp
  src/AlgoFun/SlideAlgorithm.hpp
  src/AlgoFun/GatherAlgorithm.hpp
  src/AlgoFun/StablePartitionPosition.hpp
  src/AlgoFun/SortSubRange.hpp
  src/AlgoFun/SortSubRange.cpp
  src/AlgoFun/accumulate_n.hpp
  src/AlgoFun/accumulate_iter.hpp
  src/AlgoFun/algoConcepts.hpp
  src/AlgoFun/fold_left.hpp
  src/AlgoFun/reduce_par.hpp
  src/AlgoFun/stable_partitionPos.hpp
  src/AlgoFun/stable_partitionUserBuffer.hpp)

target_include_directories(algoFunLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(algoFunLib PRIVATE algorithmsPCH)

add_executable(AlgoFun src/algorithms_Test.cpp)
# to generate assembly while compiling & linking 
# target_compile_options(AlgoFun PRIVATE -save-temps=obj)

target_link_libraries(AlgoFun PRIVATE project_options algoFunLib)
