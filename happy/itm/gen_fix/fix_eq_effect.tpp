READ_LONG  0x6a fx_off ELSE 0
READ_SHORT 0x6e fx_idx ELSE 0
READ_SHORT 0x70 fx_num ELSE 0

PATCH_IF (fx_off > 0x71) BEGIN
  FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN // check equipping effects
    READ_SHORT (fx_off +        (index * 0x30)) opcode
    READ_LONG  (fx_off + 0x04 + (index * 0x30)) param1
    READ_LONG  (fx_off + 0x08 + (index * 0x30)) param2

    PATCH_IF ((opcode = 6)  OR
              (opcode = 10) OR
              (opcode = 15) OR
              (opcode = 19) OR
              (opcode = 44) OR
              (opcode = 49)) AND (((param2 = 1) OR (param2 = 2)) AND (param1 = 0)) BEGIN
      PATCH_PRINT "HW125: %SOURCE_FILE% - Stat Opcode (#%opcode%) setting to 0%! Incrementing by 1..."
      WRITE_LONG  (fx_off + 0x04 + (index * 0x30)) 1
      WRITE_LONG  (fx_off + 0x08 + (index * 0x30)) 0
    END
/*
    READ_BYTE  (fx_off + 0xd + (index * 0x30)) resist
    PATCH_INCLUDE ~%MOD_FOLDER%/lib/dispelable_items.tpp~
    PATCH_IF (resist != 0 AND resist != 2) BEGIN
      skip = 0
      PHP_EACH dispelable_items AS int => item BEGIN //skip dispelable items from original game
        PATCH_IF ~%SOURCE_FILE%~ STR_EQ ~%item%.itm~ BEGIN skip = 1 END
      END
      PATCH_IF skip = 0 BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: equipping effect %index% is either dispellable or affected by magic resistance. Setting to 2 (no dispel / bypass MR)."
        WRITE_BYTE  (fx_off + 0xd + (index * 0x30)) 2
      END
    END
*/
  END
END
