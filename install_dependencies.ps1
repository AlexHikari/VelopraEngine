param (
    [String]$VcpkgDir
)

$dependencies = @("opengl", "glew", "assimp", "glm", "qt5", "spdlog", "glfw3")

# Get the list of already installed packages
$installed = & "$VcpkgDir\vcpkg" list
if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed to retrieve list of installed packages"
    exit $LASTEXITCODE
}

foreach ($dep in $dependencies) {
    if ($installed -notcontains $dep) {
        Write-Host "Installing $dep..."
        & "$VcpkgDir\vcpkg" install $dep
        if ($LASTEXITCODE -ne 0) {
            Write-Error "Failed to install $dep"
            exit $LASTEXITCODE
        }
    } else {
        Write-Host "$dep is already installed."
    }
}
