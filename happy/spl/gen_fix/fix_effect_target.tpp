// Effect Target Fixer
READ_LONG  0x6a "fx_off"
READ_SHORT 0x6e "fx_idx"
READ_SHORT 0x70 "fx_num"

PATCH_IF (fx_off > 0x71) BEGIN
  FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN // check equipping effects
    READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "opcode"
    READ_BYTE  ("%fx_off%" + 0x02 + ("%index%" * 0x30)) "target"
    PATCH_IF ("%target%" = 2) BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Casting Effect #%index% (opcode %opcode%) targets preset target! Targetting self..."
      WRITE_BYTE  ("%fx_off%" + 0x02 + ("%index%" * 0x30)) 1
    END
  END
END
