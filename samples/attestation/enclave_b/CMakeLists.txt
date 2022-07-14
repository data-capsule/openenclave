# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.

# Generate header with public key of enclave A

if (WIN32)
  set(WIN_BASH ${OE_BASH})
endif ()

add_custom_command(
  OUTPUT enclave_a_pubkey.h
  DEPENDS public_key_a ${CMAKE_SOURCE_DIR}/gen_pubkey_header.sh
          ${CMAKE_BINARY_DIR}/enclave_a/public_a.pem
  COMMAND ${WIN_BASH} ${CMAKE_SOURCE_DIR}/gen_pubkey_header.sh enclave_a_pubkey.h
          ${CMAKE_BINARY_DIR}/enclave_a/public_a.pem)


add_library(splinter STATIC  ${CMAKE_SOURCE_DIR}/splinterdb/src/allocator.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/io.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/PackedArray.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/splinterdb_private.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/btree.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/iterator.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/pcq.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/srq.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/btree.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/log.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/task.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/btree_private.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/memtable.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/rc_allocator.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/task.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/cache.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/memtable.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/rc_allocator.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/trunk.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/clockcache.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/merge.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/routing_filter.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/trunk.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/clockcache.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/merge.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/routing_filter.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/util.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/data_internal.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/mini_allocator.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/shard_log.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/util.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/data_internal.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/mini_allocator.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/shard_log.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/default_data_config.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/PackedArray.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/splinterdb.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/laio.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/platform.c
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/platform_inline.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/pl_splinter_trace.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/laio.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/platform.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/platform_types.h
                          ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux/poison.h
                          )

target_include_directories(splinter PRIVATE ${CMAKE_SOURCE_DIR}
                                         ${CMAKE_BINARY_DIR}
                                         ${CMAKE_SOURCE_DIR}/splinterdb/include
                                         ${CMAKE_SOURCE_DIR}/splinterdb/src
                                         ${CMAKE_SOURCE_DIR}/splinterdb/src/platform_linux
                                         ${CMAKE_SOURCE_DIR}/libaio/src
                                        )
target_link_libraries(
  splinter PRIVATE openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB}
  openenclave::oehostfs openenclave::oelibc openenclave::oelibcxx
  xxHash::xxhash)


add_executable(enclave_b ecalls.cpp
                         ${CMAKE_CURRENT_BINARY_DIR}/enclave_a_pubkey.h)

if (WIN32)
  maybe_build_using_clangw(enclave_b)
endif ()

target_include_directories(enclave_b PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                ${CMAKE_SOURCE_DIR}/splinterdb/include
                # ${CMAKE_SOURCE_DIR}/splinterdb/src
                # ${CMAKE_SOURCE_DIR}/splinterdb/include/public_platform
                ${CMAKE_SOURCE_DIR}/libaio/src/)

target_link_libraries(enclave_b common ${CMAKE_SOURCE_DIR}/splinterdb/build/release/lib/libsplinterdb.so)

# Generate key B
add_custom_command(
  OUTPUT private_b.pem public_b.pem
  COMMAND openssl genrsa -out private_b.pem -3 3072
  COMMAND openssl rsa -in private_b.pem -pubout -out public_b.pem)

add_custom_target(public_key_b DEPENDS public_b.pem)

# Sign enclave B with key B
add_custom_command(
  OUTPUT enclave_b.signed
  DEPENDS enclave_b enc.conf private_b.pem
  COMMAND openenclave::oesign sign -e $<TARGET_FILE:enclave_b> -c
          ${CMAKE_CURRENT_SOURCE_DIR}/enc.conf -k private_b.pem)

add_custom_target(enclave_b_signed ALL DEPENDS enclave_b.signed)
