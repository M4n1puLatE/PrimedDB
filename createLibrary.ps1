param([string]$ModuleName,[string]$model)
$exists = Test-Path -Path $ModuleName
if($model -eq "force" -and $exists)
{
    Remove-Item -Path $ModuleName -Force -Recurse
}
# 创建目录
New-Item -ItemType Directory -Path "$ModuleName/src"
New-Item -ItemType Directory -Path "$ModuleName/include"

# 生成 CMakeLists.txt
$cmakeContent = @"
project("$ModuleName")

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")

# 如果是库：
add_library("$ModuleName" STATIC `${SOURCES})
target_include_directories("$ModuleName" PUBLIC include)
"@

Set-Content -Path "$ModuleName/CMakeLists.txt" -Value $cmakeContent

Write-Host "Module '$ModuleName' created! Remember to add 'add_subdirectory($ModuleName)' in root CMakeLists.txt"

$mainSource = @"
#include <iostream>
int main()
{
    std::cout << "This is $ModuleName" << std::endl;
    return 0;
}
"@

Set-Content -Path "$ModuleName/src/main.cpp" -Value $mainSource