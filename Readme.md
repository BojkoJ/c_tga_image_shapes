# TGA Image Drawing Program

## Popis

Tento program umožňuje uživatelům vytvářet obrázky ve formátu TGA (Targa Graphic File) s různými geometrickými tvary, jako jsou čáry, obdélníky, kruhy a trojúhelníky. Program přijímá příkazy přes příkazovou řádku a umožňuje uživatelům specifikovat vlastnosti tvarů, jako jsou rozměry, pozice a barvy. Vytvořené obrázky jsou poté uloženy jako soubory TGA.

## Funkce

- **Čára**: Vykreslení čáry s definovanou počáteční a koncovou pozicí a barvou.
- **Obdélník**: Vykreslení obdélníku s definovanou pozicí, rozměry a barvou.
- **Kruh**: Vykreslení kruhu s definovaným středem, poloměrem a barvou.
- **Trojúhelník**: Vykreslení rovnostranného trojúhelníku s definovaným středem, délkou strany a barvou.
- **Otočený obdélník**: Vykreslení obdélníku s definovanou pozicí, rozměry, úhlem rotace a barvou.

## Ovládání programu

Program se ovládá zadáváním příkazů. Zde jsou příklady některých základních příkazů:

- **line x1,y1,x2,y2,r,g,b,a**: Vykreslí čáru z (x1, y1) do (x2, y2) s barvou (r, g, b, a).
- **rectangle x,y,width,height,r,g,b,a**: Vykreslí obdélník s rozměry a barvou.
- **circle x,y,p,r,g,b,a**: Vykreslí kruh se středem (x, y), poloměrem p a barvou.
- **triangle x,y,s,r,g,b,a**:Vykreslí trojúhelník se středem (x, y), délkou strany s a barvou.
- **rotated-rectangle angle,x,y,width,height,r,g,b,a:**: Vykreslí zarotovaný obdélník, kde jsou parametry stejné jako u obdélníku jen je přidán angle - úhel otočení
- **save**: Uloží obrázek do výstupního souboru.
- **exit**: Ukončí program a uloží obrázek.

## Jak přeložit

Program využívá `Makefile` pro jednoduché přeložení. Ujistěte se, že máte nainstalovaný kompilátor GCC a následně použijte následující příkazy:

1. Otevřete terminál ve složce, kde se nachází zdrojové soubory programu.
2. Spusťte příkaz `make` pro sestavení programu:

```bash
make
```

Tímto příkazem se sestaví výsledný spustitelný soubor, který je poté možné spustit z příkazové řádky.

## Jak spustit

Po úspěšném přeložení můžete program spustit pomocí následujícího příkazu:

```bash
./program --output <cesta_k_vystupnimu_souboru> --width <šířka obrázku> --height <výška obrázku>
```

Nahraďte <cesta_k_souboru>, <šířka> a <výška> skutečnými hodnotami podle vašich potřeb. Poté můžete zadávat příkazy pro kreslení tvarů, jak je popsáno výše.

## Zdroje:

Z čeho jsem čerpal?

- **Wikipedie**:
  [Endianita](https://en.wikipedia.org/wiki/Endianness)
  [Bresenhamuv_Algoritmus_Kruhu](https://en.wikipedia.org/wiki/Midpoint_circle_algorithm)
  [Bresenhamuv*Algoritmus*Čáry](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- **Další zdroje**:
  [Skripta](https://mrlvsb.github.io/upr-skripta/c/aplikovane_ulohy/tga.html)
  [Konstanta_Pí](https://www.piday.org/million/)
  [Dokumentace_Jazyka_C](https://devdocs.io/c/)
