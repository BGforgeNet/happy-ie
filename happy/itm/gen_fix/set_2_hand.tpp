// 2-handed Flag Setter
READ_BYTE  0x18 "flags"
READ_ASCII 0x22 "anim" (2)

PATCH_IF (("%anim%" STR_EQ "BW") OR //bow
          ("%anim%" STR_EQ "CB") OR //crossbow
          ("%anim%" STR_EQ "HB") OR //halberd
          ("%anim%" STR_EQ "QS") OR //quarterstaff
          ("%anim%" STR_EQ "S2") OR //2-handed sword
          ("%anim%" STR_EQ "SP")) AND //spear
         (("%flags%" BAND 0b00000010) = 0b00000000) BEGIN //2-handed
  PATCH_PRINT "%SOURCE_FILE% issue: Item needs to be 2-handed (%anim% anim) to prevent crash!"
  WRITE_BYTE 0x18 ("%flags%" BOR 0b00000010)
END
