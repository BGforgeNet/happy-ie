//DLTCEP | Alt damage dice type set:6

GET_OFFSET_ARRAY head_array ITM_V10_HEADERS
PHP_EACH head_array AS i => head_off BEGIN
  READ_BYTE (head_off + 0x3) alt_dice_side
  READ_BYTE (head_off + 0x11) alt_dice_num
  READ_BYTE (head_off + 0x13) alt_dam_bonus
  PATCH_IF alt_dice_side != 0 OR alt_dice_num != 0 OR alt_dam_bonus != 0 BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: header %i% has alternative damage set to %alt_dice_num%d%alt_dice_side%+%alt_dam_bonus%. Setting to 0.~
    WRITE_BYTE (head_off + 0x3) alt_dice_side
    WRITE_BYTE (head_off + 0x11) alt_dice_num
    WRITE_BYTE (head_off + 0x13) alt_dam_bonus
  END
END
