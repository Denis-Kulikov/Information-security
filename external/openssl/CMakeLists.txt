include(FetchContent)

FetchContent_Declare(
    openssl
    GIT_REPOSITORY https://github.com/openssl/openssl
    GIT_SHALLOW TRUE
    GIT_TAG OpenSSL_1_1_1
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
)

FetchContent_MakeAvailable(openssl)
