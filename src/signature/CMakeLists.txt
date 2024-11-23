add_library(lib-signature STATIC
	signature.cpp
)

find_package(OpenSSL REQUIRED)

if (OpenSSL_FOUND)
    message(STATUS "OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL libraries: ${OPENSSL_LIBRARIES}")
else()
    message(FATAL_ERROR "OpenSSL not found!")
endif()


target_link_libraries(
  lib-signature
  PRIVATE
	lib-cryptographic
	lib-cipher
	OpenSSL::Crypto
)

