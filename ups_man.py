#!/usr/bin/env python3

import serial
import time
import os

import serial.tools.list_ports

# USB VID:PID=16D0:087E LOCATION=3-4.3:1.0

if __name__ == '__main__':
    for port in serial.tools.list_ports.comports():
        if port.pid == 2174 and port.vid == 5840:
            port_path = port.device
            break
    else:
        raise RuntimeError("No appropriate USB-serial found (is digispark plugged in?)")

    flags = {'low_bat': 1, 'main_failure': 2, 'ups_shutdown': 4}
    state = {'low_bat': None, 'main_failure': None, 'ups_shutdown': None}
    delay_actions = {'main_failure': (5*60, 'shutdown +1'), 'low_bat': (30, 'shutdown now'), 'ups_shutdown': (0.5, 'shutdown now')}
    with serial.Serial(port_path, 115200, timeout=1) as ser:
        while True:
            try:
                ser.write(b'\0')  # UPS bridge will respond to each byte with status byte
                char = ser.read()

                print(char)
                if not char:
                    time.sleep(0.1)
                    continue

                char = char[0]
                for k, flag in flags.items():
                    if char & flag == flag:
                        print(f'Got flag for {k}')
                        # Set, no update
                        state[k] = state.get(k, time.monotonic())
                    else:
                        # Clear
                        state[k] = None

                for k, (delay, action) in delay_actions.items():
                    if (ts := state.get(k)) is not None:
                        if time.monotonic() - ts > delay:
                            os.system(action)

                time.sleep(0.05)
            except serial.SerialTimeoutException:
                # TODO: Missing UPS conn what now?
                raise
