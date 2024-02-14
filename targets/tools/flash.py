"""Script program target over openocd"""

import subprocess

from rules_python.python.runfiles import runfiles
from serial.tools import list_ports

_BINARY_PATH = "tupa/app.elf"
_OPENOCD_PATH = "openocd/bin/openocd"
_OPENOCD_CONFIG_PATH = "openocd/scripts/board/microchip_same54_xplained_pro.cfg"

# Vendor ID and model ID.
_VENDOR_ID = 0x03eb
_PRODUCT_ID = 0x2111


def get_board_serial() -> str:
    for dev in list_ports.comports():
        if dev.vid == _VENDOR_ID and dev.pid == _PRODUCT_ID:
            return dev.serial_number

    raise IOError("Failed to detect connected board")


def flash(board_serial):
    r = runfiles.Create()
    openocd = r.Rlocation(_OPENOCD_PATH)
    binary = r.Rlocation(_BINARY_PATH)
    openocd_cfg = r.Rlocation(_OPENOCD_CONFIG_PATH)

    print(f"Board Serial: {board_serial}")
    print(f"binary Rlocation is: {binary}")
    print(f"openocd Rlocation is: {openocd}")
    print(f"openocd config Rlocation is: {openocd_cfg}")

    assert binary is not None
    assert openocd_cfg is not None
    # " \"program build/E54ServoChar.elf verify\" -c \"reset halt\" -c shutdown"
    subprocess.check_call(
        [
            openocd,
            "-f",
            f"{openocd_cfg}",
            "-c",
            f"program {binary} reset exit",
            # "-c",
            # "adapter speed 4000",
            # "-c",
            # "bindto 0.0.0.0",
        ], )


if __name__ == "__main__":
    flash(get_board_serial())
