import os
import sys
import subprocess

if __name__ == "__main__":
    # Call premake
    subprocess.run(("./bin/premake5-windows.exe", "vs2022"))
