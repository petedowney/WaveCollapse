
if(NOT "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitinfo.txt" IS_NEWER_THAN "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/local/bin/git"  clone --no-checkout --depth 1 --no-single-branch --config "advice.detachedHead=false" "https://github.com/MikePopoloski/boost_unordered" "boost_unordered-src"
    WORKING_DIRECTORY "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/MikePopoloski/boost_unordered'")
endif()

execute_process(
  COMMAND "/usr/local/bin/git"  checkout v1.0 --
  WORKING_DIRECTORY "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v1.0'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/local/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitinfo.txt"
    "/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/petedowney/Documents/GitHub/WaveCollapse/build/temp.macosx-10.9-x86_64-cpython-310/WaveCollapseInterface/_deps/boost_unordered-subbuild/boost_unordered-populate-prefix/src/boost_unordered-populate-stamp/boost_unordered-populate-gitclone-lastrun.txt'")
endif()

