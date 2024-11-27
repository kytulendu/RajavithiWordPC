# Rajavithi Word PC

A recration of Rajavithi Word PC version 1.0 in C and Assembly.

Using any version of OpenWatcom C to compile.

All message is using [Kaset](https://github.com/kytulendu/libwordthai/blob/master/doc/Thai_character_code.md) character encoding.
The message can be edit using either CU-Writer (Prefer early 1.4x version or [ThaiWrite](https://github.com/kytulendu/TW) folk) or Rajavithi Word PC.
Keep in mind that Rajavithi Word PC and newer version of CU-Writer will save it's options at the end of file and will need to remove it before use.

All file will be using UTF-8 character encoding when possible. For files that have message in Kaset or have characters that have UTF-8 broke, the file will be in TIS-620 character encoding.
