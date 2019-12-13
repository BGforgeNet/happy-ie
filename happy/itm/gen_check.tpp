GET_OFFSET_ARRAY fx_array ITM_V10_GEN_EFFECTS
PHP_EACH fx_array AS int => fx_off BEGIN
  READ_SHORT fx_off opcode
  READ_ASCII (fx_off+0x14) resref
  PATCH_IF VARIABLE_IS_SET $opcode_with_res(~%opcode%~) BEGIN
    SPRINT ext $opcode_with_res(~%opcode%~)
    PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.%ext%~ BEGIN
      PATCH_PRINT ~HW231: %SOURCE_FILE% - effect with opcode %opcode% refers to a missing resource %resref%.%ext%~
    END
  END
END
