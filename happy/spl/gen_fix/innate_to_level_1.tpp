// Innate Fixer
READ_SHORT 0x1c "spell_type"
READ_LONG  0x34 "spell_level"

PATCH_IF SOURCE_FILE != ~bardsong.spl~ //TobEx externalizes this, but I don't think it's called from scripts
  PATCH_IF (%spell_type% = 4) BEGIN
    PATCH_IF (%spell_level% != 1) BEGIN
      PATCH_PRINT "HE10: %SOURCE_FILE% - Innate Spell is not Level 1! Setting level to 1..."
      WRITE_LONG 0x34 ~1~
    END
  END
END
