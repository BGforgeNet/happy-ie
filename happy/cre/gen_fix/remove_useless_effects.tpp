READ_BYTE 0x33  fx_flag
READ_LONG 0x2c4 fx_off
READ_LONG 0x2c8 fx_num
opcode_off = fx_flag = 1 ? 0x8 : 0
res_off = fx_flag = 1 ? 0x28 : 0x14
eff_size = fx_flag = 1 ? 0x108 : 0x30

FOR (i=0;i<fx_num;i=i+1) BEGIN
  cur_off = fx_off + i * eff_size
  READ_LONG (cur_off + opcode_off) opcode
  PATCH_IF (opcode = 206) BEGIN //protection from spell
    READ_ASCII (cur_off+res_off) spell
    PATCH_IF NOT FILE_EXISTS_IN_GAME ~%spell%.spl~ BEGIN
      PATCH_PRINT ~%SOURCE_FILE% issue: protection from non-existent spell %spell%. Removing~
      DELETE_BYTES (fx_off + i * eff_size) eff_size
      fx_num = fx_num - 1 //decrease effects number to stop cycle properly
      i = i - 1 //step back to not miss an effect
      //correcting offsets and number
      WRITE_LONG 0x2c8 fx_num //corrected earlier
      PATCH_FOR_EACH offset IN 0x2a0 0x2a8 0x2b0 0x2b8 0x2bc BEGIN
        READ_LONG offset current_off
        PATCH_IF current_off > fx_off BEGIN
          WRITE_LONG offset (current_off - eff_size)
        END
      END
    END
  END
END
