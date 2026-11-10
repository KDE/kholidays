#!/usr/bin/env python
#
# SPDX-FileCopyrightText: Allen Winter <winter@kde.org>
# SPDX-License-Identifier: LGPL-2.0-or-later
#
"""
Test for syntax problems in the plan2 holiday files
"""

# takes 1 argument:
# - full path to the testholidayregion program

import os
import subprocess
import sys

os.environ['QT_LOGGING_RULES'] = '*.debug=true'

try:
    prog = sys.argv[1]
except IndexError:
    print(f'Usage: {os.path.basename(sys.argv[0])} TESTPROGRAM_PATH')
    sys.exit(1)

errors = 0
cmd = f'{prog} -maxwarnings 0'
try:
    with subprocess.Popen(
        cmd.split(),
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
        encoding='latin-1',  # windows doesn't like utf-8
    ) as process:
        for line in process.stdout:
            if 'syntax error' in line:
                print(line.rstrip())
                errors = errors + 1
except FileNotFoundError as e:
    print(f'test program {prog} cannot be found: {str(e)}')
    sys.exit(1)
except PermissionError as e:
    print(f'test program {prog} cannot be executed: {str(e)}')
    sys.exit(1)

if errors:
    print(f'Syntax Errors Encountered: {str(errors)}')
    sys.exit(1)
sys.exit(0)
