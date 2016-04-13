// Missing Animation Fixer
READ_SHORT 0x28  "anim"

LOOKUP_IDS_SYMBOL_OF_INT animation animate %anim%
PATCH_IF ("%anim%" STRING_EQUAL "%animation%") BEGIN
  PATCH_PRINT "%SOURCE_FILE% issue: Missing animation! Assigning Gibberling animation..."
  WRITE_SHORT 0x28 30720 // Gibberling
END
