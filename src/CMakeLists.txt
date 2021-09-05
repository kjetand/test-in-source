set(APP_MODULES ${PROJECT_NAME}-modules)
set(APP_SOURCES math.cpp app.cpp)

add_library(${APP_MODULES} OBJECT ${APP_SOURCES})
target_compile_features(${APP_MODULES} PUBLIC cxx_std_20)
target_compile_options(${APP_MODULES} PUBLIC /interface)

set(APP_DEPENDENCIES fmt::fmt)

if (APP_BUILD_TESTS)
    list(APPEND APP_DEPENDENCIES Catch2::Catch2)
endif ()

target_link_libraries(${APP_MODULES} PUBLIC ${APP_DEPENDENCIES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${APP_MODULES})

add_custom_target(run
        COMMAND ${PROJECT_NAME}
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
