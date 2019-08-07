// Missing Script Remover
FOR (index = 0 ; index < 5 ; index = index + 1) BEGIN
  READ_ASCII (0x248 + (0x08 * "%index%")) "script"
  PATCH_IF NOT (("%script%" STR_EQ "NONE") OR ("%script%" STR_EQ "")) BEGIN
    SET exists = 0
    PATCH_IF FILE_EXISTS_IN_GAME ~%script%.bcs~ BEGIN
      SET exists = 1
    END
    PATCH_IF ("%exists%" = 0) BEGIN
      PATCH_IF ("%script%" STR_EQ "_DPLAYER") BEGIN
        PATCH_PRINT "HW20: %SOURCE_FILE% - Non-existent script (%script%.BCS) changed into DPLAYER.BCS..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~DPLAYER~ #8
      END ELSE
      PATCH_IF ("%script%" STR_EQ "BPMAG12D") BEGIN
        PATCH_PRINT "HW21: %SOURCE_FILE% - Non-existent script (%script%.BCS) changed into MAGE12D.BCS..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~MAGE12D~ #8
      END ELSE
      PATCH_IF ("%script%" STR_EQ "BPMAG14D") BEGIN
        PATCH_PRINT "HW22: %SOURCE_FILE% - Non-existent script (%script%.BCS) changed into MAGE14D.BCS..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~MAGE14D~ #8
      END ELSE
      PATCH_IF ("%script%" STR_EQ "BPWDASGT") BEGIN
        PATCH_PRINT "HW23: %SOURCE_FILE% - Non-existent script (%script%.BCS) changed into WDASIGHT.BCS..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~WDASIGHT~ #8
      END ELSE
      PATCH_IF ("%script%" STR_EQ "BPWTSIGT") OR
               ("%script%" STR_EQ "WTSIGHT") OR
               ("%script%" STR_EQ "WSASIGHT") BEGIN
        PATCH_PRINT "HW24: %SOURCE_FILE% - Non-existent script (%script%.BCS) changed into WTASIGHT.BCS..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~WTASIGHT~ #8
      END ELSE
      BEGIN
        PATCH_PRINT "HW25: %SOURCE_FILE% - Non-existent script (%script%.BCS) nulled..."
        WRITE_ASCII (0x248 + (0x08 * "%index%")) ~~ #8
      END
    END
  END
END
