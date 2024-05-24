#!/usr/local/bin/python3
import os
import sys
import shutil



script_file_path = sys.argv[0]
print("script_file_path: %s" % script_file_path)

script_file_dir = os.path.abspath(os.path.dirname(script_file_path))
print("script_file_dir: %s" % script_file_dir)
library_root = script_file_dir

current_dir = os.path.abspath(os.curdir)
print("current_dir: %s" % current_dir)

boost_root_dir = os.path.join(current_dir, "boost_1_80_0")
print("boost_root_dir: %s" % boost_root_dir)


def print_step(step_name):
    sep = "*" * 80
    space_count = int((80 - len(step_name) - 10) / 2)
    step = "*" * 5 + " " * space_count + step_name + " " * space_count + "*" * 5
    print(sep)
    print(step)
    print(sep)


def check_root_dir():
    print("current path: %s" % current_dir)
    if script_file_dir != current_dir:
        print("current_path should be %s" % script_file_dir)
        exit(1)


def build_boost():
    os.chdir(boost_root_dir)
    print_step("build_boost")
    if os.name == "nt":
        boost_bootstrap_path = os.path.join(boost_root_dir, "bootstrap.bat")
        boost_b2_path = os.path.join(boost_root_dir, "b2.exe")
    else:
        boost_bootstrap_path = os.path.join(boost_root_dir, "bootstrap.sh")
        boost_b2_path = os.path.join(boost_root_dir, "b2")

    ret = os.system(boost_bootstrap_path)
    if ret != 0:
        print("run %s with ret code %d" % (boost_bootstrap_path, ret))
        exit(1)

    if not os.path.exists(boost_b2_path):
        print("%s should exist!" % boost_b2_path)
        exit(1)

    # https://www.boost.org/doc/libs/1_83_0/more/getting_started/windows.html
    boost_install_path = os.path.join(boost_root_dir, "Installed")
    ret = os.system("%s install --prefix=%s" % (boost_b2_path, boost_install_path))
    if ret != 0:
        print("build boost fail!")
        exit(1)
    os.chdir(library_root)


def main():
    check_root_dir()
    build_boost()


if __name__ == "__main__":
    main()
