// Missing Spawn Remover
READ_LONG  0x60 "spawn_off" ELSE 0
READ_LONG  0x64 "spawn_num" ELSE 0

PATCH_IF (spawn_off > 0x11b) BEGIN
  FOR (index = 0 ; index < spawn_num ; index = index + 1) BEGIN
    FOR (index2 = 0 ; index2 < 10 ; index2 = index2 + 1) BEGIN
      READ_ASCII ("%spawn_off%" + 0x24 + ("%index2%" * 0x08) + ("%index%" * 0xc8)) "resref"
      PATCH_IF (NOT ("%resref%" STR_EQ "") AND                  // ignore empty entries
                NOT ("%resref%" STR_EQ "none") AND              // ignore 'none'
                ("%resref%" STRING_COMPARE_REGEXP "^[Rr][Dd].+$")) BEGIN // ignore creatures starting with RD
        SET "exists" = 0
        PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
          SET "exists" = 1
        END
        PATCH_IF ("%exists%" = 0) BEGIN
          PATCH_PRINT "%SOURCE_FILE% issue: Spawn Point #%index% creature file does not exist (%resref%.cre)! Nulling..."
          WRITE_ASCII ("%spawn_off%" + 0x24 + ("%index2%" * 0x08) + ("%index%" * 0xc8)) ~NONE~ #8
        END
      END
    END
    SET "none_count" = 0
    FOR (index2 = 0 ; index2 < 10 ; index2 = index2 + 1) BEGIN
      READ_ASCII ("%spawn_off%" + 0x24 + ("%index2%" * 0x08) + ("%index%" * 0xc8)) "resref"
      PATCH_IF (("%resref%" STR_EQ "") OR ("%resref%" STR_EQ "none")) BEGIN
        SET "none_count" = "none_count" + 1
      END
    END
    PATCH_IF ("%none_count%" = 10) BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Spawn Point #%index% has no creatures to spawn! Removing spawn entry..."
      LPF fj_are_structure
        INT_VAR fj_delete_mode    = "%index%"
        STR_VAR fj_structure_type = spawn
      END
      SET "index" = 0 - 1
      READ_LONG  0x64 "spawn_num"
    END
  END
END
