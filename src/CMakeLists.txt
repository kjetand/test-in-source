# Add modules here (name maps directly to source file name)
set(_app_modules math app)
set(_app_dependencies fmt::fmt)
set(_app_test_dependencies Catch2::Catch2)

set(_app_name ${PROJECT_NAME})
add_executable(${_app_name})

set(_compile_flags)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Building for MSVC")
    set(_compile_flags /interface)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Building for GCC")
    set(_compile_flags -fmodules-ts)
else ()
    message(FATAL_ERROR "Compiler not supported: ${CMAKE_CXX_COMPILER_ID}")
endif ()
message(STATUS "Using compile flags: ${_compile_flags}")

if (APP_BUILD_TESTS)
    list(APPEND _app_dependencies ${_app_test_dependencies})
endif ()
message(STATUS "Application dependencies: ${_app_dependencies}")

function(define_module_targets _module_names _module_dependencies _out_module_targets)
    set(_previous_module)
    set(_modules)
    foreach (_module ${_module_names})
        set(_current_module ${_module}-module)
        list(APPEND _modules ${_current_module})

        add_library(${_current_module} OBJECT ${_module}.cpp)
        target_link_libraries(${_current_module} PRIVATE ${_module_dependencies})
        target_compile_options(${_current_module} PRIVATE ${_compile_flags})

        if (_previous_module)
            # Depend on previous compiled module
            add_dependencies(${_current_module} ${_previous_module})
        endif ()

        set(_previous_module ${_current_module})
    endforeach ()
    # Make app depend on last compiled module
    add_dependencies(${_app_name} ${_previous_module})
    set(${_out_module_targets} ${_modules} PARENT_SCOPE)
endfunction()

define_module_targets("${_app_modules}" "${_app_dependencies}" _module_targets)

message(STATUS "Modules: ${_module_targets}")

target_sources(${_app_name} PRIVATE main.cpp)
target_compile_options(${_app_name} PRIVATE ${_compile_flags})
target_link_libraries(${_app_name} PRIVATE ${_module_targets} ${_app_dependencies})

add_custom_target(run
        COMMAND${_app_name}
        DEPENDS${_app_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
