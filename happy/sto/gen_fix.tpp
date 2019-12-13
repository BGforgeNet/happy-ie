READ_LONG  0x08 "type"

// Sales Manager
READ_BYTE  0x10 "flags"
READ_LONG  0x30 "purch_num"
READ_LONG  0x38 "sales_num"
READ_LONG  0x50 "drink_num"
READ_LONG  0x74 "cures_num"

PATCH_IF (("%flags%" BAND 0b00000001) = 0b00000000) AND ("%sales_num%" > 0) AND ("%type%" = 0) BEGIN
  PATCH_PRINT "HW234: %SOURCE_FILE% - Stocked Items exist but store set to not sell! Initiating sales..."
  WRITE_BYTE 0x10 ("%flags%" BOR 0b00000001)
END
PATCH_IF (("%flags%" BAND 0b00000010) = 0b00000000) AND ("%purch_num%" > 0) AND ("%type%" = 0) BEGIN
  PATCH_PRINT "HW235: %SOURCE_FILE% - Purchasable Items exist but store set to not buy! Initiating sales..."
  WRITE_BYTE 0x10 ("%flags%" BOR 0b00000010)
END
PATCH_IF (("%flags%" BAND 0b00100000) = 0b00000000) AND ("%cures_num%" > 0) AND ("%type%" = 3) BEGIN
  PATCH_PRINT "HW236: %SOURCE_FILE% - Stocked Cures exist but temple set to not sell! Initiating sales..."
  WRITE_BYTE 0x10 ("%flags%" BOR 0b00100000)
END
PATCH_IF (("%flags%" BAND 0b01000000) = 0b00000000) AND ("%drink_num%" > 0) AND ("%type%" = 1) BEGIN
  PATCH_PRINT "HW237: %SOURCE_FILE% - Stocked Drinks exist but tavern set to not sell! Initiating sales..."
  WRITE_BYTE 0x10 ("%flags%" BOR 0b01000000)
END
PATCH_IF (("%flags%" BAND 0b01000000) = 0b00000000) AND ("%drink_num%" > 0) AND ("%type%" = 2) BEGIN
  PATCH_PRINT "HW238: %SOURCE_FILE% - Stocked Drinks exist but inn set to not sell! Initiating sales..."
  WRITE_BYTE 0x10 ("%flags%" BOR 0b01000000)
END

PATCH_IF (("%flags%" BAND 0b00000001) = 0b00000001) AND ("%sales_num%" = 0) AND ("%type%" = 0) BEGIN
  PATCH_PRINT "HW239: %SOURCE_FILE% - Store selling items but does not have any in stock! Stopping sales..."
  WRITE_BYTE 0x10 ("%flags%" BAND 0b11111110)
END
PATCH_IF (("%flags%" BAND 0b00000010) = 0b00000010) AND ("%purch_num%" = 0) AND ("%type%" = 0) BEGIN
  PATCH_PRINT "HW240: %SOURCE_FILE% - Store buying items but cannot buy any kind! Stopping sales..."
  WRITE_BYTE 0x10 ("%flags%" BAND 0b11111101)
END
PATCH_IF (("%flags%" BAND 0b00100000) = 0b00100000) AND ("%cures_num%" = 0) AND ("%type%" = 3) BEGIN
  PATCH_PRINT "HW241: %SOURCE_FILE% - Temple selling cures but does not have any in stock! Stopping sales..."
  WRITE_BYTE 0x10 ("%flags%" BAND 0b11011111)
END
PATCH_IF (("%flags%" BAND 0b01000000) = 0b01000000) AND ("%drink_num%" = 0) AND ("%type%" = 1) BEGIN
  PATCH_PRINT "HW242: %SOURCE_FILE% - Tavern selling drinks but does not have any in stock! Stopping sales..."
  WRITE_BYTE 0x10 ("%flags%" BAND 0b10111111)
END
PATCH_IF (("%flags%" BAND 0b01000000) = 0b01000000) AND ("%drink_num%" = 0) AND ("%type%" = 2) BEGIN
  PATCH_PRINT "HW243: %SOURCE_FILE% - Inn selling drinks but does not have any in stock! Stopping sales..."
  WRITE_BYTE 0x10 ("%flags%" BAND 0b10111111)
END

// Missing Item Remover
READ_LONG  0x34 "sales_off" ELSE 0
READ_LONG  0x38 "sales_num" ELSE 0

PATCH_IF (sales_off > 0x9b) BEGIN
  FOR (index = 0 ; index < sales_num ; index = index + 1) BEGIN
    READ_ASCII ("%sales_off%" +        (0x1c * "%index%")) "resref"
    PATCH_IF NOT (FILE_EXISTS_IN_GAME ~%resref%.itm~) BEGIN
      PATCH_PRINT "HW244: %SOURCE_FILE% - Stocked Item #%index% does not exist (%resref%.itm)! Removing item..."
      REMOVE_STORE_ITEM ~%resref%~
      SET "index" = 0 - 1
      READ_LONG  0x38 "sales_num"
    END
  END
END
