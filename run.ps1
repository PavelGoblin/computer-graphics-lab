param(
    [Parameter(Mandatory=$true)]
    [int]$Experiment
)

$scriptDir = $PSScriptRoot
$includeDir = Join-Path $scriptDir "include"

$map = @{
    2 = "exp02_slope_intercept.cpp"
    3 = "exp03_dda_line.cpp"
    4 = "exp04_bresenham_line.cpp"
    5 = "exp05_midpoint_circle.cpp"
    6 = "exp06_translation.cpp"
    7 = "exp07_rotation.cpp"
    8 = "exp08_scaling.cpp"
    9 = "exp09_3d_rotation.cpp"
    10 = "exp10_cohen_sutherland.cpp"
    11 = "exp11_sutherland_hodgman.cpp"
    12 = "exp12_bezier.cpp"
    13 = "exp13_b_spline.cpp"
}

if (-not $map.ContainsKey($Experiment)) {
    Write-Host "Usage: .\run.ps1 <experiment_number>" -ForegroundColor Yellow
    Write-Host "Valid: 2-13" -ForegroundColor Yellow
    exit 1
}

$src = $map[$Experiment]
$srcPath = Join-Path $scriptDir $src
$exeName = [System.IO.Path]::GetFileNameWithoutExtension($src) + ".exe"
$exePath = Join-Path $scriptDir $exeName

if (-not (Test-Path $srcPath)) {
    Write-Host "[ERROR] Source not found: $src" -ForegroundColor Red
    exit 1
}

Write-Host "=== Compiling Experiment $Experiment ===" -ForegroundColor Cyan
$gppArgs = @(
    "-o", $exePath,
    $srcPath,
    "-I", $includeDir,
    "-L", $includeDir,
    "-lbgi", "-lgdi32", "-lcomdlg32", "-luuid", "-loleaut32", "-lole32"
)
$result = & "g++" $gppArgs 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Host "[ERROR] Compilation failed:" -ForegroundColor Red
    $result | ForEach-Object { Write-Host $_ -ForegroundColor Red }
    exit 1
}

Write-Host "[OK] Running Experiment $Experiment..." -ForegroundColor Green
Start-Process -Wait -FilePath $exePath
