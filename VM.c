#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char* getSector(FILE* disk, unsigned int sector, char* str)
{
	for(unsigned short int i = 512*sector ; i < 512*(sector+1) ; i++)
		str[i] = fgetc(disk);
	return str;
}

enum reg16Num {AX, BX, CX, DX};
enum reg8Num {AH, AL, BH, BL, CH, CL, DH, DL};

typedef struct reg {
  unsigned char sub[2];
  unsigned short int reg;
} reg;

// Registers
reg ax = {0}, bx = {0}, cx = {0}, dx = {0};
// Flags
unsigned char grand = 0, petit = 0, egal = 0;

reg* registers(uint8_t reg){
  switch(reg){
    case AX: return &ax;
    case BX: return &bx;
    case CX: return &cx;
    case DX: return &dx;
  }
}

void setReg16(reg* reg, short int value){
  reg -> reg = value;
  reg -> sub[0] = (uint8_t) value >> 8;
  reg -> sub[1] = (uint8_t) value;
}

void setReg8(reg* reg, uint8_t subreg, short int value){
  reg -> sub[subreg] = value;
  reg -> reg = (((short int) reg -> sub[0]) << 8) | reg -> sub[1];
}

//reg8_to_reg16: og_reg16 = reg8/2

const char* ERR[2] = {
  "Erreur de lecture du disque inséré. Avez vous essayé de souffler dessus ?",
  "Disque non-système. Veuillez insérer un Disque Système et réessayer."
};

void err(unsigned char err_code)
{
  printf("[ERR] %u: %s\n", err_code, ERR[err_code]);
}

void execSector(char* secteur)
{
  for(unsigned short int i  = 0 ; i < 512 ; i++)
  {
    switch(secteur[i])
    {
      case 0: // nop
        break;
      case 1: // int
          switch(secteur[++i])
          {
            case 0x10:
              if(ax.sub[0] == 0x0F)
                putchar(ax.sub[1]);
              break;
          }
        break;
      case 2: // mov <reg8> <val>
          setReg8(registers(secteur[i+1]/2), secteur[i+1]%2, secteur[i+2]);
          i+=2;
        break;
      case 3: // mov <reg8> <reg>
        break;
      case 4: // mov <mem8> <val>
        break;
      case 5: // mov <mem8> <mem8>
        break;
      case 6: // mov <reg8> <mem8>
        break;
      case 7: // mov <mem8> <reg8>
        break;
      case 8: // inc <reg8>
        setReg8(registers(secteur[i+1]/2), secteur[i+1]%2, registers(secteur[i+1]/2)->sub[secteur[i+1]%2] + 1);
        i++;
        break;
      case 9: // dec <reg8>
        setReg8(registers(secteur[i+1]/2), secteur[i+1]%2, registers(secteur[i+1]/2)->sub[secteur[i+1]%2] - 1);
        i++;
        break;
      case 10: // mov <reg8> <val>
        break;
      case 11: // mov <regF> <regF>
        break;
      case 12: // mov <memF> <val>
        break;
      case 13: // mov <memF> <memF>
        break;
      case 14: // mov <regF> <memF>
        break;
      case 15: // mov <memF> <regF>
        break;
      case 16: // inc <regF>
        break;
      case 17: // dec <regF>
        break;
      case 18: // jmp <octet>
        i = secteur[++i];
        i--;
        break;
      case 19: // call <routine>
        break;
      case 20: // cmp <reg8> <val>
        if(registers(secteur[i+1]/2)->sub[secteur[i+1]%2] == secteur[i+2])
          egal = 1;
        if(registers(secteur[i+1]/2)->sub[secteur[i+1]%2] > secteur[i+2])
          grand = 1;
        if(registers(secteur[i+1]/2)->sub[secteur[i+1]%2] > secteur[i+2])
          grand = 1;
        i += 2;
        break;
      case 21: // jeq <octet>
        if(egal){
          i = secteur[++i];
          i--;
        }
        break;
      case 22: // jne <octet>
        if(!egal){
          i = secteur[++i];
          i--;
        }
        break;
    }
  }
}

void exec(FILE* disk){
  char secteur[512];
  getSector(disk, 0, secteur);

  if(secteur[510] ^ secteur[511] == 0xFF)
    puts("[LIMEVM] Disque système trouvé !\r\n");
  else
  {
    err(0x01);
  }

  execSector(secteur);

  return;
}
