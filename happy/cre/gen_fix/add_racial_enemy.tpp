READ_BYTE 0x273 class
PATCH_IF class = 12 OR class = 18 BEGIN //ranger, cleric/ranger
  READ_BYTE 0x241 hated_race
  PATCH_IF hated_race = 0xff OR hated_race = 0 BEGIN
    PATCH_PRINT ~HW7: %SOURCE_FILE% - ranger without a racial enemy. Selecting gibberling.~
    WRITE_BYTE 0x241 109 //gibberling
  END
END
