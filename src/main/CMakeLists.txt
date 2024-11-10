set(target ex)

add_executable(${target})

target_sources(
  ${target}
  PRIVATE
    main.cpp
)

target_link_libraries(
  ${target}
  PRIVATE
	lib-cipher
	lib-cryptographic
	lib-signature
)