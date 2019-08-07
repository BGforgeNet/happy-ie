//DLTCEP | Useless duration set in equipping effect

GET_OFFSET_ARRAY gl_fx ITM_V10_GEN_EFFECTS
PHP_EACH gl_fx AS i => fx_off BEGIN
  READ_BYTE (fx_off + 0xc) timing
  READ_LONG (fx_off + 0xe) duration
  PATCH_IF timing != 2 BEGIN
    PATCH_PRINT ~HW124: %SOURCE_FILE% - equipping effect with timing %timing%. Setting to WHILE_EQUIPPED=2.~
    WRITE_BYTE (fx_off + 0xc) 2
    WRITE_LONG (fx_off + 0xe) 0
  END
  PATCH_IF (timing = 2 AND duration != 0) BEGIN
    PATCH_PRINT ~HI38: %SOURCE_FILE% - equipping effect with useless duration %duration%. Setting to 0.~
    WRITE_LONG (fx_off + 0xe) 0
  END
END
