//note: timings are completely unverified
//due to the ST018 chip design (on-die ROM), testing is nearly impossible

auto ArmDSP::sleep() -> void {
  step(1);
}

auto ArmDSP::get(uint mode, uint32 address) -> uint32 {
  step(1);

  static auto memory = [&](const uint8* memory, uint mode, uint32 address) -> uint32 {
    if(mode & Word) {
      memory += address & ~3;
      return memory[0] << 0 | memory[1] << 8 | memory[2] << 16 | memory[3] << 24;
    } else if(mode & Byte) {
      return memory[address];
    } else {
      return 0;  //should never occur
    }
  };

  switch(address & 0xe000'0000) {
  case 0x0000'0000: return memory(programROM, mode, address & 0x1ffff);
  case 0x2000'0000: return pipeline.fetch.instruction;
  case 0x4000'0000: break;
  case 0x6000'0000: return 0x40404001;
  case 0x8000'0000: return pipeline.fetch.instruction;
  case 0xa000'0000: return memory(dataROM, mode, address & 0x7fff);
  case 0xc000'0000: return pipeline.fetch.instruction;
  case 0xe000'0000: return memory(programRAM, mode, address & 0x3fff);
  }

  address &= 0xe000'003f;

  if(address == 0x4000'0010) {
    if(bridge.cputoarm.ready) {
      bridge.cputoarm.ready = false;
      return bridge.cputoarm.data;
    }
  }

  if(address == 0x4000'0020) {
    return bridge.status();
  }

  return 0;
}

auto ArmDSP::set(uint mode, uint32 address, uint32 word) -> void {
  step(1);

  static auto memory = [](uint8* memory, uint mode, uint32 address, uint32 word) {
    if(mode & Word) {
      memory += address & ~3;
      *memory++ = word >>  0;
      *memory++ = word >>  8;
      *memory++ = word >> 16;
      *memory++ = word >> 24;
    } else if(mode & Byte) {
      memory += address;
      *memory++ = word >>  0;
    }
  };

  switch(address & 0xe000'0000) {
  case 0x0000'0000: return;
  case 0x2000'0000: return;
  case 0x4000'0000: break;
  case 0x6000'0000: return;
  case 0x8000'0000: return;
  case 0xa000'0000: return;
  case 0xc000'0000: return;
  case 0xe000'0000: return memory(programRAM, mode, address & 0x3fff, word);
  }

  address &= 0xe000'003f;
  word    &= 0x0000'00ff;

  if(address == 0x4000'0000) {
    bridge.armtocpu.ready = true;
    bridge.armtocpu.data = word;
  }

  if(address == 0x4000'0010) bridge.signal = true;

  if(address == 0x4000'0020) bridge.timerlatch.byte(0) = word;
  if(address == 0x4000'0024) bridge.timerlatch.byte(1) = word;
  if(address == 0x4000'0028) bridge.timerlatch.byte(2) = word;

  if(address == 0x4000'002c) bridge.timer = bridge.timerlatch;
}
