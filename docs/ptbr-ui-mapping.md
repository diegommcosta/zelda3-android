# Mapeamento da interface PT-BR

ROM PT-BR: `D0D09ED41F9C373FE6AFDCCAFBF0DA8C88D3D90D`. Original: `6D4F10A8B10E10DBE624CB23CF03B88BB8252973`.

O manifesto contém somente endereços, tamanhos e hashes; nenhum recurso extraído. Os endereços são offsets de arquivo sem cabeçalho de copiador.

## Cobertura

| Área | Recursos / integração |
| --- | --- |
| Inventário e HUD | Nove tabelas de nomes/habilidades em hud.c; gráficos 69–6B |
| Seleção, criação, cópia e exclusão | Cinco stripes em nmi.c; quatro tabelas de confirmação em select_file.c; fonte original da tradução |
| Entrada de nome | Mesma tabela de caracteres e navegação US, auditada; fonte bruta da ROM PT-BR em TransferFontToVRAM |
| Salvar/continuar e derrota | Texto dos diálogos já extraído; gráficos comuns 6A/6B; nenhuma tabela adicional alterada em messaging.c |
| Abertura/apresentação | Gráficos alterados 05/08/68 e BGs; legend graphics de attract.c auditados sem mudanças |
| Mapas | Mapa global, stripes do mapa e tabelas de masmorras auditados sem mudanças; manter originais |
| Encerramento/créditos | Texto em palavras de tile big-endian; offsets e fonte PT; legendas relocadas para $A0:80C8 |

## Adaptações de código do hack

- Ponteiros gráficos: seguir tabelas separadas de banco/alto/baixo em 4FF3/50D2/51B1 (sprites) e 4F80/505F/513E (BG). Comparar conteúdo descomprimido, pois quase todos os pacotes foram recomprimidos/relocados.
- Créditos: PT troca índices de byte da tabela US por palavras completas em big-endian. O motor deve ler palavras diretamente e preencher espaços com 3CA9.
- Legendas do encerramento: dados em 1000C8, delimitados pelos 17 offsets em 742E1; o bloco US em 73F4C permanece na ROM mas não é mais usado.
- A fonte de interface usa os tiles brutos de 70000; a fonte normalizada dos diálogos permanece separada.
- Não substituir layouts completos de inventário: preservar as extensões do port e trocar somente tabelas e gráficos traduzidos.

## Recursos alterados

| ID | Recurso | Offset PT | Bytes |
| --- | --- | --- | --- |
| 0001 | kHudAbilityText | 06F959 | 160 |
| 0002 | kHudGlovesText | 06F931 | 40 |
| 0003 | kHudBottlesItemText | 06F449 | 256 |
| 0004 | kHudMushroomItemText | 06F549 | 32 |
| 0005 | kHudFluteItemText | 06F569 | 64 |
| 0006 | kHudMirrorItemText | 06F5A9 | 32 |
| 0007 | kHudBowItemText | 06F5C9 | 96 |
| 0008 | kHudItemText | 06F1C9 | 640 |
| 0009 | kHudEquipmentDungeonItemText | 06ED09 | 32 |
| 000A | kCopyFile_SelectionAndBlinker_Tab | 06668D | 173 |
| 000B | kCopyFile_TargetSelectionAndBlink_Tab0 | 06673A | 133 |
| 000C | kCopyFile_TargetSelectionAndBlink_Tab2 | 06523A | 49 |
| 000D | kKILLFile_ChooseTarget_Tab2 | 06541E | 101 |
| 0105 | sprite_05 | 088E00 | 1536 |
| 0108 | sprite_08 | 08A000 | 1536 |
| 012D | sprite_2d | 0B27D6 | 514 |
| 0161 | sprite_61 | 0C10ED | 552 |
| 0168 | sprite_68 | 0C283D | 1173 |
| 0169 | sprite_69 | 0C2CD2 | 1299 |
| 016A | sprite_6a | 0A7636 | 1434 |
| 016B | sprite_6b | 0A7BD0 | 1636 |
| 0216 | background_16 | 091A64 | 1288 |
| 023D | background_3d | 09D300 | 1178 |
| 0241 | background_41 | 09E6CB | 1329 |
| 024D | background_4d | 0A1EE2 | 1331 |
| 0253 | background_53 | 0A3ABE | 1306 |
| 0271 | background_71 | 0A7636 | 1434 |
| 0272 | background_72 | 0A7BD0 | 1636 |
| 0363 | kBgTilemap_0 | 065D6D | 1115 |
| 0364 | kBgTilemap_1 | 0667BF | 1467 |
| 0365 | kBgTilemap_2 | 0662A8 | 177 |
| 0366 | kBgTilemap_3 | 06663C | 81 |
| 0367 | kBgTilemap_4 | 066456 | 233 |
| 0400 | InterfaceFont | 070000 | 4096 |
| 0401 | CreditsText | 073038 | 2041 |
| 0402 | CreditsOffsets | 07393D | 788 |
| 0403 | SceneCaptions | 1000C8 | 1074 |
| 0404 | SceneOffsets | 0742E1 | 34 |

Hashes individuais e as 138 tabelas auditadas estão em `tools/translations/ptbr_ui_manifest.json`.

Reprodução: `python tools/translations/map_ui.py --us-rom <original> --translated-rom <ptbr>`.

## Validação no aparelho

Comparar título/apresentação; criar um nome e copiar/excluir arquivos; abrir inventário, mapas e menu de salvar; provocar derrota; conferir legendas finais e créditos. Repetir com tela cheia e telas trocadas. Carregar estados anteriores e conferir a próxima transição de tela. A inspeção dos dados não substitui essa validação visual.
