function build ($Src1, $Src2) {
    if (Test-Path ".\build") {
        Write-Host "Removing existing '.\build' directory..." -ForegroundColor Yellow
        Remove-Item -Path ".\build" -Recurse -Force -ErrorAction SilentlyContinue
    }

    if (-not (Test-Path ".\build")) {
        Write-Host "Creating fresh '.\build' directory..." -ForegroundColor Green
        New-Item -ItemType Directory -Path ".\build" -Force | Out-Null
    }

    Write-Host "Searching for files in '$Src1' and '$Src2'..." -ForegroundColor Gray
    $Files = Get-ChildItem -Path "$Src1", "$Src2" -Recurse -File -ErrorAction SilentlyContinue

    foreach ($File in $Files) {
        Write-Host "Copying: $($File.Name) -> .\build\" -ForegroundColor DarkGray
        Copy-Item -Path $File.FullName -Destination ".\build" -Force -ErrorAction SilentlyContinue
    }

    if (Test-Path ".\build\main.cpp") {
        Write-Host "Renaming 'main.cpp' to 'build.ino'..." -ForegroundColor Magenta
        Rename-Item -Path ".\build\main.cpp" -NewName "build.ino" -Force -ErrorAction SilentlyContinue
    }

    Write-Host "--- Build complete ---" -ForegroundColor Cyan
}

build ".\include" ".\src"