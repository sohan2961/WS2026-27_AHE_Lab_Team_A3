$ErrorActionPreference = "Stop"
Set-Location (Resolve-Path (Join-Path $PSScriptRoot ".."))
python reference/generate_vectors.py
if ($LASTEXITCODE -ne 0) { throw "Python reference failed" }
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++11 -O2 -Wall -Wextra -Wno-unknown-pragmas -Ihls hls/attention_top.cpp hls/attention.cpp hls/attention_testbench.cpp -o build/nexys_attention_test.exe
if ($LASTEXITCODE -ne 0) { throw "C++ build failed" }
& .\build\nexys_attention_test.exe data
if ($LASTEXITCODE -ne 0) { throw "Attention test failed" }
