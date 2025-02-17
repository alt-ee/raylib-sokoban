# Building the project

These instructions are mainly intended as a reminder to myself on how to build the project from scratch.
I use nix flakes to create a dev shell, so these instructions should be pretty simple to follow for anyone else using flakes, but I make no promises.

1. Clone this repo
2. Create the directory `external` and unzip the releases for raylib-5.5 and raygui-4.0 into the directory. (This can probably be automated with a git submodule or even using nix? Something to look into.)
3. run `make build-main`

The executable will be created at `build/main`, and can also be run immediately after compilation by running `make run`
