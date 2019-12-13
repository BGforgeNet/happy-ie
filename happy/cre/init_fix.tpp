LPF FJ_CRE_VALIDITY
  INT_VAR do_message = 1
END

PATCH_IF (existence_fix == 1) BEGIN
  READ_ASCII 0x280 "DV" (32) NULL

  PATCH_IF (NOT FILE_CONTAINS_EVALUATED (~PDIALOG.2DA~ ~^%DV% ~)) BEGIN
    READ_LONG  0x1b8 ~soundreplace~
    READ_LONG  0x1bc ~soundreplace2~
    READ_LONG  0x1c0 ~soundreplace3~
    READ_LONG  0x1c4 ~soundreplace4~
    READ_LONG  0x1c8 ~soundreplace5~

    PATCH_IF ("%soundreplace%" > 0) BEGIN
      PATCH_PRINT "HW27: %SOURCE_FILE% - Soundset moved : PICKED_POCKET -> EXISTANCE1"
      WRITE_LONG 0x1b8 ~-1~
      WRITE_LONG 0x1bc %soundreplace%
    END
    PATCH_IF ("%soundreplace2%" > 0) BEGIN
      PATCH_PRINT "HW28: %SOURCE_FILE% - Soundset moved : EXISTANCE1 -> EXISTANCE2"
      WRITE_LONG 0x1bc %soundreplace%
      WRITE_LONG 0x1c0 %soundreplace2%
    END
    PATCH_IF ("%soundreplace3%" > 0) BEGIN
      PATCH_PRINT "HW29: %SOURCE_FILE% - Soundset moved : EXISTANCE2 -> EXISTANCE3"
      WRITE_LONG 0x1c0 %soundreplace2%
      WRITE_LONG 0x1c4 %soundreplace3%
    END
    PATCH_IF ("%soundreplace4%" > 0) BEGIN
      PATCH_PRINT "HW30: %SOURCE_FILE% - Soundset moved : EXISTANCE3 -> EXISTANCE4"
      WRITE_LONG 0x1c4 %soundreplace3%
      WRITE_LONG 0x1c8 %soundreplace4%
    END
    PATCH_IF ("%soundreplace5%" > 0) BEGIN
      PATCH_PRINT "HW31: %SOURCE_FILE% - Soundset moved : EXISTANCE4 -> EXISTANCE5"
      WRITE_LONG 0x1c8 %soundreplace4%
      WRITE_LONG 0x1cc %soundreplace5%
    END
  END
END

PATCH_IF ("%SOURCE_RES%" STR_EQ "SENDRO03") AND (SOURCE_SIZE > 0x2d3) BEGIN
  READ_LONG  0x2a8 "meminfo_off" ELSE 0
  READ_LONG  0x2ac "meminfo_num" ELSE 0
  READ_LONG  0x2b0 "mem_spl_off" ELSE 0
  READ_LONG  0x2b4 "mem_spl_num" ELSE 0

  PATCH_IF ("meminfo_off" > 0x2d3) AND ("mem_spl_off" > 0x2d3) BEGIN
    READ_SHORT ("%meminfo_off%" + 0x04 + (0x10 * ("%meminfo_num%" - 1))) "spl_mem_num"
    READ_SHORT ("%meminfo_off%" + 0x08 + (0x10 * ("%meminfo_num%" - 1))) "spl_tbl_idx"
    READ_SHORT ("%meminfo_off%" + 0x0c + (0x10 * ("%meminfo_num%" - 1))) "spl_tbl_cnt"
    READ_ASCII ("%mem_spl_off%" +        (0x0c * ("%spl_tbl_idx%" + "%spl_tbl_cnt%"))) "resref1" ELSE 0
    READ_ASCII ("%mem_spl_off%" +        (0x0c * ("%spl_tbl_idx%" + "%spl_tbl_cnt%" + 1))) "resref2" ELSE 0
    READ_ASCII ("%mem_spl_off%" +        (0x0c * ("%spl_tbl_idx%" + "%spl_tbl_cnt%" + 2))) "resref3" ELSE 0
    READ_ASCII ("%mem_spl_off%" +        (0x0c * ("%spl_tbl_idx%" + "%spl_tbl_cnt%" + 3))) "resref4" ELSE 0
    PATCH_IF ("%resref1%" STR_EQ "SPCL900") BEGIN
      PATCH_PRINT "HW32: %SOURCE_FILE% - Known ERROR in SENDRO03.CRE! (%resref1%, %resref2%, %resref3%, %resref4%) unaccounted for! Fixing..."
      WRITE_SHORT ("%meminfo_off%" + 0x04 + (0x10 * ("%meminfo_num%" - 1))) 6
      WRITE_SHORT ("%meminfo_off%" + 0x0c + (0x10 * ("%meminfo_num%" - 1))) 6
    END
  END
END
