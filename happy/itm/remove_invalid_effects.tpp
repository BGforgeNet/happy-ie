GET_OFFSET_ARRAY fx_array ITM_V10_GEN_EFFECTS
PHP_EACH fx_array AS int => fx_off BEGIN size=int END //ugly hack to count array size
  PHP_EACH fx_array AS int => fx_off BEGIN
    PATCH_IF int <= size BEGIN
    READ_SHORT fx_off opcode
    READ_LONG (fx_off+0x8) parameter2
    PATCH_IF (opcode = 12 AND (VARIABLE_IS_SET $dtype(~%parameter2%~))) BEGIN
      SPRINT dtype_string $dtype(~%parameter2%~)
      PATCH_PRINT ~HE8: %SOURCE_FILE% - damage of type %dtype_string%. Removing.~
      LPF G_DELETE_ITEM_EFFECT  INT_VAR opcode = %opcode% check_globals = 1 parameter2 = %parameter2%  END
    END
    PATCH_IF (VARIABLE_IS_SET $rtype(~%opcode%~)) BEGIN
      SPRINT rtype_string $rtype(~%opcode%~)
      PATCH_PRINT ~HI63: %SOURCE_FILE% - an effect adds resistance to nonexistent damage type %rtype_string%. Removing.~
      LPF G_DELETE_ITEM_EFFECT  INT_VAR opcode = %opcode% check_globals = 1  END
      size -= 1
    END
  END
END


CLEAR_ARRAY fx_array
CLEAR_ARRAY delete_opcode
CLEAR_ARRAY delete_resref
GET_OFFSET_ARRAY fx_array ITM_V10_GEN_EFFECTS
i = 0

PHP_EACH fx_array AS int => fx_off BEGIN
  READ_SHORT fx_off opcode
  READ_ASCII (fx_off+0x14) resref
  PATCH_IF VARIABLE_IS_SET $opcode_with_res(~%opcode%~) BEGIN
    SPRINT ext $opcode_with_res(~%opcode%~)
    PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.%ext%~ BEGIN
      PATCH_PRINT ~HW232: %SOURCE_FILE% - effect with opcode %opcode% refers to a non-existent resource %resref%.%ext%. Removing.~
      SET $delete_opcode(~%i%~) = opcode
      SPRINT $delete_resref(~%i%~) ~%resref%~
      i = i + 1
    END
  END
END

PHP_EACH delete_opcode AS i2 => opcode BEGIN
  SPRINT resref $delete_resref(~%i2%~)
  LPF G_DELETE_ITEM_EFFECT
    INT_VAR opcode = %opcode%  check_globals = 1
    STR_VAR resource = EVAL ~%resref%~
  END
END
