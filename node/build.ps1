function build ($Src1, $Src2) {
    if (-not (Test-Path ".\build")) {
        New-Item -ItemType Directory -Path ".\build" -Force | Out-Null
    }

    $Files = Get-ChildItem -Path "$Src1", "$Src2" -Recurse -File -ErrorAction SilentlyContinue

    foreach ($File in $Files) {
        Copy-Item -Path $File.FullName -Destination ".\build" -Force -ErrorAction SilentlyContinue
    }

    if (Test-Path ".\build\src.ino") {
        Rename-Item -Path ".\build\src.ino" -NewName "build.ino" -Force -ErrorAction SilentlyContinue
    }
}

build ".\include" ".\src"