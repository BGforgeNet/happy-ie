// Enchantment Fixer
READ_BYTE  0x18 "flags"
READ_LONG  0x60 "enchantment"

PATCH_IF (("%enchantment%" > 0) AND (("%flags%" BAND 0b01000000) != 0b01000000)) BEGIN
  PATCH_PRINT "%SOURCE_FILE% issue: Item is enchanted but not magical! Setting magical flag..."
  WRITE_BYTE 0x18 ("%flags%" BOR 0b01000000)
END
