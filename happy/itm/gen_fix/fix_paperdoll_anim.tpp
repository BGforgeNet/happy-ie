//DLTCEP: This X has an unusual animation of Y

READ_SHORT 0x1c type
READ_ASCII 0x22 anim (2)
READ_BYTE 0x31 prof
PATCH_IF type = 0 AND NOT (~%anim%~ STRING_EQUAL ~  ~) BEGIN
  PATCH_PRINT ~%SOURCE_FILE% issue: wrong paperdoll animation %anim% for item type MISC. Setting to NONE.~
  WRITE_ASCII 0x22 ~~ #2
END
