// Actor Miscellaneous Patching
READ_LONG  0x54 "actor_off" ELSE 0
READ_SHORT 0x58 "actor_num" ELSE 0

PATCH_IF (actor_off > 0x11b) BEGIN
  FOR (index = 0 ; index < actor_num ; index = index + 1) BEGIN

    // Invalid Embedded CRE Status Patching
    READ_BYTE  ("%actor_off%" + 0x28 + (0x110 * "%index%")) "flags"  // flags first byte
    READ_ASCII ("%actor_off%" + 0x80 + (0x110 * "%index%")) "resref" // cre file
    PATCH_IF NOT (("%resref%" STR_EQ "NONE") OR ("%resref%" STR_EQ "")) BEGIN
      PATCH_IF (("%flags%" BAND 0b00000001) = 0b00000000) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Actor #%index% (%resref%.CRE) exists and should not be attached to the ARE..."
        WRITE_BYTE ("%actor_off%" + 0x28 + (0x110 * "%index%")) ("%flags%" BOR 0b00000001)
      END
    END

    // Actor Removal Prevention
    READ_LONG  ("%actor_off%" + 0x38 + (0x110 * "%index%")) "removal_timer"
    PATCH_IF ("%removal_timer%" = 0) BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Actor #%index% set to disappear after %removal_timer% seconds! Setting to -1..."
      WRITE_LONG ("%actor_off%" + 0x38 + (0x110 * "%index%")) 0xffffffff
    END ELSE
    PATCH_IF ("%removal_timer%" != 0xffffffff) BEGIN
      PATCH_PRINT "%SOURCE_FILE% issue: Actor #%index% set to disappear after %removal_timer% seconds!"
//        WRITE_LONG ("%actor_off%" + 0x38 + (0x110 * "%index%")) 0xffffffff
    END
  END
END
