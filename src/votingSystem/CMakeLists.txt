add_library(lib-votingSystem STATIC
	votingSystem.cpp
)

target_link_libraries(
  lib-votingSystem
  PRIVATE
	lib-cryptographic
	lib-cipher
)

