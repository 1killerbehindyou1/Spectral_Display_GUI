project(SpectralDisplay VERSION 0.1 LANGUAGES CXX)

if(BUILD_UT)
    add_subdirectory(pictures_for_tests)
    add_subdirectory(unit_tests)
endif()

if(BUILD_BENCHMARK_TESTS)
	add_subdirectory(benchmark_tests)
endif()