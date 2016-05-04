//DLTCEP: Invalid weapon proficiency: x

READ_SHORT 0x1c type
READ_BYTE 0x31 prof
PATCH_IF (type = 0x5 OR type = 0x1f) AND prof != 0 BEGIN
  PATCH_PRINT ~%SOURCE_FILE% issue: ammo does not need a proficiency. Setting to 0.~
  WRITE_BYTE 0x31 0
END
