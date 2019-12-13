READ_LONG  0x64 "abil_off"
READ_SHORT 0x68 "abil_num"
READ_LONG  0x6a "fx_off"
READ_SHORT 0x70 "fx_num"
PATCH_IF ((abil_off > fx_off) AND (abil_num > 1)) BEGIN
  READ_ASCII abil_off ~eh~ ELSE ~fail~ (0x38 * abil_num)
  PATCH_IF (~%eh%~ STRING_EQUAL ~fail~) BEGIN
    WHILE ((~%eh%~ STRING_EQUAL ~fail~) AND (abil_num > 0)) BEGIN
      READ_ASCII abil_off ~eh~ ELSE ~fail~ (0x38 * abil_num)
      abil_num -= 1
    END
  END
  offset = abil_off
  value  = 0x38 * abil_num
  PATCH_PRINT "HI57: %SOURCE_FILE% - Restructuring - Unused Ability Structure found! Trimming %value% bytes from offset %offset%..."
  DELETE_BYTES offset value
  SOURCE_SIZE = SOURCE_SIZE - value
  abil_off = 0x72
  WRITE_LONG 0x64 abil_off
  WRITE_SHORT 0x68 abil_num
  fx_off = (0x72 + (0x38 * abil_num))
  WRITE_LONG 0x6a fx_off
  PATCH_IF !(~%eh%~ STRING_EQUAL ~fail~) BEGIN
    INSERT_BYTES abil_off (0x38 * abil_num)
    WRITE_ASCIIE abil_off ~%eh%~
  END
END ELSE PATCH_IF ((abil_off != 0x72) AND (abil_num = 0)) BEGIN
  abil_off = 0x72
  WRITE_LONG 0x64 abil_off
END
FOR (i1 = 0; i1 < (0x38 * abil_num); i1 += 0x38) BEGIN
  WRITE_SHORT (abil_off + i1 + 0x20) fx_num
  READ_SHORT (abil_off + i1 + 0x1e) cx
  fx_num += cx
END
PATCH_IF ((abil_off + (0x38 * abil_num)) < fx_off) BEGIN
  offset = abil_off + (0x38 * abil_num)
  value  = fx_off - ((abil_off + (0x38 * abil_num)))
  PATCH_PRINT "HI58: %SOURCE_FILE% - Restructuring - Unused Inter-structural Bytes found! Trimming %value% bytes from offset %offset%..."
  DELETE_BYTES offset value
  SOURCE_SIZE = SOURCE_SIZE - value
  fx_off = offset
  WRITE_LONG 0x6a %fx_off%
END
PATCH_IF (SOURCE_SIZE > (0x72 + (0x38 * abil_num) + (0x30 * fx_num))) BEGIN
  offset = 0x72 + (0x38 * abil_num) + (0x30 * fx_num)
  value  = SOURCE_SIZE - (0x72 + (0x38 * abil_num) + (0x30 * fx_num))
  PATCH_PRINT "HI59: %SOURCE_FILE% - Restructuring - Unused Trailing Bytes found! Trimming %value% bytes from offset %offset%..."
  DELETE_BYTES offset value
  SOURCE_SIZE = SOURCE_SIZE - value
END
