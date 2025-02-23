# Rowhammer Lab

**Learning Objectives**
* Investigate the physical memory controller and learn how banked DRAM is implemented.
* Implement a double-sided Rowhammer attack to flip bits in a victim address.

**Note on XOR function**

There is a way to have a different "correct" XOR function 24 years in a row for the Bank ID mapping in the rowhammer lab - you just shuffle the XOR pairings in the function listing so it looks different every year in the lab. The bank IDs will change for addresses, but will remain consistent for the set of addresses in the same bank.

**Note on Obfuscation for Distributed Reference Solution**
Since we distribute reference solutions as a checker, some obfuscation is applied onto the functions with solutions. Take a look at `src/obfuscator.hh` and its usage in `src/verif.cc` for more details. Effectively, each function with a solution is wrapped in a stub, and a trampoline calls into it. The trampoline performs a runtime decryption routine on the function. The encryption key is specified during the build process, and the decryption routine takes the SHA256 hash of it to then use as the key and IV to an AES CBC decryption routine. `static inline` with `always_inline` attribute is aggressively applied to make solving the task at hand simpler than pulling the solution from decompilation or reversing (as this is a security class after all).

Use `ENCRYPT_FUNC` to label a function for encryption, and place an `ENCRYPT_FUNC_END` afterwards. `-fno-toplevel-reorder` is an important flag to use for gcc in this case. Make calls with the arguments forwarded through `ENCRYPT_FUNC_CALL` or `ENCRYPT_FUNC_CALL_VOID`. `encrypt.py` is added in the build process to handle post-compilation encryption.