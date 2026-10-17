#include "ui_translation.h"
#include "assets.h"
#include "zelda_rtl.h"
#include "variables.h"
#include "load_gfx.h"
#include "hud.h"
#include <string.h>

// Old snapshots contain their own graphics. Refresh identified UI banks without
// touching progress, custom controller glyphs, dialogue pixels or other banks.
void UiTranslation_RestoreAfterLoad(void) {
  if (!UiTranslation_Active()) return;
  static uint8 original[4096], translated[4096];
  int module = main_module_index;
  if ((module >= 1 && module <= 4) || module == 26) {
    const uint8 *font = FindIndexInMemblk(kDialogueFont(0), 0).ptr;
    UiTranslation_RestoreTiles((uint8 *)&g_zenv.vram[0x7000], font,
                              UiTranslation_Get(kUi_InterfaceFont, font), 4096);
  } else if (module >= 5 && module <= 25 && module != 20) {
    const int packs[3] = {0x6a, 0x6b, 0x69};
    for (int i = 0; i < 3; i++) {
      MemBlk us = FindInAssetArray(64, packs[i]);
      if (Decompress(original, us.ptr) != 2048 || Decomp_spr(translated, packs[i]) != 2048)
        continue;
      UiTranslation_RestoreTiles((uint8 *)&g_zenv.vram[0x7000 + i * 0x400], original, translated, 2048);
      UiTranslation_RestoreTiles(&g_ram[0x14000], original, translated, 2048);
    }
  }
  // Rebuild labels only while a complete inventory is displayed. Opening,
  // closing and bottle expansion retain their in-flight animation buffers.
  if (module == 14 && submodule_index == 1 && overworld_map_state >= 3 && overworld_map_state <= 5) {
    Hud_DrawYButtonItems();
    Hud_DrawAbilityBox();
    Hud_DrawEquipmentBox();
    Hud_DrawSelectedYButtonItem();
    memcpy(&g_zenv.vram[0x6800], &g_ram[0x1000], 0x800);
  }
}
