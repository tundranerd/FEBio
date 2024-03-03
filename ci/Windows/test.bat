call "%ONEAPI_ROOT%\setvars.bat" --force
python ci\test-suite\nightly.py
if %errorlevel% neq 0 exit /b %errorlevel%
