READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0
PATCH_IF (abil_off > 0x71) BEGIN
  FOR (index = 0; index < abil_num; index = index + 1) BEGIN
    READ_BYTE  ("%abil_off%" + 0x02 + (0x28 * "%index%")) "slot"
    READ_BYTE  ("%abil_off%" + 0x0c + (0x28 * "%index%")) "target"

    // Ability Target Fixer
    PATCH_IF (("%target%"  = 2) OR ("%target%" = 6)) BEGIN
      PATCH_PRINT "HI65: %SOURCE_FILE% - Ability #%index% target may crash! (was %target%) Setting to self..."
      WRITE_BYTE  ("%abil_off%" + 0x0c + (0x28 * "%index%")) 1
    END

    // Spell Slot Fixer
    PATCH_IF (("%spell_type%"  = 4) AND ("%slot%" != 4)) BEGIN
      PATCH_IF ("%slot%" = 1) BEGIN
        PATCH_PRINT "HI66: %SOURCE_FILE% - Ability #%index% assigned to INNATE slot (was WEAPON)..."
      END ELSE
      PATCH_IF ("%slot%" = 2) BEGIN
        PATCH_PRINT "HI67: %SOURCE_FILE% - Ability #%index% assigned to INNATE slot (was SPELL)..."
      END ELSE
      PATCH_IF ("%slot%" = 3) BEGIN
        PATCH_PRINT "HI68: %SOURCE_FILE% - Ability #%index% assigned to INNATE slot (was EQUIPMENT)..."
      END ELSE
      BEGIN
        PATCH_PRINT "HI69: %SOURCE_FILE% - Ability #%index% assigned to INNATE slot (was %slot%)..."
      END
      WRITE_BYTE  ("%abil_off%" + 0x02 + (0x28 * "%index%")) 4
    END
    PATCH_IF (("%spell_type%" != 4) AND ("%slot%" != 2)) BEGIN
      PATCH_IF ("%slot%" = 1) BEGIN
        PATCH_PRINT "HI70: %SOURCE_FILE% - Ability #%index% assigned to SPELL slot (was WEAPON)..."
      END ELSE
      PATCH_IF ("%slot%" = 3) BEGIN
        PATCH_PRINT "HI71: %SOURCE_FILE% - Ability #%index% assigned to SPELL slot (was EQUIPMENT)..."
      END ELSE
      PATCH_IF ("%slot%" = 4) BEGIN
        PATCH_PRINT "HI72: %SOURCE_FILE% - Ability #%index% assigned to SPELL slot (was INNATE)..."
      END ELSE
      BEGIN
        PATCH_PRINT "HI73: %SOURCE_FILE% - Ability #%index% assigned to SPELL slot (was %slot%)..."
      END
      WRITE_BYTE  ("%abil_off%" + 0x02 + (0x28 * "%index%")) 2
    END
  END
END
