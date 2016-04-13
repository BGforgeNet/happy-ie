// Ability Slot Fixer
READ_SHORT 0x1c "type"
READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0

PATCH_IF (abil_off > 0x71) BEGIN
  FOR (index = 0; index < abil_num; index = index + 1) BEGIN
    READ_BYTE  ("%abil_off%" + 0x00 + (0x38 * "%index%")) "abil_type"
    READ_BYTE  ("%abil_off%" + 0x02 + (0x38 * "%index%")) "slot"
    PATCH_IF ((((%type% > 14) AND (%type% < 31)) OR %type% = 44) AND (("%abil_type%" = 1) OR ("%abil_type%" = 2) OR ("%abil_type%" = 4)) AND ("%slot%" != 1)) BEGIN
      PATCH_IF ("%slot%" = 2) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to WEAPON slot (was SPELL)..."
      END ELSE
      PATCH_IF ("%slot%" = 3) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to WEAPON slot (was EQUIPMENT)..."
      END ELSE
      PATCH_IF ("%slot%" = 4) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to WEAPON slot (was INNATE)..."
      END ELSE
      BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to WEAPON slot (was %slot%)..."
      END
      WRITE_BYTE  ("%abil_off%" + 0x02 + (0x38 * "%index%")) 1
    END
    PATCH_IF ((%type% < 15 OR ((%type% > 30) AND (%type% != 44))) AND ("%abil_type%" = 3) AND ("%slot%" != 3)) BEGIN
      PATCH_IF ("%slot%" = 1) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to EQUIPMENT slot (was WEAPON)..."
      END ELSE
      PATCH_IF ("%slot%" = 2) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to EQUIPMENT slot (was SPELL)..."
      END ELSE
      PATCH_IF ("%slot%" = 4) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to EQUIPMENT slot (was INNATE)..."
      END ELSE
      BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% assigned to EQUIPMENT slot (was %slot%)..."
      END
      WRITE_BYTE  ("%abil_off%" + 0x02 + (0x38 * "%index%")) 3
    END
  END
END
