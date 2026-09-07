# J*B Online Assessment

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | cr0 |
| Points at close | 93 |
| Solves | 142 |
| Status | solved |

> Can you get a j*b in 2026?

Files: [`job-oa.pka`](handout/job-oa.pka)

<details>
<summary><b>My Solution</b></summary>

This is a Cisco Packet Tracer activity. Download `job-oa.pka`, complete the activity, and upload it back. `solve/pka.py` inverts the [pka2xml](https://github.com/mircodz/pka2xml) chain in pure Python (reverse then XO)R, Twofish-EAX with key 16 bytes of `137` and IV 16 bytes of `16`, then XOR again, then a four-byte big-endian size and zlib. 3 MB of ciphertext -> 73 MB of XML. In python you'll need to `pip install twofish` plus an `imp` shim, because `twofish.py` still imports the stdlib module. Screenshots and flavortext courtesy of Claude:

![three PACKETTRACER5 blocks](media/03-recon-three-networks.png)

The XML holds three `PACKETTRACER5` blocks, and block 2 is the answer we want. Router `Research-Core` has 123 config lines in the candidate block and 249 in the answer block, including all the DHCP pools we want. So to exploit we do some string slicing and paste block 2 over block 0, then re-encrypt. Blocks 0 and 1 are identical, so the file alone doesn't tell you which one the candidate edits. Luckily, the encryptor round-trips the untouched XML byte for byte, and uploading that still scores 18/122, so re-encryption alone doesn't change anything. The rebuilt file decrypts with block 0 replaced and 1 and 2 untouched. Then, `cmp` matches the file that we want for 122/122 and the flag.

Flag: `TFCCTF{cheating_is_the_only_way_to_get_a_job_in_2026}`
</details>
