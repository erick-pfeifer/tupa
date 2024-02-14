#!/usr/bin/env python3
"""Presubmit checks script."""

import argparse
import logging
import os
import re
import sys
from pathlib import Path

import pw_cli.log
import pw_presubmit
from pw_presubmit import (PresubmitContext, cli, cpp_checks, format_code,
                          git_repo, inclusive_language, install_hook,
                          python_checks, todo_check)

__LOG = logging.getLogger(__name__)

PROJECT_ROOT = Path(os.environ['PROJECT_ROOT'])

REPOS = (PROJECT_ROOT, )

PATH_EXCLUSIONS = [
    re.compile(r'^.gitmodules'),
    re.compile(r'^src/bsp/atsame54n20a.*')
]

TODO_CHECK_PATTERN = re.compile(r'(?:\bTODO\(#issue-\d+(?:, ?b/\d+)*\).*\w)|'
                                r'(?:\bTODO: #issue-\d+(?:, ?b/\d+)* - )')

QUICK = (
    todo_check.create(TODO_CHECK_PATTERN),
    format_code.presubmit_checks(),
    inclusive_language.presubmit_check,
    cpp_checks.pragma_once,
)

# TODO(#issue-1971402255): Add more presubmit checks.
PROGRAMS = pw_presubmit.Programs(
    default=QUICK,
    quick=QUICK,
    full=QUICK,
)


def run(install: bool, exclude: list, **presubmit_args) -> int:
    """Runs presubmit checks. Installs git hook if necessary."""
    if install:
        install_hook.install_git_hook('pre-push',
                                      ['pw', 'presubmit', '--base', 'HEAD~1'],
                                      git_repo.root())
        __LOG.info('Presubmit checks are now installed as a git hook.')
        return 0

    exclude.extend(PATH_EXCLUSIONS)
    return cli.run(root=PROJECT_ROOT,
                   repositories=REPOS,
                   exclude=exclude,
                   **presubmit_args)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    cli.add_arguments(parser, PROGRAMS, 'default')
    parser.add_argument('--install',
                        action='store_true',
                        help='Install git hook for pre push operation.')

    return run(**vars(parser.parse_args()))


if __name__ == '__main__':
    pw.cli.log.install(logging.INF)
    sys.exit(main())
