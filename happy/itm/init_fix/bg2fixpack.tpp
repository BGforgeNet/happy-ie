READ_LONG   0x64 "abil_off"
READ_SHORT  0x68 "abil_num"
READ_LONG   0x6a "fx_off"
READ_SHORT  0x70 "fx_num"
SET delta = 0
FOR (index = 0 ; index < fx_num ; ++index) BEGIN
  READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "type"
  READ_ASCII ("%fx_off%" + 0x14 + ("%index%" * 0x30)) "eff_file"
  PATCH_IF (("%type%" = 177) AND
            (("%eff_file%" STR_EQ "DAMACEA") OR
              ("%eff_file%" STR_EQ "DOPPDAM") OR
              ("%eff_file%" STR_EQ "DRAGDAM3") OR
              ("%eff_file%" STR_EQ "EVILDAM2") OR
              ("%eff_file%" STR_EQ "FLAMENOR") OR
              ("%eff_file%" STR_EQ "GIANTDAM") OR
              ("%eff_file%" STR_EQ "HOLYAVEN") OR
              ("%eff_file%" STR_EQ "LYCANDAM") OR
              ("%eff_file%" STR_EQ "LYCNDAM3") OR
              ("%eff_file%" STR_EQ "LYCNDAM4") OR
              ("%eff_file%" STR_EQ "PHANBLAD") OR
              ("%eff_file%" STR_EQ "SKULLCR") OR
              ("%eff_file%" STR_EQ "SW2H19A") OR
              ("%eff_file%" STR_EQ "UNDDAM1") OR
              ("%eff_file%" STR_EQ "TROLLD1") OR
              ("%eff_file%" STRING_COMPARE_REGEXP "EQUAL0[1-8]" = 0) OR
              ("%eff_file%" STRING_COMPARE_REGEXP "FT[1-3]DAM" = 0) OR
              ("%eff_file%" STRING_COMPARE_REGEXP "SW1H6[45]A" = 0) OR
              ("%eff_file%" STRING_COMPARE_REGEXP "SW1H62[BCDEF]" = 0))) BEGIN
    PATCH_IF ("%eff_file%" STR_EQ "lycandam") BEGIN
      SPRINT eff_file "cdsw1h03"
    END
    PATCH_IF ("%eff_file%" STR_EQ "dragdam3") BEGIN
      SPRINT eff_file "cdhalb04"
    END
    READ_ASCII   ("%fx_off%" +        ("%index%" * 0x30)) "clone" (48)
    PATCH_PRINT "%SOURCE_FILE% patched for BG2Fixpack EFF fixes..."
    offset = "%fx_off%" + ("%index%" * 0x30)
    value  = 0x30
    DELETE_BYTES offset value
    SOURCE_SIZE = SOURCE_SIZE - value
    SET fx_num = (fx_num - 1)
    SET delta  = (delta - 1)
    SET index  = (index - 1)
    INNER_ACTION BEGIN
      COPY_EXISTING ~%eff_file%.eff~ ~override~
        READ_ASCII 0x1c "ids" (8)
      BUT_ONLY
    END
    FOR (index2 = 0 ; index2 < abil_num ; index2 = index2 + 1) BEGIN
      READ_BYTE   ("%abil_off%" +        ("%index2%" * 0x38)) "type"
      READ_SHORT  ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "abil_fx_idx"
      SET "abil_fx_idx" = "%abil_fx_idx%" + "%delta%"
      WRITE_SHORT ("%abil_off%" + 0x20 + ("%index2%" * 0x38)) "%abil_fx_idx%"
      PATCH_IF (("%type%" = 1) OR ("%type%" = 2)) BEGIN
        INSERT_BYTES (fx_off +        (0x30 * abil_fx_idx)) 0x30
        WRITE_ASCIIE (fx_off +        (0x30 * abil_fx_idx)) "%clone%"
        WRITE_SHORT  (fx_off +        (0x30 * abil_fx_idx)) 177     // use eff
        WRITE_BYTE   (fx_off + 0x02 + (0x30 * abil_fx_idx))   2     // preset target
        WRITE_ASCIIE (fx_off + 0x04 + (0x30 * abil_fx_idx)) "%ids%" // ids target from eff
        WRITE_BYTE   (fx_off + 0x0c + (0x30 * abil_fx_idx))   1     // instant/perm
        WRITE_ASCIIE (fx_off + 0x14 + (0x30 * abil_fx_idx)) "%eff_file%" #8 // for the items with changing effs
        READ_SHORT  ("%abil_off%" + 0x1e + ("%index2%" * 0x38)) "abil_fx_num"
        WRITE_SHORT ("%abil_off%" + 0x1e + ("%index2%" * 0x38)) ("%abil_fx_num%" + 1)
        SET delta = (delta + 1)
      END
    END
  END
END
WRITE_SHORT  0x70 "%fx_num%"

// Poison Resist Effect Fixer (needs ToBEx)
READ_LONG   0x6a "fx_off" ELSE 0
READ_SHORT  0x6e "fx_idx" ELSE 0
READ_SHORT  0x70 "fx_num" ELSE 0

PATCH_IF (fx_off > 0x71) BEGIN
  FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN
    READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "opcode"
    READ_BYTE  ("%fx_off%" + 0x02 + ("%index%" * 0x30)) "target"
    READ_LONG  ("%fx_off%" + 0x04 + ("%index%" * 0x30)) "param1"
    READ_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) "param2"
    PATCH_IF ("%opcode%" = 173) AND ("%target%" = 1) AND ("%param1%" < 100) AND ("%param2%" != 1) BEGIN
      PATCH_PRINT "HW132: %SOURCE_FILE% - Poison Resist set to INCREMENT to %param1%"
      WRITE_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) 1
    END ELSE
    PATCH_IF ("%opcode%" = 173) AND ("%target%" = 1) AND ("%param1%" > 99) AND ("%param2%" != 0) BEGIN
      PATCH_PRINT "HW133: %SOURCE_FILE% - Poison Resist set to SET to %param1%"
      WRITE_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) 0
    END
  END
END
