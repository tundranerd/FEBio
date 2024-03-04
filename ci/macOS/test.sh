#! /bin/bash
# Uncomment next line if not global on target machine
set -e

chmod +x cmbuild/bin/febio4

FEBIO_XML="$(dirname $0)/febio.xml"
FEBIO_DIR=./cmbuild/bin
FEBIO_LIB=./cmbuild/lib
FEBIO_BIN="${FEBIO_DIR}/febio4"

FEBIOHEAT=./febioheat/lib/libFEBioHeat.dylib
FEBIOCHEM=./febioheat/lib/libFEBioHeat.dylib

TESTSUITE=./TestSuite

if [[ ! -d $TESTSUITE ]]; then
	echo "Error: TestSuite was not located" >&2; exit 1
fi

if [[ -f "$FEBIOHEAT" ]]; then
    cp $FEBIOHEAT $FEBIO_LIB
fi

if [[ -f "$FEBIOCHEM" ]]; then
    cp $FEBIOCHEM $FEBIO_LIB
fi

cp $FEBIO_XML $FEBIO_DIR
./TestSuite/code/tools.py -r $FEBIO_BIN
