
find_package(Git)

if (GIT_FOUND)
  set(GIT_REVISION_COMMAND  ${GIT_EXECUTABLE} rev-parse --verify HEAD --short=8)

  execute_process(COMMAND ${GIT_REVISION_COMMAND}
    RESULT_VARIABLE GIT_REVISION_VALID
    OUTPUT_VARIABLE GIT_REVISION)

  string(REPLACE "\n" "" GIT_REVISION ${GIT_REVISION})

  if (NOT ${GIT_REVISION_VALID} EQUAL 0)
    message(WARNING "${GIT_REVISION_COMMAND} failed, build will not have a revision.")
    set(GIT_REVISION "unknown")
  endif()
else()
  message(WARNING "Git not found, build will not have a revision")
  set(GIT_REVISION "unknown")
endif()

file(WRITE revision.h.in "#define GIT_REVISION \"${GIT_REVISION}\"\n")

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
  revision.h.in revision.h)
