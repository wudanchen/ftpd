# ftpd
基于ace 的简单ftpd服务器

编译和使用简单说明：
1. mkdir build
2. cd build
3. 编译debug版本：cmake -DCMAKE_BUILD_TYPE=Debug ../
   编译release版本：cmake -DCMAKE_BUILD_TYPE=Release ../
4. make
5. debug版本编译生成可执行文件放在ftpd/release/linux/debug/下的ftpserver
   release版本编译生成的可执行文件放在ftpd/release/linux/release/下的ftpserver
   gtest 生成的测试执行文件 'gtest_*' 放在build/gtest下

6. 执行：./ftpserver PORT  例如，./ftpserver 8080
