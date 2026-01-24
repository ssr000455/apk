#!/bin/bash
set -e

echo "=== Android构建脚本 ==="

# 检查必要文件
if [ ! -f "app/build.gradle" ]; then
    echo "错误：缺少app/build.gradle"
    exit 1
fi

# 创建最简单的gradlew
cat > gradlew << 'SCRIPT'
#!/bin/bash
echo "使用系统gradle..."
exec gradle "$@"
SCRIPT
chmod +x gradlew

echo "✅ 准备完成"
