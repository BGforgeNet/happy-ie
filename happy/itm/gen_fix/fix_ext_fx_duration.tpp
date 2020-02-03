//DLTCEP: Useless duration set in Extended header #x/y
//DLTCEP: No duration set in Extended header #x/y

GET_OFFSET_ARRAY h_array ITM_V10_HEADERS
PHP_EACH h_array AS i1 => h_off BEGIN
  GET_OFFSET_ARRAY2 fx_array h_off ITM_V10_HEAD_EFFECTS
  PHP_EACH fx_array AS i2 => fx_off BEGIN
    READ_BYTE (fx_off + 0xc) timing
    READ_LONG (fx_off + 0xe) duration
    PATCH_IF (timing = 1 OR timing = 9) AND duration !=0 BEGIN
      PATCH_PRINT ~HI39: %SOURCE_FILE% - effect %i1%/%i2% has useless duration of %duration%. Setting to 0.~
      WRITE_LONG (fx_off + 0xe) 0
    END
    PATCH_IF (timing = 0) AND duration = 0 BEGIN
      PATCH_PRINT ~HI40: %SOURCE_FILE% - effect %i1%/%i2% has no duration set. Setting timing to 1/instant.~
      WRITE_BYTE (fx_off + 0xc) 1
    END
  END
END
