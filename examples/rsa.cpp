#include <iostream>
#include <cstring>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace std;

// Error handling function
void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

int main() {
    // Plaintext message to be encrypted
    unsigned char plaintext[] = "Hello, world!";

    // Generate RSA keypair
    RSA *rsa = RSA_new();
    BIGNUM *bn = BN_new();
    int bits = 2048; // or choose your own key size
    int exp = RSA_F4;
    BN_set_word(bn, exp);
    RSA_generate_key_ex(rsa, bits, bn, nullptr);

    // Get the length of the modulus in bytes
    int modulus_len = BN_num_bytes(RSA_get0_n(rsa));

    // Allocate memory for the encrypted message and the decrypted message
    unsigned char *ciphertext = new unsigned char[modulus_len];
    unsigned char *decryptedtext = new unsigned char[modulus_len];

    // Encrypt the plaintext
    int ciphertext_len = RSA_public_encrypt(strlen((char *) plaintext), plaintext, ciphertext, rsa, RSA_PKCS1_PADDING);
    if (ciphertext_len == -1) {
        handleErrors();
    }
    cout << ciphertext_len << "|" << ::strlen((char *) ciphertext) << rsa << endl;
    // Decrypt the ciphertext
    int decryptedtext_len = RSA_private_decrypt(ciphertext_len, ciphertext, decryptedtext, rsa, RSA_PKCS1_PADDING);
    if (decryptedtext_len == -1) {
        handleErrors();
    }

    // Print the original plaintext, the encrypted message, and the decrypted message
    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: ";
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02X", ciphertext[i]);
    }
    cout << endl;
    cout << "Decrypted text: " << decryptedtext << endl;

    // Clean up memory and resources
    RSA_free(rsa);
    BN_free(bn);
    delete[] ciphertext;
    delete[] decryptedtext;

    return 0;
}
