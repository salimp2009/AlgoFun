macro(project_warnings)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED True)

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(IS_GNU On)
    add_definitions(-DIS_GCC=true)
  else()
    set(IS_GNU Off)
    add_definitions(-DIS_GCC=false)
  endif()

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}"
                                                    STREQUAL "AppleClang")
    set(IS_CLANG On)
    add_definitions(-DIS_CLANG=true)
  else()
    set(IS_CLANG Off)
    add_definitions(-DIS_CLANG=false)
  endif()

  if(MSVC)
    add_definitions(-DIS_MSVC=true)
    # add_definitions(/WX)
    add_definitions(/W3)
    add_definitions(/wd4189)
    add_definitions(/wd4100)
    add_definitions(
      /wd4996) # 'fopen': This function or variable may be unsafe. Consider
               # using fopen_s instead. To disable deprecation, use
               # _CRT_SECURE_NO_WARNINGS.
    add_definitions(/wd4267)
    add_definitions(/wd4505)
    # add_definitions(/await) # enable coroutine support

    # Use sane and nice C++ for MSVC. This makes alternative tokens (not, and,
    # ...) as actual keywords and enables more conformant C++ in general
    add_definitions(/permissive-)
    # add_definitions(/std:c++latest)

  else()
    add_definitions(-DIS_MSVC=false)
    # add_definitions(-Werror)
    add_definitions(-Wall)
    add_definitions(-Wextra)
    add_definitions(-Wold-style-cast)
    add_definitions(-Wno-unused-variable)
    add_definitions(-Wno-unused-parameter)
    add_definitions(-Wno-unused-value)
    add_definitions(-Wno-cpp)
    add_definitions(-Wconversion)
    # add_definitions(-Wpessimizing-move)

    if(IS_GNU)
      add_definitions(-Wmisleading-indentation)
      add_definitions(-Wduplicated-cond)
      add_definitions(-Wduplicated-branches)
      add_definitions(-Wlogical-op) # warn about logical operations being used
                                    # where bitwise were probably wanted
      add_definitions(-Wuseless-cast) # warn if you perform a cast to the same
                                      # type
      add_definitions(-Wpessimizing-move)
      # add_definitions(-fcoroutines) # required for GCC-10
    endif()

    if(IS_CLANG)
      add_definitions(-Wall)
      add_definitions(-Wno-unused-private-field)
      add_definitions(-Wno-unneeded-internal-declaration)
      add_definitions(-fcoroutines-ts)

    else()
      add_definitions(-fcoroutines) # required for GCC-10
      add_definitions(-fpermissive) # to relax typename requirement

    endif()
  endif()
endmacro()
