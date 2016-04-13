// Invalid Ability Remover
READ_LONG  0x64 "abil_off" ELSE 0
READ_SHORT 0x68 "abil_num" ELSE 0
READ_LONG  0x6a "fx_off" ELSE 0
READ_SHORT 0x6e "fx_idx" ELSE 0
READ_SHORT 0x70 "fx_num" ELSE 0

PATCH_IF (abil_off > 0x71) BEGIN
  FOR (index = 0; index < abil_num; index = index + 1) BEGIN
    READ_BYTE  ("%abil_off%" +        (0x38 * "%index%")) "abil_type"
    PATCH_IF ("%abil_type%" = 0) BEGIN
      READ_SHORT ("%abil_off%" + 0x1e + (0x38 * "%index%")) "abil_fx_num"
      READ_SHORT ("%abil_off%" + 0x20 + (0x38 * "%index%")) "abil_fx_idx"
      PATCH_IF ("%abil_fx_num%" > 0) BEGIN
        offset = "%fx_off%" + ("%abil_fx_idx%" * 0x30)
        value  = %abil_fx_num% * 0x30
        DELETE_BYTES offset value
        SOURCE_SIZE = SOURCE_SIZE - value
        PATCH_IF ("%abil_off%" > "%fx_off%") BEGIN
          SET "abil_off" = "abil_off" - (%abil_fx_num% * 0x30)
          WRITE_LONG  0x64 "abil_off"
        END
      END
      PATCH_IF ("%fx_idx%" > "%abil_fx_idx%") BEGIN
        SET "fx_idx" = "fx_idx" - "abil_fx_num"
        PATCH_PRINT "%SOURCE_FILE% issue: Writing new FX IDX = %fx_idx%!"
        WRITE_SHORT 0x6e "fx_idx"
      END
      FOR (index1 = 0; index1 < abil_num; index1 = index1 + 1) BEGIN
        PATCH_IF ("%index1%" != "%index%") BEGIN
          READ_SHORT ("%abil_off%" + 0x20 + (0x38 * "%index1%")) "abil_fx_idx1"
          PATCH_IF ("%abil_fx_idx1%" > "%abil_fx_idx%") BEGIN
            SET "abil_fx_idx1" = "abil_fx_idx1" - "abil_fx_num"
            PATCH_PRINT "%SOURCE_FILE% issue: Writing new ABIL #%index1% FX IDX = %abil_fx_idx1%!"
            WRITE_SHORT ("%abil_off%" + 0x20 + (0x38 * "%index1%")) "abil_fx_idx1"
          END
        END
      END
      offset = "%abil_off%" + ("%index%" * 0x38)
      value  = 0x38
      DELETE_BYTES offset value
      SOURCE_SIZE = SOURCE_SIZE - value
      PATCH_PRINT "%SOURCE_FILE% issue: Ability #%index% is invalid! Deleting Ability #%index%..."
      SET "index" = 0 - 1
      SET "abil_num" = "abil_num" - 1
      WRITE_SHORT 0x68 "abil_num"
      PATCH_IF ("%fx_off%" > "%abil_off%") BEGIN
        SET "fx_off" = "fx_off" - 0x38
        WRITE_LONG  0x6a "fx_off"
      END
    END
  END
END
