# coffeehack

`coffeehack.ino` is the arduino/squirrel-code that runs the local interface to the machine's maintenance port. Run it on a Spark Photon. `webhook-coffee.json` is what you'll need to `particle webhook create` in order for the Photon's event trigger to cause a web requests to the API.

`test-app` shows how to get data out of the API (over DDP)

`reverse-engineering` has info on the machine, the v? files are EEPROM dumps.

(`jura.py` is an earlier attempt in python on a raspberry Pi.)
