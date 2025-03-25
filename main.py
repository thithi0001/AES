from mylib import *

# plaintext = "Hello World!"
plaintext = input("Enter plaintext: ")
key = random_vector()
nk, nr = 4, 10
roundKeys = key_expansion(key, nk, nr)

plainvector = str_to_vector_hex(plaintext)
cipher = encrypt(plainvector, roundKeys, nk, nr)

decipher = decrypt(cipher, roundKeys, nk, nr)
deciphertext = vector_hex_to_str(decipher)

# print("Plaintext:", plaintext)
print("Key (128-bit):")
print_vector_hex(key)
print("\nCipher:")
print_vector_hex(cipher)
# print("\nDeciphertext:", deciphertext)