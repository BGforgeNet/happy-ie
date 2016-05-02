//DTLCEP: Item name contains cr/lf


READ_LONG 0x8 uname_ref
READ_LONG 0xc name_ref
GET_STRREF uname_ref uname
GET_STRREF name_ref name
name_len = STRING_LENGTH ~%name%~
uname_len = STRING_LENGTH ~%uname%~

PATCH_IF name_len > 1 BEGIN
  INNER_PATCH ~%name%~ BEGIN
     READ_BYTE (name_len - 1) last_char
  END
  PATCH_IF last_char = 0xa OR last_char = 0xd // \r or \n
//  (~%name%~ STRING_MATCHES_REGEXP ~^.*\r$~) = 0 OR
//  (~%name%~ STRING_MATCHES_REGEXP ~^.*\n$~) = 0
  BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: name ends with CRLF. Fixed.~
    INNER_PATCH_SAVE new_name ~%name%~ BEGIN
      DELETE_BYTES (name_len - 1) 1
    END
    SAY_EVALUATED NAME2 ~%new_name%~
  END
END

PATCH_IF uname_len > 1 BEGIN
  INNER_PATCH ~%uname%~ BEGIN
     READ_BYTE (uname_len - 1) last_char
  END
  PATCH_IF last_char = 0xa OR last_char = 0xd
  BEGIN
    PATCH_PRINT ~%SOURCE_FILE% issue: uname ends with CRLF. Fixed.~
    INNER_PATCH_SAVE new_uname ~%uname%~ BEGIN
      DELETE_BYTES (uname_len - 1) 1
    END
    SAY_EVALUATED NAME1 ~%new_uname%~
  END
END
