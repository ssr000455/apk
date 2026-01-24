#!/bin/bash
set -e

echo "=== 直接使用Gradle ==="

# 检查是否已安装gradle
if ! command -v gradle &> /dev/null; then
    echo "安装Gradle 8.5..."
    # 在GitHub Actions中会自动处理
    echo "在GitHub Actions中会通过工作流安装"
fi

# 直接调用gradle
exec gradle "$@"
