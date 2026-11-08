# PasswordlessChecks

| | |
|---|---|
| Event | MetaCTF October 2026 Flash CTF |
| Category | rev |
| Points | 300 |
| Solves at capture | 76 |
| Status | solved |

> This challenge was definitely not made just to announce the fact I got a new Xbox controller.

Files: [`passwordless-checks.zip`](handout/passwordless-checks.zip)

<details>
<summary><b>Solution</b></summary>

The game has one event, and it saves whatever name you type without checking it. The flag is that 16-character name, typed on a controller in the USB capture.

## Recon

It's an RPG Maker VX game. `Game.rgss2a` uses the version 1 cipher, seeded with `0xDEADCAFE` and stepped by `key = key * 7 + 3`. It decrypts to `Data/*.rvdata` Ruby marshal dumps.

## The map event

`Data/Map001.rvdata` has one Autorun event. Its only command is `C303`, Name Input Processing, for actor 1 with a 16-character limit.

## Decoding the controller

The controller is an Xbox Wireless Controller, VID `045e` and PID `0b12`. In each GIP input report (type `0x20`), byte 4 holds the face buttons and byte 5 the D-pad. The D-pad walks the 10-column, 9-row `Window_NameInput` ENGLISH grid from index 0, and X picks a letter. This game's grid has different digit rows from the VX default, so I copied the table from its scripts.

```
decoded name: Nbu8W32GsvbSNSNS
```

## Reproduce

    CTF_LOCAL=1 ctf-python solve/solve.py

The script replays the presses from `capture.pcapng` on the grid.

Flag: `MetaCTF{Nbu8W32GsvbSNSNS}`

</details>
