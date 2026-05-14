#!/usr/bin/env python3

import sys
from pathlib import Path

BASE_DIR = Path(__file__).parent.resolve()

# Add local lib and modules folders to the import path
if "lib" not in sys.path:
    sys.path.insert(0, str(BASE_DIR / "lib"))
if "modules" not in sys.path:
    sys.path.insert(0, str(BASE_DIR / "modules"))
if "scripts" not in sys.path:
    sys.path.insert(0, str(BASE_DIR / "scripts"))


# Only runs if this script is executed directly
if __name__ == "__main__":
    import main
    main.run()