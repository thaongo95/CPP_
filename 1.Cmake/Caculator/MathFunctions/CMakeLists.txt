add_library(MathFunctions MathFunctions.cpp)

# TODO 1: State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword

target_include_directories(MathFunctions INTERFACE 
					${CMAKE_CURRENT_SOURCE_DIR})

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cpp
              )

  # TODO 6: Link SqrtLibrary to tutorial_compiler_flags

  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()
set(installable_libs MathFunctions)
if(TARGET SqrtLibrary)
	list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs} DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)

# TODO 7: Link MathFunctions to tutorial_compiler_flags
