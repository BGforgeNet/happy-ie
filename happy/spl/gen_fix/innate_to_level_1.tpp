// Innate Fixer
READ_SHORT 0x1c "spell_type"
READ_LONG  0x34 "spell_level"

PATCH_IF (%spell_type% = 4) BEGIN
  PATCH_IF (%spell_level% != 1) BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: Innate Spell is not Level 1! Setting level to 1..."
    WRITE_LONG 0x34 ~1~
  END
END
