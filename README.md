this is a basic qmk userspace that uses a wrapper and a little bit of custom code in order to build firmwares in github actions

it is tied to master qmk/qmk_firmware

it has a single keymap corne

it has a somewhat basic wrapper


repo layout:
the majority of the keymap work is done in `keymaps/<boardname>.h
the ridingintraffic.c/h files are the custom code and anything special that needs to be used by the keymaps.

Flow:
 - github actions starts up.
 - checks out qmk firmware repo
 - checkout submodules IE (make git submodules - but done the git local way)
 - checkous out the userspace repo and then copies them to the `qmk_firmware/users/<github_username>`  folder
 - runs a build that references the json layout file in the userspace folder

config flow:
 - config.h identifies the keymap file to include
 - wrappers.h keymap templates that are shared amongst keymaps
   - keymaps/<keymap_name>.h the setup of the keymap itself
 - ridingintraffic.c - custom qmk code
 - ridingintraffic.h - custom qmk config
 - rules.mk qmk rules


