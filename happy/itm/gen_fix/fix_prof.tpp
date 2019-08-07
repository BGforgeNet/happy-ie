//DLTCEP: Invalid weapon proficiency: x

READ_SHORT 0x1c type
READ_BYTE 0x31 prof
PATCH_IF (type = 0x5 OR type = 0x1f OR type = 0xe) AND prof != 0 BEGIN //bullets, arrows, bolts
  PATCH_PRINT ~HI43: %SOURCE_FILE% - ammo does not need a proficiency. Setting to 0.~
  WRITE_BYTE 0x31 0
END
