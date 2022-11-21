#!/bin/bash

set -e

SCRIPT_PATH=$(dirname "$(realpath -s "$0")")

if [ -z "$1" ]; then
    echo "Usage: $0 <path>"
    exit 1
fi
INSTALL_PATH="$1"

"$SCRIPT_PATH/bootstrap.sh" --show-libraries > /dev/null
"$SCRIPT_PATH/b2" tools/bcp/ -j4
mkdir "$INSTALL_PATH"
"$SCRIPT_PATH/dist/bin/bcp" boost/program_options.hpp boost/filesystem.hpp boost/crc.hpp boost/functional/hash.hpp build "$INSTALL_PATH"
