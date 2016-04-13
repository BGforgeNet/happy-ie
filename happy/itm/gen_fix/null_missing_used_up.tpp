// Used Up Item Fixer
READ_ASCII 0x10 "used_itm"

PATCH_IF NOT ((FILE_EXISTS_IN_GAME ~%used_itm%.itm~) OR ("%used_itm%" STR_EQ "") OR ("%used_itm%" STR_EQ "none")) BEGIN
  PATCH_PRINT "%SOURCE_FILE% issue: Non-existent Used Up Item (%used_itm%.ITM)! Nulling..."
  WRITE_ASCII 0x10 ~NONE~ #8
END
