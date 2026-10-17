#!/usr/bin/env python3
"""Check real PT-BR imports with the production Java classes, without Android.

Requires a JDK (javac/java on PATH) and the user's own US and translated ROMs.
ROMs, classes and generated test data are kept in a temporary directory.
"""

import argparse
from pathlib import Path
import subprocess
import tempfile

from build_ptbr_patch import ROOT, read_rom


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--us-rom", required=True)
    parser.add_argument("--translated-rom", required=True)
    args = parser.parse_args()
    sources = ROOT / "app/src/main/java/com/dishii/zelda3"
    with tempfile.TemporaryDirectory(prefix="zelda3-ptbr-tests-") as temporary:
        directory = Path(temporary)
        pt, us = directory / "pt.sfc", directory / "us.sfc"
        pt.write_bytes(read_rom(args.translated_rom))
        us.write_bytes(read_rom(args.us_rom))
        subprocess.run([
            "javac", "--release", "8", "-Xlint:-options", "-d", str(directory),
            str(sources / "BpsPatcher.java"), str(sources / "TranslationExtractor.java"),
            str(sources / "UiTranslationPackage.java"), str(sources / "UiTranslationResources.java"),
            str(ROOT / "tools/tests/TranslationImportTest.java"),
            str(ROOT / "tools/tests/UiTranslationPackageTest.java"),
        ], cwd=ROOT, check=True)
        subprocess.run([
            "java", "-cp", str(directory), "com.dishii.zelda3.UiTranslationPackageTest", str(pt), str(us),
            str(ROOT / 'build/ui-package.bin'),
        ], cwd=ROOT, check=True)
        subprocess.run([
            "java", "-cp", str(directory), "com.dishii.zelda3.TranslationImportTest", str(pt), str(us),
        ], cwd=ROOT, check=True)


if __name__ == "__main__":
    main()
