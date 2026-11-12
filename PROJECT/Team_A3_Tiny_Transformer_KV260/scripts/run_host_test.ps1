# PowerShell. Run from any directory with Python+NumPy and g++ on PATH.
$ErrorActionPreference = "Stop"
Set-Location (Join-Path $PSScriptRoot "..")
python reference/generate_vectors.py
if ($LASTEXITCODE -ne 0) { throw "Reference generation failed" }
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++11 -O2 -Wno-unknown-pragmas -Ihls hls/transformer_top.cpp hls/attention.cpp hls/transformer_layers.cpp hls/testbench.cpp -o build/team_a3_testbench.exe
if ($LASTEXITCODE -ne 0) { throw "C++ compile failed" }
& .\build\team_a3_testbench.exe data
if ($LASTEXITCODE -ne 0) { throw "Host tests failed" }
