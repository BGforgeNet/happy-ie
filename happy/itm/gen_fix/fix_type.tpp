// Type Fixer
READ_SHORT 0x1c "type"

PATCH_IF ("%type%" = 39) OR ("%type%" = 40) OR ("%type%" = 42) OR ("%type%" = 50) OR ("%type%" = 55) OR ("%type%" = 59) BEGIN
  WRITE_SHORT 0x1c 0
  PATCH_PRINT "HI44: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Misc type..."
END
PATCH_IF ("%type%" = 41) OR ("%type%" = 47) OR ("%type%" = 49) OR ("%type%" = 53) BEGIN
  WRITE_SHORT 0x1c 12
  PATCH_PRINT "HI45: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Shield type..."
END
PATCH_IF ("%type%" = 44) BEGIN
  WRITE_SHORT 0x1c 17
  PATCH_PRINT "HI46: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Mace type..."
END
PATCH_IF ("%type%" = 56) OR ("%type%" = 71) BEGIN
  WRITE_SHORT 0x1c 9
  PATCH_PRINT "HI47: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Potion type..."
END
PATCH_IF ("%type%" = 57) OR ("%type%" = 69) BEGIN
  WRITE_SHORT 0x1c 20
  PATCH_PRINT "HI48: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Large Sword type..."
END
PATCH_IF ("%type%" = 58) BEGIN
  WRITE_SHORT 0x1c 36
  PATCH_PRINT "HI49: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Container type..."
END
PATCH_IF ("%type%" = 60) OR ("%type%" = 61) OR ("%type%" = 62) OR ("%type%" = 63) OR ("%type%" = 64) OR ("%type%" = 65) OR ("%type%" = 66) OR ("%type%" = 67) BEGIN
  WRITE_SHORT 0x1c 2
  PATCH_PRINT "HI50: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Armor type..."
END
PATCH_IF ("%type%" = 70) BEGIN
  WRITE_SHORT 0x1c 32
  PATCH_PRINT "HI51: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Cloak type..."
END
PATCH_IF ("%type%" = 72) BEGIN
  WRITE_SHORT 0x1c 7
  PATCH_PRINT "HI52: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Headgear type..."
END
PATCH_IF ("%type%" = 73) BEGIN
  WRITE_SHORT 0x1c 6
  PATCH_PRINT "HI53: %SOURCE_FILE% - Invalid Item Type (%type%)! Setting to Gauntlet type..."
END
