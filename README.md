# A UPS bridge for Netstar 800/1000/1250

It uses a non-standard DB9 communication protoocol, which means we need a way to bridge the raw I/O to the PC, to do this I've used what I had on hand which is an old DigiSpark (Tiny).

The toolchain is a bit outdated but usable, but I've added an `config.sh` which configures `arduino-cli` to add it, then it can be uploaded with `upload.sh`.


## Usage
Make sure the Digispark is connected correctly to the DB9 connector, and program it using `upload.sh`.

Then run `python3 ups_man.py` (will require pyserial), if all is well you will see `\x08` repeatedly coming through the terminal.

If you wish you can make it a service so it runs on startup. 

The default behaviour is to shutdown after 6 minutes in case of mains failure, and 30s in case of low battery. You can change this inside `ups_main.py` (it's very smol).
