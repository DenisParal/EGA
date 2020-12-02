cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(EvolutionGeneticAlgorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")
set(INCLUDE_DIR include)

function(build_src SRC_NAME)
    set(TARGET_DIR "src/${SRC_NAME}.cpp")
    add_executable(${SRC_NAME} ${TARGET_DIR})
    target_include_directories(${SRC_NAME} PUBLIC ${INCLUDE_DIR})
endfunction(build_src)

#build_src(monte_carlo)
#build_src(DFS_alg)
#build_src(BFS_alg)
#build_src(test_utils)
#build_src(BFS_Grey_alg)
#build_src(Random_alg)
#build_src(MNN)
#build_src(MNC)
build_src(greedy)

