# Read Photo-resistor

This demo explores setting up an I2C connection between an ATtiny85 and a Particle Photon by:

- Taking analog readings from a photo-resistor with ATtiny85
- Converting reading into a byte value with ATtiny85
- Setting up an I2C bus connection
- Sending the current light reading on request with Photon
- Publishing the light reading to Particle Cloud with Photon

### Schematic

![Schematic](https://raw.githubusercontent.com/larryschirmer/TinyWire/lib/add-reRef-files/examples/read_photoresistor/photon-attiny85-pr-i2c.png)

### Contents

- ATtiny85 Code: `attiny85_read_photoresistor.ino`
- Particle Photon Code: `photon_read_i2c.ino`

### Usage

1. Install Library

The main repository is setup to be importable as an Arduino IDE library. Save this repository as a `.zip` and import using Arduino's dropdown menu by:

```
> Arduino > Sketch > Include Library > Add .ZIP Library
```

2. Flash ATtiny85 sketch

Open `attiny85_read_photoresistor.ino` or copy its contents into the Arduino IDE.

You may need to add the imported library by:

```
> Arduino > Sketch > Include Library
```

Then select the newly added library under `Contributed Libraries`.

This will prepend the library headers a second time. Be sure to remove

```
#include <usiTwiSlave.h>
```

and include

```
#include <TinyWireSlave.h>
```

once.

To flash the ATtiny85, I used the Tiny AVR Programmer. The [Tiny AVR Programmer Hookup Guide](https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/) is a great place to start if you need help using this board to flash this sketch.

3. Flash Particle Photon

Open a [build.particle.io](build.particle.io) sketch and copy `photon_read_i2c.ino` into editor. If you need help getting started with the Photon, checkout Particle's [Quick Start Guide](https://docs.particle.io/quickstart/photon/). If you need help with Particle's online IDE, they've got you covered there too. [Web IDE (Build Tutorial)](https://docs.particle.io/tutorials/developer-tools/build/photon/)

4. Wire Up Prototype and Add Power

After the photon connects to wifi, it will begin to request readings from the ATtiny85. There are two ways to interact with this prototype. 

1. The onboard LED: The LED will light up when there is less light and turn off when there is more light (much like a night light). This means that the ATtiny85 is converting the voltage difference into an analog reading properly. 
2. [Particle's Devices Console](https://console.particle.io/devices): After selecting the photon from the list of claimed devices, the photon should be logging events in the details page. The expected value will be between 0 and 255 (0 - darkest, 255 lightest).

![example event logs](https://raw.githubusercontent.com/larryschirmer/TinyWire/lib/add-reRef-files/examples/read_photoresistor/example_event_logs.png)

Sources/Resources:

- https://docs.particle.io/datasheets/wi-fi/photon-datasheet/
- https://docs.particle.io/reference/device-os/firmware/photon/#particle-publish-
- https://github.com/DzikuVx/attiny_photoresistor_i2c
- https://openhomeautomation.net/cloud-data-logger-particle-photon
-
