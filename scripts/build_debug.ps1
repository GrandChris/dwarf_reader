
if(-Not (Test-Path build/compile_commands.json)) {
    scripts/cmake_configure.ps1
}

cmake --build ./build --config debug