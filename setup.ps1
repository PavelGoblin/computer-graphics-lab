# Computer Graphics Lab - Environment Setup Script
Write-Host "=== Computer Graphics Lab Setup ===" -ForegroundColor Cyan

# Step 1: Check for g++
$gpp = (Get-Command "g++" -ErrorAction SilentlyContinue).Source
if (-not $gpp) {
    Write-Host "[ERROR] g++ not found in PATH!" -ForegroundColor Red
    Write-Host "Install MinGW-w64 from: https://www.mingw-w64.org/" -ForegroundColor Yellow
    Write-Host "Or install via: winget install -e --id MSYS2.MSYS2" -ForegroundColor Yellow
    Write-Host "Then: pacman -S mingw-w64-ucrt-x86_64-gcc" -ForegroundColor Yellow
    exit 1
}
Write-Host "[OK] g++ found at: $gpp" -ForegroundColor Green

# Step 2: Copy graphics headers if needed
$parentHeaders = Join-Path (Get-Item $PSScriptRoot).Parent.FullName "graphics.h"
$parentWinBgi = Join-Path (Get-Item $PSScriptRoot).Parent.FullName "winbgim.h"
$parentLib = Join-Path (Get-Item $PSScriptRoot).Parent.FullName "libbgi.a"

$includeDir = Join-Path $PSScriptRoot "include"
if (-not (Test-Path $includeDir)) {
    New-Item -ItemType Directory -Path $includeDir -Force | Out-Null
}

if (Test-Path $parentHeaders) {
    Copy-Item $parentHeaders (Join-Path $includeDir "graphics.h") -Force
    Write-Host "[OK] Copied graphics.h" -ForegroundColor Green
} else {
    Write-Host "[WARN] graphics.h not found in parent directory" -ForegroundColor Yellow
}

if (Test-Path $parentWinBgi) {
    Copy-Item $parentWinBgi (Join-Path $includeDir "winbgim.h") -Force
    Write-Host "[OK] Copied winbgim.h" -ForegroundColor Green
} else {
    Write-Host "[WARN] winbgim.h not found in parent directory" -ForegroundColor Yellow
}

if (Test-Path $parentLib) {
    Copy-Item $parentLib (Join-Path $includeDir "libbgi.a") -Force
    Write-Host "[OK] Copied libbgi.a" -ForegroundColor Green
} else {
    Write-Host "[WARN] libbgi.a not found in parent directory" -ForegroundColor Yellow
}

Write-Host "`n=== Setup Complete ===" -ForegroundColor Cyan
Write-Host "Run '.\menu.ps1' to start the interactive lab menu." -ForegroundColor Green
