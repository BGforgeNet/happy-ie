// Script Assigner
READ_ASCII 0x94 "script"

SET "exists" = 0
SET "scexists" = 0
SET "unassigned" = 0
SET "missing" = 0
PATCH_IF FILE_EXISTS_IN_GAME ~%SOURCE_RES%.bcs~ BEGIN
  SET "exists" = 1
END
PATCH_IF FILE_EXISTS_IN_GAME ~%script%.bcs~ BEGIN
  SET "scexists" = 1
END
PATCH_IF (("%scexists%" = 0) AND ("%exists%" = 0)) BEGIN
  SET "missing" = 1
END
PATCH_IF (("%scexists%" = 0) AND ("%exists%" = 1)) BEGIN
  SET "unassigned" = 1
END
PATCH_IF ("%unassigned%" = 1) BEGIN
  PATCH_PRINT "%SOURCE_FILE% issue: Area Script (%SOURCE_RES%.bcs) assigned"
  WRITE_ASCIIE 0x94 ~%SOURCE_RES%~ #8
END ELSE
PATCH_IF ("%missing%" = 1) BEGIN
  PATCH_IF NOT (("%script%" STR_EQ "NONE") OR ("%script%" STR_EQ "")) BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: Missing area Script (%script%.bcs) created"
    INNER_ACTION BEGIN
      <<<<<<<< %script%.BAF
>>>>>>>>
      COMPILE ~%script%.BAF~
    END
  END ELSE
  BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: Missing area Script (%SOURCE_RES%.bcs) created and assigned"
    INNER_ACTION BEGIN
      <<<<<<<< %SOURCE_RES%.BAF
>>>>>>>>
      COMPILE ~%SOURCE_RES%.BAF~
    END
    WRITE_ASCIIE 0x94 ~%SOURCE_RES%~ #8
  END
END
