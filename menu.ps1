# Computer Graphics Lab - Interactive Menu
# Requires: g++ with WinBGIm

$scriptDir = $PSScriptRoot
$includeDir = Join-Path $scriptDir "include"

function Compile-Run {
    param($num, $src, $desc)
    $exe = [System.IO.Path]::GetFileNameWithoutExtension($src) + ".exe"
    $exePath = Join-Path $scriptDir $exe

    Write-Host "`n=== Compiling: $desc ===" -ForegroundColor Cyan
    $srcPath = Join-Path $scriptDir $src

    if (-not (Test-Path $srcPath)) {
        Write-Host "[ERROR] Source file not found: $src" -ForegroundColor Red
        return
    }

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
        Read-Host "`nPress Enter to return to menu"
        return
    }

    Write-Host "[OK] Compiled successfully!" -ForegroundColor Green
    Write-Host "`n=== Running: $desc ===" -ForegroundColor Yellow
    Write-Host "(Close the graphics window when done)`n" -ForegroundColor Gray

    # Run the executable - for GUI apps use Start-Process and wait
    Start-Process -Wait -FilePath $exePath

    Write-Host "`n[Done] Execution finished." -ForegroundColor Green
    Read-Host "`nPress Enter to return to menu"
}

function Show-Menu {
    Clear-Host
    Write-Host "==============================================" -ForegroundColor Cyan
    Write-Host "  Computer Graphics & Multimedia System Lab" -ForegroundColor Cyan
    Write-Host "  CSE41P8" -ForegroundColor Cyan
    Write-Host "==============================================" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "  0. View Theory (README.md)" -ForegroundColor White
    Write-Host "  1. Study of I/O Devices (Theory only)" -ForegroundColor Gray
    Write-Host "  2. Line using Slope-Intercept Formula" -ForegroundColor White
    Write-Host "  3. Line using DDA Algorithm" -ForegroundColor White
    Write-Host "  4. Line using Bresenham's Algorithm" -ForegroundColor White
    Write-Host "  5. Circle using Midpoint Algorithm" -ForegroundColor White
    Write-Host "  6. Translation of Line & Triangle" -ForegroundColor White
    Write-Host "  7. Rotation of Line & Triangle" -ForegroundColor White
    Write-Host "  8. Scaling Transformation" -ForegroundColor White
    Write-Host "  9. 3D Rotation about Arbitrary Axis" -ForegroundColor White
    Write-Host " 10. Cohen-Sutherland Line Clipping" -ForegroundColor White
    Write-Host " 11. Sutherland-Hodgman Polygon Clipping" -ForegroundColor White
    Write-Host " 12. Bezier Curve" -ForegroundColor White
    Write-Host " 13. B-Spline Curve" -ForegroundColor White
    Write-Host " 14. Compile ALL experiments" -ForegroundColor Yellow
    Write-Host "  q. Quit" -ForegroundColor Red
    Write-Host ""
    $choice = Read-Host "Select experiment (0-14)"
    return $choice
}

$experiments = @(
    @{num=2;  src="exp02_slope_intercept.cpp";    desc="Slope-Intercept Line"},
    @{num=3;  src="exp03_dda_line.cpp";           desc="DDA Line Algorithm"},
    @{num=4;  src="exp04_bresenham_line.cpp";     desc="Bresenham's Line Algorithm"},
    @{num=5;  src="exp05_midpoint_circle.cpp";    desc="Midpoint Circle Algorithm"},
    @{num=6;  src="exp06_translation.cpp";        desc="2D Translation"},
    @{num=7;  src="exp07_rotation.cpp";           desc="2D Rotation"},
    @{num=8;  src="exp08_scaling.cpp";            desc="2D Scaling"},
    @{num=9;  src="exp09_3d_rotation.cpp";        desc="3D Rotation about Arbitrary Axis"},
    @{num=10; src="exp10_cohen_sutherland.cpp";   desc="Cohen-Sutherland Line Clipping"},
    @{num=11; src="exp11_sutherland_hodgman.cpp"; desc="Sutherland-Hodgman Polygon Clipping"},
    @{num=12; src="exp12_bezier.cpp";             desc="Bezier Curve"},
    @{num=13; src="exp13_b_spline.cpp";           desc="B-Spline Curve"}
)

# Start with theory compiled check
$theoryPath = Join-Path $scriptDir "README.md"
if (-not (Test-Path $theoryPath)) {
    Write-Host "[WARN] README.md (theory) not found!" -ForegroundColor Yellow
}

do {
    $choice = Show-Menu
    switch ($choice) {
        "0" {
            if (Test-Path $theoryPath) {
                Clear-Host
                Write-Host "=== Opening Theory Document ===" -ForegroundColor Cyan
                # Try to display in console with limited view
                Get-Content $theoryPath -TotalCount 50 | ForEach-Object { Write-Host $_ }
                Write-Host "`n[Theory is 300+ lines — open README.md in a text editor for full view]" -ForegroundColor Yellow
                Read-Host "`nPress Enter to return to menu"
            }
        }
        "1" {
            $ioPath = Join-Path $scriptDir "exp01_io_devices.md"
            if (Test-Path $ioPath) {
                Clear-Host
                Write-Host "=== Experiment 1: Input & Output Devices (Theory) ===" -ForegroundColor Cyan
                Get-Content $ioPath | ForEach-Object { Write-Host $_ }
                Read-Host "`nPress Enter to return to menu"
            }
        }
        "q" { Write-Host "Goodbye!" -ForegroundColor Cyan; break }
        "14" {
            Write-Host "`n=== Compiling ALL Experiments ===" -ForegroundColor Cyan
            foreach ($exp in $experiments) {
                $srcPath = Join-Path $scriptDir $exp.src
                if (-not (Test-Path $srcPath)) {
                    Write-Host "[SKIP] $($exp.src) not found" -ForegroundColor Yellow
                    continue
                }
                $exeName = [System.IO.Path]::GetFileNameWithoutExtension($exp.src) + ".exe"
                $exePath = Join-Path $scriptDir $exeName
                $gppArgs = @(
                    "-o", $exePath,
                    $srcPath,
                    "-I", $includeDir,
                    "-L", $includeDir,
                    "-lbgi", "-lgdi32", "-lcomdlg32", "-luuid", "-loleaut32", "-lole32"
                )
                $result = & "g++" $gppArgs 2>&1
                if ($LASTEXITCODE -eq 0) {
                    Write-Host "[OK] $($exp.desc)" -ForegroundColor Green
                } else {
                    Write-Host "[FAIL] $($exp.desc)" -ForegroundColor Red
                    $result | ForEach-Object { Write-Host "  $_" -ForegroundColor Red }
                }
            }
            Read-Host "`nPress Enter to return to menu"
        }
        default {
            $exp = $experiments | Where-Object { $_.num -eq $choice }
            if ($exp) {
                Compile-Run $exp.num $exp.src $exp.desc
            } else {
                Write-Host "[Invalid] Please enter 0-14 or q" -ForegroundColor Red
                Start-Sleep -Seconds 1
            }
        }
    }
} while ($choice -ne "q")
