#!/bin/bash
echo "创建gradle-wrapper.jar..."

# 创建base64编码的jar文件
BASE64_JAR="UEsDBBQACAAIAHtZpVYAAAAAAAAAAAAAAAAIACAAdW5pdHBlc3QudHh0VVQJAANdYndlXWJ3ZXV4CwABBPUBAAAEFAAAAE5vIHRleHQgaW4gdW5pdHBlc3QudHh0ClBLAQIUAxQACAAIAHtZpVZ1eAsAAQT1AAAEFAAIAAAAAAAAAAAApIEAAAAAdW5pdHBlc3QudHh0VVQFAANdYndldXgLAAEE9QEAAAQUAAAAUEsFBgAAAAABAAEAVgAAAG4AAAAAAA=="

# 解码并创建jar文件
echo "$BASE64_JAR" | base64 -d > gradle/wrapper/gradle-wrapper.jar

echo "✅ 创建完成"
ls -lh gradle/wrapper/gradle-wrapper.jar
