// Missing Actor Remover
READ_LONG  0x54 "actor_off" ELSE 0
READ_SHORT 0x58 "actor_num" ELSE 0

PATCH_IF (actor_off > 0x11b) BEGIN
  FOR (index = 0 ; index < actor_num ; index = index + 1) BEGIN
    READ_BYTE  ("%actor_off%" + 0x28 + (0x110 * "%index%")) "flags"  // flags first byte
    READ_ASCII ("%actor_off%" + 0x80 + (0x110 * "%index%")) "resref" // cre file
    PATCH_IF NOT ("%resref%" STRING_COMPARE_REGEXP "^[Rr][Dd].+$" == 0) BEGIN // ignore creatures starting with RD
      SET "exists" = 0
      PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
        SET "exists" = 1
      END
      PATCH_IF (("%exists%" = 0) AND (("%flags%" BAND 0b00000001) = 0b00000001)) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Actor #%index% does not exist (%resref%.cre)! Removing actor..."
        LPF fj_are_structure
          INT_VAR fj_delete_mode    = "%index%"
          STR_VAR fj_structure_type = actor
        END
        SET "index" = 0 - 1
        READ_SHORT 0x58 "actor_num"
      END
    END
  END
END
