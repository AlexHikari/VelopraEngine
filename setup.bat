@echo off
SETLOCAL

SET PROJECT_DIR=%~dp0
SET VCPKG_DIR=%PROJECT_DIR%vcpkg

IF NOT EXIST "%VCPKG_DIR%" (
    echo Cloning vcpkg into %VCPKG_DIR%
    git clone https://github.com/Microsoft/vcpkg.git "%VCPKG_DIR%"
    IF %ERRORLEVEL% NEQ 0 (
        echo Failed to clone vcpkg
        exit /b %ERRORLEVEL%
    )

    echo Bootstrapping vcpkg
    CALL "%VCPKG_DIR%\bootstrap-vcpkg.bat"
    IF %ERRORLEVEL% NEQ 0 (
        echo Failed to bootstrap vcpkg
        exit /b %ERRORLEVEL%
    )
) ELSE (
    echo vcpkg already installed
)

echo Installing dependencies
powershell -File "%PROJECT_DIR%install_dependencies.ps1" "%VCPKG_DIR%"

IF %ERRORLEVEL% NEQ 0 (
    echo Failed to install dependencies
    exit /b %ERRORLEVEL%
)

echo Dependencies installed successfully
echo Setup completed successfully
ENDLOCAL
