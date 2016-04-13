// Ability Icon Assigner
READ_ASCII 0x3a "inv_icon"
READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0

PATCH_IF (abil_off > 0x71) BEGIN
  FOR (index = 0; index < abil_num; index = index + 1) BEGIN
    READ_BYTE  ("%abil_off%" +        (0x38 * "%index%")) "abil_type"
    READ_ASCII ("%abil_off%" + 0x04 + (0x38 * "%index%")) "abil_icon"
    PATCH_IF NOT (FILE_EXISTS_IN_GAME ~%abil_icon%.bam~) AND ("%abil_type%" > 0) BEGIN
      PATCH_IF ("%abil_icon%" STR_EQ "none") OR ("%abil_icon%" STR_EQ "") BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% has no icon assigned! Assigning Inventory Icon (%inv_icon%.BAM)..."
      END ELSE
      BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% has a non-existent icon (%abil_icon%.BAM)! Assigning Inventory Icon (%inv_icon%.BAM)..."
      END
      WRITE_ASCIIE ("%abil_off%" + 0x04 + (0x38 * "%index%")) ~%inv_icon%~ #8
    END
  END
END
