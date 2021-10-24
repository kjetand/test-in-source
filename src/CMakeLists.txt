# Add modules here (name maps directly to source file name)
set(_app_modules math app)

function(set_global_compiler_options)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(STATUS "Building for MSVC")
        add_compile_options(/interface)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Building for GCC")
        add_compile_options(-fmodules-ts)
    else ()
        message(FATAL "Compiler not supported: ${CMAKE_CXX_COMPILER_ID}")
    endif ()
endfunction()

function(get_external_dependencies _out_dependencies)
    set(_deps fmt::fmt)
    if (APP_BUILD_TESTS)
        list(APPEND _deps Catch2::Catch2)
    endif ()
    set(${_out_dependencies} ${_deps} PARENT_SCOPE)
endfunction()

function(define_module_targets _module_names _module_dependencies _out_module_targets)
    set(_previous_module)
    set(_modules)
    foreach (_module ${_module_names})
        set(_current_module ${_module}-module)
        list(APPEND _modules ${_current_module})

        add_library(${_current_module} OBJECT ${_module}.cpp)
        target_link_libraries(${_current_module} PUBLIC ${_module_dependencies})

        if (_previous_module)
            add_dependencies(${_current_module} ${_previous_module})
        endif ()

        set(_previous_module ${_current_module})
    endforeach ()
    set(_out_module_targets ${_modules} PARENT_SCOPE)
endfunction()

set_global_compiler_options()
get_external_dependencies(_app_dependencies)
define_module_targets("${_app_modules}" "${_app_dependencies}" _module_targets)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${_module_targets} ${_app_dependencies})

add_custom_target(run
        COMMAND ${PROJECT_NAME}
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
