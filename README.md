# cryptography
密码学实验代码

各个文件的解释：

### aes

`aes.cpp`将`passage.txt`文件加密，加密结果写入`encode.txt`

`aes_decode.cpp`将`encode.txt`文件解密，揭秘结果写入`decode.txt`

这两个文件主要是用于验证aes的实现是否正确

`setPassword.cpp`以输入的密码作为密钥对`word.txt`中的文件进行加密，结果存入`passwor_decode.txt`中

`login.cpp`以输入的密码作为密钥对`word.txt`中的文件进行加密，与`password_decode.txt`进行比较，判断密码是否正确

这两个文件主要是模仿linux登录的过程

### rsa

`getBigPrime.py`生成两个大素数$p,q$，计算$n$，选定$e$，计算$d$，将公钥$n,e$存到`public.txt`中，将私钥$p,q,d$存到`secret.txt`中

`rsa.py`读取公钥，对`passage.txt`进行加密，结果存入`rsa_encode.txt`

`rsa_decode.py`读取私钥，对`rsa_encode.txt`进行解密，结果存入`rsa_decode.txt`





代码结构不是很好 可能不久的将来会优化一下结构+增加代码注释
