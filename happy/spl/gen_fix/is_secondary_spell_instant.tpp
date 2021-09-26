GET_OFFSET_ARRAY ab_array SPL_V10_HEADERS
PHP_EACH ab_array AS int => ab_off BEGIN
  GET_OFFSET_ARRAY2 fx_array ab_off SPL_V10_HEAD_EFFECTS
  PHP_EACH fx_array AS int => fx_off BEGIN
    READ_SHORT (fx_off + FX_opcode) opcode
    PATCH_MATCH opcode WITH
      OPCODE_cast_spell_at_creature
      OPCODE_cast_spell_at_point
    BEGIN
      READ_LONG (fx_off + FX_parameter2) casting_type
      READ_ASCII (fx_off + FX_resource) spell
      PATCH_IF casting_type != CASTING_TYPE_instant BEGIN
        PATCH_PRINT ~HW245: %SOURCE_FILE% - opcode %opcode%, non-instant casting type %casting_type% for secondary spell %spell%. This is likely a mistake, secondary spell can be interrupted after main spell is cast. Changing effect #%i% to instant cast.~
        WRITE_LONG (fx_off + FX_parameter2) CASTING_TYPE_instant
      END
    END DEFAULT END
  END
END
