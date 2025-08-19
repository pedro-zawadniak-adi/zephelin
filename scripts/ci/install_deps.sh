#!/bin/bash

# Copyright (c) 2025 Analog Devices, Inc.
# Copyright (c) 2025 Antmicro <www.antmicro.com>
#
# SPDX-License-Identifier: Apache-2.0

set -xeuo pipefail

if [ -z "${RENODE_VERSION:-}" ]; then
	echo "RENODE_VERSION is not set!"
	exit 1
fi

# install deps with apt
apt update -qq
apt install -yqq xxd gdb-multiarch mono-complete

# install deps with pip
pip install -r requirements.txt

# install recent flatbuffers-compiler
wget https://github.com/google/flatbuffers/releases/download/v25.2.10/Linux.flatc.binary.g++-13.zip -O flatc.zip
unzip flatc.zip -d /usr/bin && rm flatc.zip

# install Renode
wget -q "https://dl.antmicro.com/projects/renode/builds/${RENODE_VERSION}" -O renode.deb
dpkg -i renode.deb
rm renode.deb
