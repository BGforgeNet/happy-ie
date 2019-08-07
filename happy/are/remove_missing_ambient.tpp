// Missing Ambient Remover
READ_SHORT 0x82 "amb_num" ELSE 0
READ_LONG  0x84 "amb_off" ELSE 0

PATCH_IF (amb_off > 0x11b) BEGIN
  FOR (index = 0 ; index < amb_num ; index = index + 1) BEGIN
    FOR (index2 = 0 ; index2 < 10 ; index2 = index2 + 1) BEGIN
      READ_ASCII ("%amb_off%" + 0x30 + ("%index2%" * 0x08) + (0xd4 * "%index%")) "resref"
      PATCH_IF NOT (("%resref%" STR_EQ "") OR ("%resref%" STR_EQ "none")) BEGIN
        SET "exists" = 0
        PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.wav~ BEGIN
          SET "exists" = 1
        END
        PATCH_IF ("%exists%" = 0) BEGIN
          PATCH_PRINT "HI11: %SOURCE_FILE% - Ambient #%index% does not exist (%resref%.wav)! Nulling..."
          WRITE_ASCII ("%amb_off%" + 0x30 + ("%index2%" * 0x08) + (0xd4 * "%index%")) ~NONE~ #8
        END
      END
    END
  END
END
