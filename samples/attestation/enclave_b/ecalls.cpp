// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.
#include <common/attestation_t.h>
#include <common/dispatcher.h>
#include <enclave_a_pubkey.h>
#include <openenclave/enclave.h>

#include <fstream>      // std::ifstream
#define DB_FILE_SIZE_MB 1024 // Size of SplinterDB device; Fixed when created
#define CACHE_SIZE_MB   64   // Size of cache; can be changed across boots
#define DB_FILE_NAME    "splinterdb_intro_db"
/* Application declares the limit of key-sizes it intends to use */
#define USER_MAX_KEY_SIZE ((int)100)

extern "C" {
#include "splinterdb/public_platform.h"
#include "splinterdb/default_data_config.h"
#include "splinterdb/splinterdb.h"
}

int
run_splinter_hello()
{
   printf("     **** SplinterDB Basic example program ****\n\n");

   // Initialize data configuration, using default key-comparison handling.
   data_config splinter_data_cfg;

   default_data_config_init(USER_MAX_KEY_SIZE, &splinter_data_cfg);

//    // Basic configuration of a SplinterDB instance
    splinterdb_config splinterdb_cfg;
    memset(&splinterdb_cfg, 0, sizeof(splinterdb_cfg));
   splinterdb_cfg.filename   = DB_FILE_NAME;
   splinterdb_cfg.disk_size  = (DB_FILE_SIZE_MB * 1024 * 1024);
   splinterdb_cfg.cache_size = (CACHE_SIZE_MB * 1024 * 1024);
   splinterdb_cfg.data_cfg   = &splinter_data_cfg;

    splinterdb *spl_handle = NULL; // To a running SplinterDB instance

    int rc = splinterdb_create(&splinterdb_cfg, &spl_handle);
    printf("Created SplinterDB instance, dbname '%s'.\n\n", DB_FILE_NAME);

//    // Insert a few kv-pairs, describing properties of fruits.
    const char *fruit = "apple";
   const char *descr = "An apple a day keeps the doctor away!";
   slice       key   = slice_create((size_t)strlen(fruit), fruit);
   slice       value = slice_create((size_t)strlen(descr), descr);

//    rc = splinterdb_insert(spl_handle, key, value);
//    printf("Inserted key '%s'\n", fruit);

//    fruit = "Orange";
//    descr = "Is a good source of vitamin-C.";
//    key   = slice_create((size_t)strlen(fruit), fruit);
//    value = slice_create((size_t)strlen(descr), descr);
//    rc    = splinterdb_insert(spl_handle, key, value);
//    printf("Inserted key '%s'\n", fruit);

//    fruit = "Mango";
//    descr = "Mango is the king of fruits.";
//    key   = slice_create((size_t)strlen(fruit), fruit);
//    value = slice_create((size_t)strlen(descr), descr);
//    rc    = splinterdb_insert(spl_handle, key, value);
//    printf("Inserted key '%s'\n", fruit);

//    // Retrieve a key-value pair.
//    splinterdb_lookup_result result;
//    splinterdb_lookup_result_init(spl_handle, &result, 0, NULL);

//    fruit = "Orange";
//    key   = slice_create((size_t)strlen(fruit), fruit);
//    rc    = splinterdb_lookup(spl_handle, key, &result);
//    rc    = splinterdb_lookup_result_value(spl_handle, &result, &value);
//    if (!rc) {
//       printf("Found key: '%s', value: '%.*s'\n",
//              fruit,
//              (int)slice_length(value),
//              (char *)slice_data(value));
//    }

//    // Handling non-existent keys
//    fruit = "Banana";
//    key   = slice_create((size_t)strlen(fruit), fruit);
//    rc    = splinterdb_lookup(spl_handle, key, &result);
//    rc    = splinterdb_lookup_result_value(spl_handle, &result, &value);
//    if (rc) {
//       printf("Key: '%s' not found. (rc=%d)\n", fruit, rc);
//    }
//    printf("\n");

//    printf("Shutdown and reopen SplinterDB instance ...\n");
//    splinterdb_close(&spl_handle);

//    rc = splinterdb_open(&splinterdb_cfg, &spl_handle);
//    if (rc) {
//       printf("Error re-opening SplinterDB instance, dbname '%s' (rc=%d).\n",
//              DB_FILE_NAME,
//              rc);
//       return (rc);
//    }

//    // Retrieve all the key-value pairs from the database
//    printf("Iterate through all the key-value pairs"
//           " returning keys in lexicographic sort order:\n");

//    splinterdb_iterator *it = NULL;
//    rc = splinterdb_iterator_init(spl_handle, &it, NULL_SLICE);

//    int i = 0;
//    for (; splinterdb_iterator_valid(it); splinterdb_iterator_next(it)) {
//       slice key, value;
//       splinterdb_iterator_get_current(it, &key, &value);
//       printf("  [%d] key='%.*s', value='%.*s'\n",
//              i,
//              (int)slice_length(key),
//              (char *)slice_data(key),
//              (int)slice_length(value),
//              (char *)slice_data(value));
//       i++;
//    }
//    rc = splinterdb_iterator_status(it);
//    splinterdb_iterator_deinit(it);

//    printf("Found %d key-value pairs\n\n", i);

//    splinterdb_close(&spl_handle);
//    printf("Shutdown SplinterDB instance, dbname '%s'.\n\n", DB_FILE_NAME);

}

// For this purpose of this example: demonstrating how to do attestation
// g_enclave_secret_data is hardcoded as part of the enclave. In this sample,
// the secret data is hard coded as part of the enclave binary. In a real world
// enclave implementation, secrets are never hard coded in the enclave binary
// since the enclave binary itself is not encrypted. Instead, secrets are
// acquired via provisioning from a service (such as a cloud server) after
// successful attestation.
// This g_enclave_secret_data holds the secret data specific to the holding
// enclave, it's only visible inside this secured enclave. Arbitrary enclave
// specific secret data exchanged by the enclaves. In this sample, the first
// enclave sends its g_enclave_secret_data (encrypted) to the second enclave.
// The second enclave decrypts the received data and adds it to its own
// g_enclave_secret_data, and sends it back to the other enclave.
uint8_t g_enclave_secret_data[ENCLAVE_SECRET_DATA_SIZE] =
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

enclave_config_data_t config_data = {
    g_enclave_secret_data,
    OTHER_ENCLAVE_PUBLIC_KEY,
    sizeof(OTHER_ENCLAVE_PUBLIC_KEY)};

// Declare a static dispatcher object for enabling
// for better organizing enclave-wise global variables
static ecall_dispatcher dispatcher("Enclave2", &config_data);
const char* enclave_name = "Enclave2";

int get_enclave_format_settings(
    const oe_uuid_t* format_id,
    format_settings_t* format_settings)
{
    return dispatcher.get_enclave_format_settings(format_id, format_settings);
}

/**
 * Return the public key of this enclave along with the enclave's
 * evidence. Another enclave can use the evidence to attest the enclave
 * and verify the integrity of the public key.
 */
int get_evidence_with_public_key(
    const oe_uuid_t* format_id,
    format_settings_t* format_settings,
    pem_key_t* pem_key,
    evidence_t* evidence)
{
        run_splinter_hello();
    return dispatcher.get_evidence_with_public_key(
        format_id, format_settings, pem_key, evidence);
}

// Attest and store the public key of another enclave.
int verify_evidence_and_set_public_key(
    const oe_uuid_t* format_id,
    pem_key_t* pem_key,
    evidence_t* evidence)
{
    return dispatcher.verify_evidence_and_set_public_key(
        format_id, pem_key, evidence);
}

// Encrypt message for another enclave using the public key stored for it.
int generate_encrypted_message(message_t* message)
{
    return dispatcher.generate_encrypted_message(message);
}

// Process encrypted message
int process_encrypted_message(message_t* message)
{
    return dispatcher.process_encrypted_message(message);
}
