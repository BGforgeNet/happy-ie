// Missing Rest Spawn Remover
READ_LONG  0xc0 "rest_off" ELSE 0

PATCH_IF (rest_off > 0x11b) BEGIN
  FOR (index = 0 ; index < 10 ; index = index + 1) BEGIN
    READ_ASCII ("%rest_off%" + 0x48 + ("%index%" * 0x08)) "resref"
    PATCH_IF (NOT ("%resref%" STR_EQ "") AND                  // ignore empty entries
              NOT ("%resref%" STR_EQ "none") AND              // ignore 'none'
              ("%resref%" STRING_COMPARE_REGEXP "^[Rr][Dd].+$")) BEGIN // ignore creatures starting with RD
      SET "exists" = 0
      PATCH_IF FILE_EXISTS_IN_GAME ~%resref%.cre~ BEGIN
        SET "exists" = 1
      END
      PATCH_IF ("%exists%" = 0) BEGIN
        PATCH_PRINT "%SOURCE_FILE% issue: Rest Spawn creature file does not exist (%resref%.cre)! Nulling..."
        WRITE_ASCII ("%rest_off%" + 0x48 + ("%index%" * 0x08)) "NONE" #8
      END
    END
  END
  SET "none_count" = 0
  FOR (index = 0 ; index < 10 ; index = index + 1) BEGIN
    READ_ASCII ("%rest_off%" + 0x48 + ("%index%" * 0x08)) "resref"
    PATCH_IF (("%resref%" STR_EQ "") OR ("%resref%" STR_EQ "none")) BEGIN
      SET "none_count" = "none_count" + 1
    END
  END
  READ_SHORT ("%rest_off%" + 0x98) "spawncount"
  PATCH_IF (("%none_count%" = 10) AND ("%spawncount%" != 0)) BEGIN
    PATCH_PRINT "%SOURCE_FILE% issue: No creatures in Rest Spawn Entry but area still set to spawn something! Setting number of spawnable creatures to 0..."
    WRITE_SHORT ("%rest_off%" + 0x98) 0
  END
END
