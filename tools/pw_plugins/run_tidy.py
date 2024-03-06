#!/usr/bin/env python3
"""Runs clang-tidy via manual compile command generation and run-clang-tidy."""

import logging
import os
import sys
import subprocess
from pathlib import Path

import pw_cli.log

__LOG = logging.getLogger(__name__)

FILE_LIST = ['src/main.cc', 'src/app/.*', 'src/pigweed_backends/.*']


def main() -> int:
    __LOG.info('Running bazel target to generate compiler commands json file.')
    command = ['bazel', 'run', '//:compile_commands_device']
    process = subprocess.run(command, check=True)
    if process.returncode != 0:
        __LOG.error('Failed to run bazel command to generate json script.')
        sys.exit(process.returncode)

    command = ['run-clang-tidy', '-use-color=1'] + FILE_LIST

    __LOG.info(f'Running clang-tidy: {command}')
    process = subprocess.run(command, check=True)
    if process.returncode != 0:
        __LOG.error('Failed to run clang-tidy.')
        sys.exit(process.returncode)

    sys.exit(0)
