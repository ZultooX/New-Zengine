#include "Asset.h"

void Asset::SetDirty() { myFlags.SetBit((int)Flags::Dirty, true); }
void Asset::ClearDirty() { myFlags.SetBit((int)Flags::Dirty, false); }
bool Asset::IsDirty() { return myFlags.GetBit((int)Flags::Dirty); }
