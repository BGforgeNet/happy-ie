//DLTCEP: Inventory BAM has no 2 frames. For scrolls, it doesn't matter

READ_SHORT 0x1c type
PATCH_IF type != 0xb BEGIN //scroll
  SPRINT real_src ~%SOURCE_FILE%~
  READ_ASCII 0x3a inv_bam
  READ_ASCII 0x44 ground_bam
  READ_ASCII 0x58 desc_bam
  READ_BYTE  0x18 flags
  PATCH_IF ( FILE_EXISTS_IN_GAME ~%inv_bam%.bam~
         AND FILE_EXISTS_IN_GAME ~%ground_bam%.bam~
         AND FILE_EXISTS_IN_GAME ~%desc_bam%.bam~
         AND flags BAND 0b00000100 = 0b00000100  // movable
         AND flags BAND 0b00001000 = 0b00001000  // displayable in shop
           ) BEGIN
    INNER_ACTION BEGIN
      COPY_EXISTING ~%inv_bam%.bam~ ~override~
        READ_ASCII 0 sig (4) NULL
        PATCH_IF (~%sig%~ STR_EQ ~BAMC~) BEGIN //If compressed
          READ_LONG 0x8 dl //Uncompressed data length
          DECOMPRESS_INTO_VAR 0xc (SOURCE_SIZE - 0xc) dl ucbam
          INNER_PATCH ~%ucbam%~ BEGIN
            READ_SHORT 0x8 frm_cnt
          END
        END ELSE BEGIN
          READ_SHORT 0x8 frm_cnt
        END
        PATCH_IF frm_cnt < 2 BEGIN
          PATCH_PRINT ~HW99: %real_src% (type %type%): inventory bam %inv_bam% has %frm_cnt% frames.~
        END
      BUT_ONLY
      OUTER_SPRINT SOURCE_FILE ~%real_src%~ //reset SOURCE_FILE for later PATCH_PRINT's
    END
  END
END
