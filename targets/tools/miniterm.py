"""Spin up a miniterm for talking to the board."""

from serial.tools import miniterm

if __name__ == "__main__":
    miniterm.main(default_baudrate=115200)
