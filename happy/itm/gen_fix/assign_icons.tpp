// Placeholder Icon Assigner
READ_SHORT 0x1c "type"
READ_ASCII 0x3a "inv_icon"
READ_ASCII 0x44 "gnd_icon"
READ_ASCII 0x58 "desc_icon"
SET "inv_exists" = 0
SET "gnd_exists" = 0
SET "desc_exists" = 0

PATCH_IF FILE_EXISTS_IN_GAME ~%inv_icon%.bam~ BEGIN
  SET "inv_exists" = 1
END
PATCH_IF FILE_EXISTS_IN_GAME ~%gnd_icon%.bam~ BEGIN
  SET "gnd_exists" = 1
END
PATCH_IF FILE_EXISTS_IN_GAME ~%desc_icon%.bam~ BEGIN
  SET "desc_exists" = 1
END

PATCH_IF ("%inv_exists%" = 0) BEGIN
  PATCH_IF ("%inv_icon%" STR_EQ "none") OR ("%inv_icon%" STR_EQ "") BEGIN
    PATCH_PRINT "HW90: %SOURCE_FILE% - Unassigned Inventory Icon! Assigning placeholder icon..."
  END ELSE
  BEGIN
    PATCH_PRINT "HW91: %SOURCE_FILE% - Non-existent Inventory Icon (%inv_icon%.BAM)! Assigning placeholder icon..."
  END
  WRITE_ASCII 0x3a ~IMISC6V~ #8
END
PATCH_IF ("%gnd_exists%" = 0) BEGIN
  PATCH_IF ("%gnd_icon%" STR_EQ "GCLCKC01") BEGIN
    PATCH_PRINT "HW92: %SOURCE_FILE% - Non-existent Ground Icon (%gnd_icon%.BAM)! Assigning GCLCK01.BAM..."
    WRITE_ASCII 0x44 ~GCLCK01~ #8
  END ELSE
  PATCH_IF ("%gnd_icon%" STR_EQ "_GPOTN01") OR
           ("%gnd_icon%" STR_EQ "GPOTN11") OR
           ("%gnd_icon%" STR_EQ "GPOTN41") OR
           ("%gnd_icon%" STR_EQ "PTION2KG") OR
           ("%gnd_icon%" STR_EQ "PTION2LG") OR
           ("%gnd_icon%" STR_EQ "PTION2MG") BEGIN
    PATCH_PRINT "HW93: %SOURCE_FILE% - Non-existent Ground Icon (%gnd_icon%.BAM)! Assigning GPOTN01.BAM..."
    WRITE_ASCII 0x44 ~GPOTN01~ #8
  END ELSE
  PATCH_IF ("%gnd_icon%" STR_EQ "ICRATE01") BEGIN
    PATCH_PRINT "HW94: %SOURCE_FILE% - Non-existent Ground Icon (%gnd_icon%.BAM)! Assigning GCRATE01.BAM..."
    WRITE_ASCII 0x44 ~GCRATE01~ #8
  END ELSE
  PATCH_IF ("%gnd_icon%" STR_EQ "none") OR ("%gnd_icon%" STR_EQ "") BEGIN
    PATCH_PRINT "HW95: %SOURCE_FILE% - Unassigned Ground Icon! Assigning placeholder icon..."
    WRITE_ASCII 0x44 ~GCRATE01~ #8
  END ELSE
  BEGIN
    PATCH_PRINT "HW96: %SOURCE_FILE% - Non-existent Ground Icon (%gnd_icon%.BAM)! Assigning placeholder icon..."
    WRITE_ASCII 0x44 ~GCRATE01~ #8
  END
END
PATCH_IF ("%desc_exists%" = 0) BEGIN
  PATCH_IF ("%desc_icon%" STR_EQ "none") OR ("%desc_icon%" STR_EQ "") BEGIN
    PATCH_PRINT "HW97: %SOURCE_FILE% - Unassigned Description Icon! Assigning placeholder icon..."
  END ELSE
  BEGIN
    PATCH_PRINT "HW98: %SOURCE_FILE% - Non-existent Description Icon (%desc_icon%.BAM)! Assigning placeholder icon..."
  END
  WRITE_ASCII 0x58 ~CMISC6V~ #8
END
