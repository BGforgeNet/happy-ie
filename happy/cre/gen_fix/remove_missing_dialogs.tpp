// Missing Dialogue Remover
READ_ASCII 0x2cc "dialog"

PATCH_IF NOT (("%dialog%" STR_EQ "NONE") OR ("%dialog%" STR_EQ "")) BEGIN
  SET exists = 0
  SET dlgexists = 0
  PATCH_IF FILE_EXISTS_IN_GAME ~%dialog%.dlg~ BEGIN
    SET exists = 1
  END
  PATCH_IF FILE_EXISTS_IN_GAME ~%SOURCE_RES%.dlg~ BEGIN
    SET dlgexists = 1
  END
  PATCH_IF ("%exists%" = 0) AND ("%dlgexists%" = 1) BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: Non-existent dialogue (%dialog%.DLG) changed into %SOURCE_RES%.DLG..."
    WRITE_ASCIIE 0x2cc ~%SOURCE_RES%~ #8
  END ELSE
  PATCH_IF ("%exists%" = 0) BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: Non-existent dialogue (%dialog%.DLG) nulled..."
    WRITE_ASCII 0x2cc ~~ #8
  END
END
