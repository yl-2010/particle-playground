# Particle playground

Yan's sandbox for custom Zephyr on a Particle Argon. No Particle cloud, no Particle CLI, no Device OS.

Austin Zhu's firmware lives in [`austin/`](austin/). That folder is his [particle-zephyr-telemetry](https://github.com/az01-65/particle-zephyr-telemetry) tree (this GitHub repo is a fork of that). His README, toolchain notes, flash scripts, and prebuilt hexes are all in there.

## Layout

```
austin/     Austin's Zephyr apps, docs, tools, prebuilts
            including a D5 breadboard LED blink in blank_app
```

Add your own apps next to `austin/` as they show up. Do not dump new work into yanylevin.

## Blink the breadboard LED

The D5 change is in `austin/firmware/blank_app`. There is no prebuilt hex for it. Flashing `austin/prebuilt/argon_gateway.hex` runs Austin's mesh gateway, not the blink.

Build (after the Zephyr T2 workspace in `austin/docs/TOOLCHAIN.md`):

```bash
west build -b particle_argon -d /tmp/build_blank austin/firmware/blank_app
```

Then program that hex over SWD with OpenOCD. `austin/tools/flash.sh` is Austin's mass-erase + program path. First flash needs a CMSIS-DAP debugger (Particle Debugger) on the Argon's 10-pin SWD header. Argon micro-USB is power and serial only.

## Hardware on this Mac Studio

- Argon: data-capable micro-USB into the Studio (the board is micro-USB, the Mac is USB-C).
- Debugger: USB to the Studio, ribbon on the Argon SWD header. Pull the plastic plug if it is still in the header.
- LED: one leg on D5, other in the blue negative column (ground). Overlay is active-high for that. Put 220–330 Ω in series if it is not already there.

Onboard proof LED is `led1` (red status, active-low). `led0` does not visibly light.

## Flash without building

```bash
brew install openocd   # already on the Studio
./austin/tools/flash.sh argon --yes
```

That wipes Particle's bootloader. Yan asked for that.
