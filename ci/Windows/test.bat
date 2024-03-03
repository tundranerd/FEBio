call "%ONEAPI_ROOT%\setvars.bat" --force
FEBIO_TEST_BIN=./cmbuild/bin/febio4  python ./TestSuite/code/tools.py -r
