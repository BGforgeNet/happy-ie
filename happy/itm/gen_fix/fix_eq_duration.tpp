GET_OFFSET_ARRAY gen_fx ITM_V10_GEN_EFFECTS
PHP_EACH gen_fx AS i => fx_off BEGIN
  READ_BYTE (fx_off + 0xc) timing
  READ_LONG (fx_off + 0xe) duration
  PATCH_IF timing != 2 BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: equipping effect with timing %timing%. Correcting.~
    WRITE_BYTE (fx_off + 0xc) 2
    WRITE_LONG (fx_off + 0xe) 0
  END
  PATCH_IF (timing = 2 AND duration != 0) BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: equipping effect with duration %duration%. Correcting.~
    WRITE_LONG (fx_off + 0xe) 0
  END
END
