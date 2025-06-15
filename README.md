This is my QMK configuration for the [TOTEM](https://github.com/GEIGEIGEIST/TOTEM) split keyboard.
I am using a vim friendly version of [Gallium](https://github.com/GalileoBlues/Gallium).
The other layers are inspired by [Pascal Getreuer](https://github.com/getreuer/qmk-keymap).

To flash first reset (press reset button twice) the left half and run:

```
qmk flash -kb totem -km default -bl uf2-split-left
```

Then reset the right controller and run:

```
qmk flash -kb totem -km default -bl uf2-split-right
```

For the visualization I use [keymap-drawer](https://github.com/caksoylar/keymap-drawer).
```
qmk c2json keymaps/default/keymap.c | keymap -c visualize/keymap-drawer-config.yaml parse -c 12 -q - > visualize/keymap.yaml
keymap -c visualize/keymap-drawer-config.yaml draw visualize/keymap.yaml > visualize/keymap.svg
```

![Visualization of the layout](./visualize/keymap.svg)
