READ_LONG  0x2a0 "known_off" ELSE 0
READ_LONG  0x2a4 "known_num" ELSE 0

PATCH_IF (known_off > 0x2d3) BEGIN
  FOR (index = 0 ; index < known_num ; index = index + 1) BEGIN
    READ_ASCII ("%known_off%" +        ("%index%" * 0x0c)) "resref"
    SET exists = 0
    INNER_PATCH_FILE ~%resref%.spl~ BEGIN
      READ_SHORT 0x1c "spl_type"
      READ_LONG  0x34 "spl_level"
      SET exists = 1
    END
    PATCH_IF ("%exists%" = 1) BEGIN

      // Spell Slot Fixer
      READ_SHORT ("%known_off%" + 0x0a + ("%index%" * 0x0c)) "type"
      PATCH_IF (("%spl_type%" = 2) AND ("%type%" != 0)) BEGIN // priest
        PATCH_IF ("%type%" = 1) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a PRIEST spell (was MAGE)..."
        END ELSE
        PATCH_IF ("%type%" = 2) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a PRIEST spell (was INNATE)..."
        END ELSE
        BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a PRIEST spell (was %type%)..."
        END
        WRITE_SHORT ("%known_off%" + 0x0a + ("%index%" * 0x0c)) 0
      END
      PATCH_IF (("%spl_type%" = 1) AND ("%type%" != 1)) BEGIN // mage
        PATCH_IF ("%type%" = 0) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a MAGE spell (was PRIEST)..."
        END ELSE
        PATCH_IF ("%type%" = 2) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a MAGE spell (was INNATE)..."
        END ELSE
        BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is a MAGE spell (was %type%)..."
        END
        WRITE_SHORT ("%known_off%" + 0x0a + ("%index%" * 0x0c)) 1
      END
      PATCH_IF (("%spl_type%" = 4) AND ("%type%" != 2)) BEGIN // innate
        PATCH_IF ("%type%" = 0) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is an INNATE spell (was PRIEST)..."
        END ELSE
        PATCH_IF ("%type%" = 1) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is an INNATE spell (was MAGE)..."
        END ELSE
        BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is an INNATE spell (was %type%)..."
        END
        WRITE_SHORT ("%known_off%" + 0x0a + ("%index%" * 0x0c)) 2
      END

      // Spell Level Fixer
      READ_SHORT ("%known_off%" + 0x08 + ("%index%" * 0x0c)) "olevel"
      READ_SHORT ("%known_off%" + 0x0a + ("%index%" * 0x0c)) "type"
      SET level = %olevel% + 1
      PATCH_IF (("%level%" != "%spl_level%") AND ("%spl_level%" > 0) AND (("%spl_type%" = 1) OR ("%spl_type%" = 2))) BEGIN
        SET nlevel = %spl_level% - 1
        PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) has wrong level (%olevel%)! Should be %nlevel%..."
        WRITE_SHORT ("%known_off%" + 0x08 + ("%index%" * 0x0c)) %nlevel%
      END
      PATCH_IF ("%olevel%" > 0) AND ("%spl_type%" = 4) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Known spell (%resref%.SPL) is INNATE with non-zero level (%olevel%)! Setting to 0 to avoid crash..."
        WRITE_SHORT ("%known_off%" + 0x08 + ("%index%" * 0x0c)) 0
      END

      // Invalid Spell Level Fixer
      READ_SHORT ("%known_off%" + 0x08 + ("%index%" * 0x0c)) "olevel"
      SET nlevel = %olevel% + 1
      PATCH_IF ("%olevel%" > 6) AND ("%spl_type%" = 2) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Spell level out of bounds (%resref%.SPL is a level %nlevel% PRIEST spell)! Removing to avoid crash..."
        REMOVE_KNOWN_SPELL ~%resref%~
        SET "index" = 0 - 1
        READ_LONG  0x2a4 "known_num"
      END ELSE
      PATCH_IF ("%olevel%" > 8) AND ("%spl_type%" = 1) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Spell level out of bounds (%resref%.SPL is a level %nlevel% MAGE spell)! Removing to avoid crash..."
        REMOVE_KNOWN_SPELL ~%resref%~
        SET "index" = 0 - 1
        READ_LONG  0x2a4 "known_num"
      END
    END ELSE

    // Missing Known Spell Remover
    BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Known spell does not exist (%resref%.SPL)! Removing..."
      REMOVE_KNOWN_SPELL ~%resref%~
      SET "index" = 0 - 1
      READ_LONG  0x2a4 "known_num"
    END
  END
  END

// Missing Memorized Spell Remover
READ_LONG  0x2b0 "mem_off" ELSE 0
READ_LONG  0x2b4 "mem_num" ELSE 0

PATCH_IF (mem_off > 0x2d3) BEGIN
  FOR (index = 0 ; index < mem_num ; index = index + 1) BEGIN
    READ_ASCII ("%mem_off%" +        ("%index%" * 0x0c)) "resref"
    SET exists = 0
    PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.spl~ BEGIN
      SET exists = 1
    END
    PATCH_IF ("%exists%" = 0) BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Memorized spell does not exist (%resref%.SPL)! Removing..."
      REMOVE_MEMORIZED_SPELL ~%resref%~
      SET "index" = 0 - 1
      READ_LONG  0x2b4 "mem_num"
    END
  END
END
