BOOTMAGIC_ENABLE = yes
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE   = yes
COMMAND_ENABLE     = no
TAP_DANCE_ENABLE = yes
UNICODE_ENABLE = yes
WPM_ENABLE = yes
EXTRAKEY_ENABLE = yes
SRC += ridingintraffic.c
CAPS_WORD_ENABLE = yes


ifeq ($(strip $(USE_SECRETS)), yes)
	ifneq ("$(wildcard $(USER_PATH)/secrets.c)", "")
		SRC += rotary_lock.c secrets.c
	else
		OPT_DEFS += -DNO_SECRETS
	endif
else
	OPT_DEFS += -DNO_SECRETS
endif


# Corne CRKBD
ifeq ($(strip $(KEYBOARD)), crkbd/rev1)

endif

# planck
ifeq ($(strip $(KEYBOARD)), planck/rev6)
        STENO_ENABLE = yes
	STENO_PROTOCOL = geminipr
endif
# planck
ifeq ($(strip $(KEYBOARD)), fingerpunch/sweeeeep)
        PIN_COMPATIBLE=elite_c
endif
