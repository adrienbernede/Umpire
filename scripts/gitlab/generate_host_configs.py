#!/usr/bin/env python3

import json
import os
import subprocess
from string import digits
import sys


def cmd_exe(cmd,ret_output=False,echo=False):
    """
    Helper for executing shell commands.
    """
    if echo:
        print("[cmd_exe: {}]".format(cmd))
    if ret_output:
        p = subprocess.Popen(cmd,
                             shell=True,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        out = p.communicate()[0]
        out = out.decode('utf8')
        return p.returncode,out
    else:
        return subprocess.call(cmd,shell=True)


def get_machine_name():
    """
    Use hostname and strip digit to get machine name
    """
    cmd = "hostname"
    res, out = cmd_exe(cmd, ret_output=True)

    if res != 0:
        print("[ERROR]: '{}' call failed".format(cmd))
        sys.exit(-1)

    hostname=out.strip(digits).strip()

    if not hostname:
        print("[ERROR]: hostname is empty")
        sys.exit(-1)

    return hostname


def get_system_type():
    """
    Use environment variable to get system type
    """
    sys_type = os.environ.get('SYS_TYPE')

    if not sys_type:
        print("[ERROR]: sys_type is empty")
        sys.exit(-1)

    return sys_type


# Main
machine = get_machine_name()
sys_type = get_system_type()

with open('scripts/gitlab/list_of_specs.json') as f:
    specs_data = json.load(f)

    print(specs_data[sys_type][machine])

